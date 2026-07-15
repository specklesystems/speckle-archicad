// SGEO v1 mesh codec + CRC32 + SHA256 — port of Speckle.Objects SgeoEncoder.EncodeMesh /
// SgeoFormat, extended with the archicad producer's colors flag and the decoder.
// Header (16B LE): "SGEO" | ver=1 | type=0(Mesh) | flags u16 | units u16 | reserved u16 | crc32 u32.
// Body: u32 vertexCount(=verts/3) | u32 faceCount(=faces.size) | f64 verts[] | i32 faces[]
//       | [i32 argb colors[vertexCount] when FLAG_HAS_COLORS].
// encodeMesh with no colors is byte-identical to the pre-consolidation converters encoder
// (flags=0) — the snowden md5 baseline depends on that.
#pragma once
#include "units.h"

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>

namespace sgeo {

inline constexpr uint16_t FLAG_QUANTIZED = 1 << 0;
inline constexpr uint16_t FLAG_HAS_NORMALS = 1 << 4;
inline constexpr uint16_t FLAG_HAS_UVS = 1 << 5;
inline constexpr uint16_t FLAG_HAS_COLORS = 1 << 6;

// Units.GetEncodingFromUnit (SDK) — short unit string → uint16 code.
// Kept as a delegate so existing sgeo::unitsCode callers survive the units.h split.
inline uint16_t unitsCode(const std::string& u) { return units::code(u); }

// Canonical CRC-32 (IEEE 802.3, reflected poly 0xEDB88320) over the SGEO body — the
// standard CRC-32 (matches zlib.crc32 / System.IO.Hashing.Crc32). The whole stack uses
// this same polynomial — the managed SDK (Speckle.Objects/Utils/SgeoFormat.cs `Crc32`,
// whose SgeoDecoder verifies it) and the Python encoder (specklepy bundle/sgeo.py) — so
// SGEO blobs stay byte-for-byte identical across producers and the geometry `id` (SHA256
// of the blob, CRC bytes included) matches. (This replaced an earlier non-standard
// 0xEDB88820 quirk, changed in lockstep across all three producers; no persisted v1
// blobs depended on the old value, so no SGEO version bump was needed.)
inline uint32_t crc32(const uint8_t* p, size_t n) {
  static uint32_t tbl[256];
  static bool init = false;
  if (!init) {
    for (uint32_t i = 0; i < 256; i++) {
      uint32_t c = i;
      for (int k = 0; k < 8; k++) c = (c & 1) ? 0xEDB88320u ^ (c >> 1) : c >> 1;
      tbl[i] = c;
    }
    init = true;
  }
  uint32_t crc = 0xFFFFFFFFu;
  for (size_t i = 0; i < n; i++) crc = tbl[(crc ^ p[i]) & 0xFF] ^ (crc >> 8);
  return crc ^ 0xFFFFFFFFu;
}

// ── SHA-256 (compact, public-domain style) → lowercase hex ──
struct Sha256 {
  uint32_t h[8];
  uint64_t len = 0;
  uint8_t buf[64];
  size_t bl = 0;
  Sha256() {
    static const uint32_t iv[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372,
                                   0xa54ff53a, 0x510e527f, 0x9b05688c,
                                   0x1f83d9ab, 0x5be0cd19};
    memcpy(h, iv, sizeof iv);
  }
  static uint32_t ror(uint32_t x, int n) { return (x >> n) | (x << (32 - n)); }
  void block(const uint8_t* p) {
    static const uint32_t K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
        0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
        0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
        0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
        0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
        0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    uint32_t w[64];
    for (int i = 0; i < 16; i++)
      w[i] = (p[i * 4] << 24) | (p[i * 4 + 1] << 16) | (p[i * 4 + 2] << 8) |
             p[i * 4 + 3];
    for (int i = 16; i < 64; i++) {
      uint32_t s0 = ror(w[i - 15], 7) ^ ror(w[i - 15], 18) ^ (w[i - 15] >> 3),
               s1 = ror(w[i - 2], 17) ^ ror(w[i - 2], 19) ^ (w[i - 2] >> 10);
      w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }
    uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5],
             g = h[6], hh = h[7];
    for (int i = 0; i < 64; i++) {
      uint32_t S1 = ror(e, 6) ^ ror(e, 11) ^ ror(e, 25),
               ch = (e & f) ^ (~e & g), t1 = hh + S1 + ch + K[i] + w[i],
               S0 = ror(a, 2) ^ ror(a, 13) ^ ror(a, 22),
               maj = (a & b) ^ (a & c) ^ (b & c), t2 = S0 + maj;
      hh = g;
      g = f;
      f = e;
      e = d + t1;
      d = c;
      c = b;
      b = a;
      a = t1 + t2;
    }
    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
    h[5] += f;
    h[6] += g;
    h[7] += hh;
  }
  void update(const uint8_t* p, size_t n) {
    len += n;
    while (n) {
      size_t k = 64 - bl;
      if (k > n) k = n;
      memcpy(buf + bl, p, k);
      bl += k;
      p += k;
      n -= k;
      if (bl == 64) {
        block(buf);
        bl = 0;
      }
    }
  }
  std::string hex() {
    uint64_t bits = len * 8;
    uint8_t pad = 0x80;
    update(&pad, 1);
    uint8_t z = 0;
    while (bl != 56) update(&z, 1);
    uint8_t lb[8];
    for (int i = 0; i < 8; i++) lb[i] = (uint8_t)(bits >> (56 - i * 8));
    update(lb, 8);
    static const char* hx = "0123456789abcdef";
    std::string out;
    out.reserve(64);
    for (int i = 0; i < 8; i++)
      for (int j = 3; j >= 0; j--) {
        uint8_t b = (uint8_t)(h[i] >> (j * 8));
        out += hx[b >> 4];
        out += hx[b & 0xF];
      }
    return out;
  }
};

