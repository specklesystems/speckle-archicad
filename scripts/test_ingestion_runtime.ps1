param([switch]$Baseline)
$ErrorActionPreference = 'Stop'
trap {
    [Console]::Error.WriteLine($_.ToString())
    exit 1
}
$repo = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$mode = if ($Baseline) { 'baseline' } else { 'fixed' }
$audit = Join-Path $repo ('.audit/runtime-' + $mode + '-' + (Get-Date -Format 'yyyyMMdd-HHmmss'))
New-Item -ItemType Directory -Path $audit -Force | Out-Null
$vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio/Installer/vswhere.exe'
if (!(Test-Path -LiteralPath $vswhere)) { throw 'Visual Studio Installer vswhere.exe is required.' }
$installation = & $vswhere -latest -prerelease -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (!$installation) { throw 'Visual Studio C++ toolchain was not found.' }
$devshell = Join-Path $installation 'Common7/Tools/Launch-VsDevShell.ps1'
& $devshell -Arch amd64 -HostArch amd64 -SkipAutomaticLocation
if (!(Get-Command cl -ErrorAction SilentlyContinue)) { throw 'Visual Studio developer shell did not provide cl.exe.' }
$addon = Join-Path $repo 'AddOns/Speckle/Sources/AddOn'
$executable = Join-Path $audit 'IngestionRuntimeTests.exe'
$arguments = @('/nologo', '/std:c++20', '/EHsc', '/W4', '/DWIN32_LEAN_AND_MEAN', '/DNOMINMAX')
if ($Baseline) { $arguments += '/DINGESTION_BASELINE' }
foreach ($directory in @('Artifacts', 'Network', 'Converter', 'Connector', 'Utils')) { $arguments += ('/I' + (Join-Path $addon $directory)) }
$arguments += '/I' + (Join-Path $repo 'Libs/json/include')
$arguments += @((Join-Path $repo 'tests/IngestionRuntimeTests.cpp'), (Join-Path $addon 'Artifacts/ArtifactUploader.cpp'), (Join-Path $addon 'Network/WinHttpClient.cpp'))
$arguments += @(('/Fe' + $executable), ('/Fo' + $audit + '\'), '/link', 'winhttp.lib')
& cl @arguments 2>&1 | Tee-Object -FilePath (Join-Path $audit 'compile.log')
if ($LASTEXITCODE -ne 0) { throw "Runtime integration compile failed; see $audit" }
$python = (Get-Command python -ErrorAction Stop).Source
$ready = Join-Path $audit 'server-port.txt'
$serverScript = Join-Path $repo 'tests/ingestion_http_server.py'
$server = Start-Process -FilePath $python -ArgumentList @('-u', ('"' + $serverScript + '"'), '--ready-file', ('"' + $ready + '"')) -WindowStyle Hidden -PassThru -RedirectStandardOutput (Join-Path $audit 'server.log') -RedirectStandardError (Join-Path $audit 'server-errors.log')
try {
    $until = (Get-Date).AddSeconds(10)
    while (!(Test-Path -LiteralPath $ready)) {
        if ($server.HasExited -or (Get-Date) -gt $until) { throw "Loopback server failed to start; see $audit" }
        Start-Sleep -Milliseconds 50
    }
    $port = (Get-Content -LiteralPath $ready -Raw).Trim()
    & $executable ('http://127.0.0.1:' + $port) (Join-Path $audit 'runtime.parquet') 2>&1 | Tee-Object -FilePath (Join-Path $audit 'runtime.log')
    if ($LASTEXITCODE -ne 0) { throw "Runtime integration failed; see $audit" }
    Write-Host "Runtime component integration evidence: $audit"
}
finally {
    if (!$server.HasExited) { Stop-Process -Id $server.Id }
}
