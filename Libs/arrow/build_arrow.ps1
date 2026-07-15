# Builds the minimal static Apache Arrow + Parquet libraries vendored under Libs/arrow/.
#
# The add-on links Arrow statically into the .apx (single-file deployment), so these libs
# must be built with the exact ABI-relevant flags the add-on uses (see the root
# CMakeLists.txt SetCompilerParams + CMAKE_MSVC_RUNTIME_LIBRARY):
#   /Zc:wchar_t-  /MD (MultiThreadedDLL, all configs)  _ITERATOR_DEBUG_LEVEL=0  C++20
# One Release-flavored build per toolset serves both Debug and Release add-on builds
# because the add-on always uses the release CRT (/MD) and IDL=0.
#
# Feature set is the minimum for the Speckle bundle format: Parquet + ZSTD (+ IPC, which
# parquet::arrow needs to serialize the ARROW:schema metadata). Everything else is off.
# SIMD is disabled for BOTH toolsets: v142 (MSVC 14.29) cannot compile Arrow 24's
# constexpr-heavy SIMD bit-packing kernels (bpacking_simd_kernel_internal.h), and keeping
# v143 scalar too gives AC 27/28/29 identical behavior. Scalar Parquet unpacking is an
# accepted perf trade for the add-on.
#
# Run manually when bumping the Arrow version (this is NOT part of the normal build):
#   powershell -ExecutionPolicy Bypass -File Libs\arrow\build_arrow.ps1
# Requires: VS 2022+ with the v142 and v143 toolsets, CMake >= 3.25, network access
# (source tarball + Arrow's bundled third-party downloads at build time).

param(
    [string]$ArrowVersion = "24.0.0",
    [string]$WorkDir = "C:\dev\arrowtmp",   # short path: Arrow's ExternalProject trees are deep
    [string[]]$Toolsets = @("v142", "v143"),
    [string]$Generator = "Visual Studio 18 2026"
)

$ErrorActionPreference = "Stop"
$repoArrow = $PSScriptRoot   # .../Libs/arrow

# ── fetch + extract source ──
New-Item -ItemType Directory -Force $WorkDir | Out-Null
$tarball = Join-Path $WorkDir "apache-arrow-$ArrowVersion.tar.gz"
$srcDir = Join-Path $WorkDir "arrow-apache-arrow-$ArrowVersion"
if (-not (Test-Path $tarball)) {
    Write-Host "Downloading Arrow $ArrowVersion source..."
    curl.exe -sSL -o $tarball "https://github.com/apache/arrow/archive/refs/tags/apache-arrow-$ArrowVersion.tar.gz"
}
if (-not (Test-Path $srcDir)) {
    Write-Host "Extracting..."
    tar -xzf $tarball -C $WorkDir
}

# ── v142 compat patch ──
# MSVC 14.29 (v142) loses sight of constexpr locals referenced inside nested generic
# lambdas (parquet/decoder.cc: 'kBufferSize': undeclared identifier). 'static constexpr'
# is semantically identical here and compiles on every toolset. Idempotent.
$decoderCc = Join-Path $srcDir "cpp\src\parquet\decoder.cc"
$src = Get-Content -Raw $decoderCc
$patched = $src -replace '(?<!static )constexpr int32_t kBufferSize', 'static constexpr int32_t kBufferSize'
if ($patched -ne $src) {
    Set-Content -NoNewline -Encoding utf8 $decoderCc $patched
    Write-Host "Patched decoder.cc (static constexpr kBufferSize) for v142"
}

# ABI-critical flags. /EHsc etc. mirror CMake's MSVC defaults, which passing CMAKE_CXX_FLAGS replaces.
# _HAS_AUTO_PTR_ETC=1 restores C++17-removed STL features (std::random_shuffle) that the
# bundled Thrift still uses. The C++ standard is NOT forced globally: Arrow picks its own
# (C++17) and the bundled deps pick theirs — MSVC's STL ABI is stable across std levels,
# so the add-on's C++20 TUs link against these libs fine.
$cxxFlags = "/DWIN32 /D_WINDOWS /EHsc /Zc:wchar_t- /D_ITERATOR_DEBUG_LEVEL=0 /D_HAS_AUTO_PTR_ETC=1"