inline std::string sha256hex(const uint8_t* p, size_t n) {
  Sha256 s;
  s.update(p, n);
  return s.hex();
}
inline std::string sha256hex(const std::string& s) {
  return sha256hex((const uint8_t*)s.data(), s.size());
}

// Encode a mesh (flat verts xyz, flat faces [3,i,j,k,...], optional per-vertex ARGB
// colors) into an SGEO blob. With empty colors the output is byte-identical to the
// pre-consolidation converters encoder (flags=0); with colors it matches the archicad
// SgeoEncoder (FLAG_HAS_COLORS, colors appended after faces).
inline std::vector<uint8_t> encodeMesh(const std::vector<double>& verts,
                                       const std::vector<int32_t>& faces,
                                       uint16_t uc,
                                       const std::vector<int32_t>& colors =
                                           std::vector<int32_t>()) {
  if (verts.size() % 3 != 0)
    throw std::runtime_error("SGEO mesh: vertices length must be a multiple of 3");
  const uint16_t flags = colors.empty() ? 0 : FLAG_HAS_COLORS;
  std::vector<uint8_t> body;
  body.reserve(8 + verts.size() * 8 + faces.size() * 4 + colors.size() * 4);
  auto u32 = [&](uint32_t v) {
    for (int i = 0; i < 4; i++) body.push_back((uint8_t)(v >> (8 * i)));
  };
  auto i32 = [&](int32_t v) {
    for (int i = 0; i < 4; i++) body.push_back((uint8_t)(v >> (8 * i)));
  };
  auto f64 = [&](double v) {
    uint64_t b;
    memcpy(&b, &v, 8);
    for (int i = 0; i < 8; i++) body.push_back((uint8_t)(b >> (8 * i)));
  };
  u32((uint32_t)(verts.size() / 3));
  u32((uint32_t)faces.size());
  for (double v : verts) f64(v);
  for (int32_t f : faces) i32(f);
  for (int32_t c : colors) i32(c);

  std::vector<uint8_t> buf(16 + body.size(), 0);
  buf[0] = 'S';
  buf[1] = 'G';
  buf[2] = 'E';
  buf[3] = 'O';
  buf[4] = 1;
  buf[5] = 0;  // magic, ver, type=Mesh
  buf[6] = (uint8_t)(flags & 0xFF);
  buf[7] = (uint8_t)(flags >> 8);
  buf[8] = (uint8_t)(uc & 0xFF);
  buf[9] = (uint8_t)(uc >> 8);  // units
  buf[10] = 0;
  buf[11] = 0;  // reserved
  memcpy(buf.data() + 16, body.data(), body.size());
  uint32_t crc = crc32(body.data(), body.size());
  buf[12] = (uint8_t)(crc & 0xFF);
  buf[13] = (uint8_t)((crc >> 8) & 0xFF);
  buf[14] = (uint8_t)((crc >> 16) & 0xFF);
  buf[15] = (uint8_t)((crc >> 24) & 0xFF);
  return buf;
}

