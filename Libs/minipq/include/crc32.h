// CRC-32 (zlib polynomial, reflected) — the checksum parquet page headers carry.
// Shared by the minipq writer (emit) and reader (verify). Table-based, no deps.
#pragma once
#include <cstdint>
#include <cstddef>

namespace minipq {

inline uint32_t crc32(const void* data, size_t n, uint32_t seed = 0) {
  static const auto table = [] {
    struct T { uint32_t t[256]; };
    T t{};
    for (uint32_t i = 0; i < 256; ++i) {
      uint32_t c = i;
      for (int k = 0; k < 8; ++k) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
      t.t[i] = c;
    }
    return t;
  }();
  uint32_t c = seed ^ 0xFFFFFFFFu;
  const uint8_t* p = (const uint8_t*)data;
  for (size_t i = 0; i < n; ++i) c = table.t[(c ^ p[i]) & 0xFF] ^ (c >> 8);
  return c ^ 0xFFFFFFFFu;
}

}  // namespace minipq