foreach ($ts in $Toolsets) {
    $buildDir = Join-Path $WorkDir "build_$ts"
    $installDir = Join-Path $WorkDir "install_$ts"
    Write-Host "=== Configuring Arrow for toolset $ts ==="
    cmake -S (Join-Path $srcDir "cpp") -B $buildDir -G $Generator -A x64 -T $ts `
        -DCMAKE_INSTALL_PREFIX="$installDir" `
        -DCMAKE_CXX_FLAGS="$cxxFlags" `
        -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDLL `
        -DARROW_BUILD_STATIC=ON `
        -DARROW_BUILD_SHARED=OFF `
        -DARROW_SIMD_LEVEL=NONE `
        -DARROW_RUNTIME_SIMD_LEVEL=NONE `
        -DARROW_PARQUET=ON `
        -DARROW_IPC=ON `
        -DARROW_WITH_ZSTD=ON `
        -DARROW_DEPENDENCY_SOURCE=BUNDLED `
        -DARROW_DEPENDENCY_USE_SHARED=OFF `
        -DARROW_COMPUTE=OFF `
        -DARROW_ACERO=OFF `
        -DARROW_DATASET=OFF `
        -DARROW_CSV=OFF `
        -DARROW_JSON=OFF `
        -DARROW_FILESYSTEM=OFF `
        -DARROW_FLIGHT=OFF `
        -DARROW_GANDIVA=OFF `
        -DARROW_WITH_SNAPPY=OFF `
        -DARROW_WITH_LZ4=OFF `
        -DARROW_WITH_ZLIB=OFF `
        -DARROW_WITH_BROTLI=OFF `
        -DARROW_WITH_BZ2=OFF `
        -DARROW_JEMALLOC=OFF `
        -DARROW_MIMALLOC=OFF `
        -DARROW_BUILD_TESTS=OFF `
        -DARROW_BUILD_BENCHMARKS=OFF `
        -DARROW_BUILD_EXAMPLES=OFF
    if ($LASTEXITCODE -ne 0) { throw "configure failed for $ts" }

    Write-Host "=== Building ($ts, Release) ==="
    cmake --build $buildDir --config Release --parallel
    if ($LASTEXITCODE -ne 0) { throw "build failed for $ts" }
    cmake --install $buildDir --config Release
    if ($LASTEXITCODE -ne 0) { throw "install failed for $ts" }

    # ── vendor libs ──
    $dst = Join-Path $repoArrow $ts
    New-Item -ItemType Directory -Force $dst | Out-Null
    Copy-Item (Join-Path $installDir "lib\*.lib") $dst -Force
    # arrow_bundled_dependencies.lib (zstd/thrift/…) is not always installed — take it from the build tree.
    $bundled = Get-ChildItem -Recurse (Join-Path $buildDir "Release") -Filter "arrow_bundled_dependencies.lib" -ErrorAction SilentlyContinue | Select-Object -First 1
    if ($null -eq $bundled) {
        $bundled = Get-ChildItem -Recurse $buildDir -Filter "arrow_bundled_dependencies.lib" -ErrorAction SilentlyContinue | Select-Object -First 1
    }
    if ($null -ne $bundled) { Copy-Item $bundled.FullName $dst -Force }
    # The raw static libs are ~300 MB per toolset but compress ~9:1 — the repo vendors
    # the ZIP; CMake extracts it next to the zip at configure time (dir is gitignored).
    Compress-Archive -Path "$dst\*" -DestinationPath (Join-Path $repoArrow "$ts.zip") -CompressionLevel Optimal -Force
    Write-Host "Vendored libs -> $dst (+ $ts.zip)"
}

# ── vendor headers (toolset-independent, once) ──
$incSrc = Join-Path $WorkDir ("install_" + $Toolsets[0] + "\include")
$incDst = Join-Path $repoArrow "include"
if (Test-Path $incDst) { Remove-Item -Recurse -Force $incDst }
Copy-Item -Recurse $incSrc $incDst
Set-Content -Encoding utf8 (Join-Path $repoArrow "ARROW_VERSION.txt") "$ArrowVersion (static, Parquet+ZSTD+IPC minimal; /Zc:wchar_t- /MD IDL=0 C++20; built by build_arrow.ps1)"
Write-Host "Done. Vendored include/ + $($Toolsets -join ', ') under Libs/arrow/."