// ── decoder (ported from the archicad SgeoDecoder; mirrors the SDK decoder) ──

struct DecodedMesh {
  std::vector<double> vertices;  // flat xyz
  std::vector<int32_t> faces;    // [3, i, j, k, ...]
  std::string units;
};

// Decode an SGEO blob into verts/faces/units. Returns false for non-mesh primitives
// and quantized payloads (unsupported); throws on structural corruption (short buffer,
// magic/version/CRC mismatch, truncated body). Normals/uvs are skipped with the SDK's
// 8-byte-alignment rule; trailing colors are ignored.
inline bool decodeMesh(const uint8_t* data, size_t length, DecodedMesh& mesh) {
  constexpr size_t kHeader = 16;
  if (length < kHeader)
    throw std::runtime_error("SGEO buffer too small to contain a header");
  if (memcmp(data, "SGEO", 4) != 0)
    throw std::runtime_error("SGEO magic mismatch");
  if (data[4] != 1)
    throw std::runtime_error("SGEO version " + std::to_string(data[4]) +
                             " unsupported");

  const uint8_t primitiveType = data[5];
  uint16_t flags;
  memcpy(&flags, data + 6, 2);
  uint16_t uc;
  memcpy(&uc, data + 8, 2);
  uint32_t crc;
  memcpy(&crc, data + 12, 4);

  if (crc32(data + kHeader, length - kHeader) != crc)
    throw std::runtime_error("SGEO CRC mismatch");
  if (primitiveType != 0 /*Mesh*/ || (flags & FLAG_QUANTIZED) != 0) return false;

  // Cursor over the little-endian body (incl. the SDK's Align8 rule for f64 arrays).
  size_t pos = kHeader;
  auto ensure = [&](size_t bytes) {
    if (pos + bytes > length) throw std::runtime_error("SGEO buffer truncated");
  };
  auto u = [&]() {
    ensure(4);
    uint32_t v;
    memcpy(&v, data + pos, 4);
    pos += 4;
    return v;
  };

  const uint32_t vCount = u();
  const uint32_t fCount = u();

  mesh.units = units::fromCode(uc);
  mesh.vertices.resize((size_t)vCount * 3);
  ensure(mesh.vertices.size() * 8);
  memcpy(mesh.vertices.data(), data + pos, mesh.vertices.size() * 8);
  pos += mesh.vertices.size() * 8;
  mesh.faces.resize(fCount);
  ensure((size_t)fCount * 4);
  memcpy(mesh.faces.data(), data + pos, (size_t)fCount * 4);
  pos += (size_t)fCount * 4;

  if ((flags & FLAG_HAS_NORMALS) != 0) {
    pos = (pos + 7) & ~(size_t)7;
    ensure((size_t)vCount * 3 * 8);
    pos += (size_t)vCount * 3 * 8;
  }
  if ((flags & FLAG_HAS_UVS) != 0) {
    pos = (pos + 7) & ~(size_t)7;
    ensure((size_t)vCount * 2 * 8);
    pos += (size_t)vCount * 2 * 8;
  }
  // FLAG_HAS_COLORS payload trails; current consumers don't read it.

  return true;
}

}  // namespace sgeo
