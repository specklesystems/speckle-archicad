// LOCAL ADDITION (not from upstream speckle-converters) — see README.md.
// UTF-8-safe file IO: the CRT's narrow fopen/_stat64 interpret paths in the
// ANSI codepage, but bundle paths live under %TEMP%/%APPDATA% which may be
// non-ASCII. Convert UTF-8 -> wide via std::filesystem and use the wide CRT
// functions on Windows.
#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <string>

namespace minipq {

inline std::filesystem::path utf8Path(const std::string& utf8) {
  return std::filesystem::path(std::u8string(utf8.begin(), utf8.end()));
}

inline FILE* openUtf8(const std::string& utf8, const char* mode) {
#ifdef _WIN32
  std::wstring wmode(mode, mode + std::strlen(mode));
  FILE* f = nullptr;
  return _wfopen_s(&f, utf8Path(utf8).c_str(), wmode.c_str()) == 0 ? f : nullptr;
#else
  return std::fopen(utf8.c_str(), mode);
#endif
}

inline int64_t fileSizeUtf8(const std::string& utf8) {
  std::error_code ec;
  const auto size = std::filesystem::file_size(utf8Path(utf8), ec);
  return ec ? -1 : (int64_t)size;
}

}  // namespace minipq
