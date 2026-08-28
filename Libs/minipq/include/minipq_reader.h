// minipq reader — the read-side twin of minipq.h, sized to the bundle subset:
// flat schemas of {bool,int32,int64,double,byte_array}, V1 data pages, ZSTD (or
// uncompressed), encodings PLAIN / DELTA_BINARY_PACKED(i32) / RLE_DICTIONARY /
// PLAIN_DICTIONARY, RLE def levels. Reads both minipq-written files (one page per
// chunk, no stats) and parquet-cpp-written ones (1MB pages, stats/CRC skipped).
//
// Batch = one row group, decoded into row-indexed typed columns. API mirrors the
// arrow accessors bundle_merge used (Value / IsNull / GetView) so the port is
// mechanical. Unsupported features (nested, V2 pages, other codecs, INT96/FLOAT)
// fail loudly via ok()/good, never silently.
#pragma once
#include <zstd.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <string_view>
#include <vector>

#include "crc32.h"
#include "minipq_io.h"  // LOCAL: UTF-8-safe fopen (see README.md)

namespace minipq {

namespace rdetail {

// ── thrift compact-protocol reader (with skip for unknown fields) ─────────────
struct TR {
  const uint8_t* p;
  const uint8_t* end;
  bool ok = true;

  uint8_t byte() {
    if (p >= end) { ok = false; return 0; }
    return *p++;
  }
  uint64_t uvarint() {
    uint64_t r = 0;
    int s = 0;
    while (true) {
      uint8_t x = byte();
      r |= (uint64_t)(x & 0x7f) << s;
      if (!(x & 0x80)) return r;
      s += 7;
      if (s > 63) { ok = false; return 0; }
    }
  }
  int64_t zig() {
    uint64_t u = uvarint();
    return (int64_t)(u >> 1) ^ -(int64_t)(u & 1);
  }
  std::string_view binary() {
    uint64_t n = uvarint();
    if ((uint64_t)(end - p) < n) { ok = false; return {}; }
    std::string_view v((const char*)p, (size_t)n);
    p += n;
    return v;
  }
  // field header: returns false on STOP. type out; fid tracked via lastId.
  bool fieldHeader(int16_t& lastId, int16_t& fid, uint8_t& type) {
    uint8_t h = byte();
    if (h == 0 || !ok) return false;
    uint8_t delta = h >> 4;
    type = h & 0xf;
    fid = delta ? (int16_t)(lastId + delta) : (int16_t)zig();
    lastId = fid;
    return true;
  }
  void skip(uint8_t type) {
    switch (type) {
      case 1: case 2: break;              // bool folded into type
      case 3: byte(); break;              // byte
      case 4: case 5: case 6: zig(); break;
      case 7: p += 8; break;              // double
      case 8: binary(); break;
      case 9: case 10: {                  // list/set
        uint8_t h = byte();
        uint64_t n = (h >> 4) == 0xf ? uvarint() : (h >> 4);
        for (uint64_t i = 0; i < n && ok; ++i) skip(h & 0xf);
        break;
      }
      case 11: {                          // map
        uint64_t n = uvarint();
        if (n) {
          uint8_t kv = byte();
          for (uint64_t i = 0; i < n && ok; ++i) { skip(kv >> 4); skip(kv & 0xf); }
        }
        break;
      }
      case 12: {                          // struct
        int16_t last = 0, fid;
        uint8_t t;
        while (ok && fieldHeader(last, fid, t)) skip(t);
        break;
      }
      default: ok = false;
    }
    if (p > end) ok = false;
  }
  // list header for a field we DO read
  uint64_t listHeader(uint8_t& elemType) {
    uint8_t h = byte();
    elemType = h & 0xf;
    return (h >> 4) == 0xf ? uvarint() : (h >> 4);
  }
};

// RLE / bit-packed hybrid decoder → appends exactly n values.
inline bool decodeHybrid(const uint8_t* b, size_t len, int bw, size_t n,
                         std::vector<uint32_t>& out) {
  size_t i = 0;
  int vb = (bw + 7) / 8;
  uint32_t mask = bw >= 32 ? 0xffffffffu : ((1u << bw) - 1);
  while (out.size() < n) {
    if (i >= len) return false;
    uint64_t h = 0;
    int s = 0;
    while (true) {
      if (i >= len) return false;
      uint8_t x = b[i++];
      h |= (uint64_t)(x & 0x7f) << s;
      s += 7;
      if (!(x & 0x80)) break;
    }
    if (h & 1) {  // bit-packed groups
      size_t cnt = (size_t)(h >> 1) * 8;
      size_t nbytes = (cnt * bw + 7) / 8;
      if (i + nbytes > len) return false;
      uint64_t acc = 0;
      int bits = 0;
      size_t bi = i;
      for (size_t k = 0; k < cnt; ++k) {
        while (bits < bw) {
          acc |= (uint64_t)b[bi++] << bits;
          bits += 8;
        }
        if (out.size() < n) out.push_back((uint32_t)(acc & mask));
        acc >>= bw;
        bits -= bw;
      }
      i += nbytes;
    } else {  // RLE run
      if (i + vb > len) return false;
      uint32_t v = 0;
      for (int k = 0; k < vb; ++k) v |= (uint32_t)b[i++] << (8 * k);
      size_t cnt = (size_t)(h >> 1);
      for (size_t k = 0; k < cnt && out.size() < n; ++k) out.push_back(v & mask);
    }
  }
  return true;
}

// DELTA_BINARY_PACKED int32 → appends exactly n values (wrapping arithmetic).
inline bool decodeDeltaI32(const uint8_t* b, size_t len, size_t n,
                           std::vector<int32_t>& out) {
  size_t i = 0;
  auto uvar = [&](uint64_t& v) {
    v = 0;
    int s = 0;
    while (true) {
      if (i >= len) return false;
      uint8_t x = b[i++];
      v |= (uint64_t)(x & 0x7f) << s;
      s += 7;
      if (!(x & 0x80)) return true;
    }
  };
  auto zig32 = [&](int32_t& v) {
    uint64_t u;
    if (!uvar(u)) return false;
    v = (int32_t)((uint32_t)(u >> 1) ^ (uint32_t)(-(int64_t)(u & 1)));
    return true;
  };
  uint64_t blockSize, nMini, total;
  int32_t first;
  if (!uvar(blockSize) || !uvar(nMini) || !uvar(total) || !zig32(first))
    return false;
  if (nMini == 0 || blockSize % nMini || (blockSize / nMini) % 8) return false;
  size_t miniVals = (size_t)(blockSize / nMini);
  if (n == 0) return true;
  out.push_back(first);
  uint32_t cur = (uint32_t)first;
  size_t remaining = (total > 0 ? (size_t)total - 1 : 0);
  std::vector<uint8_t> bws(nMini);
  while (out.size() < n && remaining > 0) {
    int32_t minD;
    if (!zig32(minD)) return false;
    if (i + nMini > len) return false;
    for (size_t m = 0; m < nMini; ++m) bws[m] = b[i++];
    for (size_t m = 0; m < nMini && remaining > 0; ++m) {
      int bw = bws[m];
      uint64_t acc = 0;
      int bits = 0;
      size_t nbytes = (miniVals * bw + 7) / 8;
      if (i + nbytes > len) return false;
      size_t bi = i;
      for (size_t k = 0; k < miniVals; ++k) {
        uint32_t adj = 0;
        if (bw) {
          while (bits < bw) {
            acc |= (uint64_t)b[bi++] << bits;
            bits += 8;
          }
          adj = (uint32_t)(acc & (bw >= 32 ? 0xffffffffu : ((1u << bw) - 1)));
          acc >>= bw;
          bits -= bw;
        }
        if (remaining > 0) {
          cur += (uint32_t)minD + adj;  // wrapping
          if (out.size() < n) out.push_back((int32_t)cur);
          --remaining;
        }
      }
      i += nbytes;
    }
  }
  return out.size() >= n;
}

}  // namespace rdetail

// ── decoded column (row-indexed; nulls hold defaults) ─────────────────────────
struct RCol {
  int pqtype = -1;  // parquet Type enum: 0 bool, 1 i32, 2 i64, 5 f64, 6 bytes
  std::vector<uint8_t> def;
  std::vector<int32_t> vi32;
  std::vector<int64_t> vi64;
  std::vector<double> vf64;
  std::vector<uint8_t> vb1;
  std::string arena;
  std::vector<uint64_t> offs;  // rows+1 offsets into arena
};

// Typed accessor views, mirroring the arrow array API bundle_merge used.
struct Int32Arr {
  const RCol* c;
  bool IsNull(int64_t i) const { return !c->def[(size_t)i]; }
  int32_t Value(int64_t i) const { return c->vi32[(size_t)i]; }
};
struct Int64Arr {
  const RCol* c;
  bool IsNull(int64_t i) const { return !c->def[(size_t)i]; }
  int64_t Value(int64_t i) const { return c->vi64[(size_t)i]; }
};
struct DoubleArr {
  const RCol* c;
  bool IsNull(int64_t i) const { return !c->def[(size_t)i]; }
  double Value(int64_t i) const { return c->vf64[(size_t)i]; }
};
struct BoolArr {
  const RCol* c;
  bool IsNull(int64_t i) const { return !c->def[(size_t)i]; }
  bool Value(int64_t i) const { return c->vb1[(size_t)i] != 0; }
};
struct BytesArr {  // utf8 + binary
  const RCol* c;
  bool IsNull(int64_t i) const { return !c->def[(size_t)i]; }
  std::string_view GetView(int64_t i) const {
    return {c->arena.data() + c->offs[(size_t)i],
            (size_t)(c->offs[(size_t)i + 1] - c->offs[(size_t)i])};
  }
};

struct Batch {
  int64_t rows = 0;
  std::vector<RCol> cols;
  int64_t num_rows() const { return rows; }
};

inline Int32Arr i32(const Batch& b, int c) { return {&b.cols[(size_t)c]}; }
inline Int64Arr i64(const Batch& b, int c) { return {&b.cols[(size_t)c]}; }
inline DoubleArr f64(const Batch& b, int c) { return {&b.cols[(size_t)c]}; }
inline BoolArr b1(const Batch& b, int c) { return {&b.cols[(size_t)c]}; }
inline BytesArr bytes(const Batch& b, int c) { return {&b.cols[(size_t)c]}; }

// ── the reader ─────────────────────────────────────────────────────────────────
class Reader {
 public:
  bool good = false;

  explicit Reader(const std::string& path) : path_(path) {
    f_ = openUtf8(path, "rb");  // LOCAL: was fopen (ANSI codepage on Windows)
    if (!f_) { err("open"); return; }
    dctx_ = ZSTD_createDCtx();
    if (!parseFooter()) { err("footer"); return; }
    good = true;
  }
  ~Reader() {
    if (f_) fclose(f_);
    if (dctx_) ZSTD_freeDCtx(dctx_);
  }
  Reader(const Reader&) = delete;

  int numColumns() const { return (int)types_.size(); }
  int64_t totalRows() const { return totalRows_; }
  const std::vector<std::string>& columnNames() const { return names_; }

  // Decode the next row group into `out`. Returns false at EOF or error (check good).
  bool next(Batch& out) {
    if (!good || nextRg_ >= rgs_.size()) return false;
    const RgInfo& rg = rgs_[nextRg_++];
    out.rows = rg.rows;
    out.cols.assign(types_.size(), {});
    for (size_t c = 0; c < types_.size(); ++c) {
      curOptional_ = !required_[c];
      if (!readChunk(rg.chunks[c], rg.rows, out.cols[c])) {
        good = false;
        err(("chunk col " + std::to_string(c)).c_str());
        return false;
      }
    }
    return true;
  }

 private:
  // parquet.thrift constants
  enum { T_BOOL = 0, T_I32 = 1, T_I64 = 2, T_I96 = 3, T_F32 = 4, T_F64 = 5, T_BA = 6 };
  enum { E_PLAIN = 0, E_PLAIN_DICT = 2, E_RLE = 3, E_DELTA_BP = 5, E_RLE_DICT = 8 };
  enum { C_UNCOMPRESSED = 0, C_ZSTD = 6 };
  enum { P_DATA = 0, P_DICT = 2, P_DATA_V2 = 3 };

  struct ChunkInfo {
    int type = -1, codec = -1;
    int64_t numValues = 0, dataOff = 0, dictOff = -1, compSize = 0;
  };
  struct RgInfo {
    int64_t rows = 0;
    std::vector<ChunkInfo> chunks;
  };

  void err(const char* what) {
    fprintf(stderr, "minipq reader [%s]: %s\n", path_.c_str(), what);
  }

  bool readAt(int64_t off, size_t n, std::string& buf) {
    buf.resize(n);
#ifdef _WIN32
    if (_fseeki64(f_, off, SEEK_SET)) return false;
#else
    if (fseeko(f_, off, SEEK_SET)) return false;
#endif
    return fread(buf.data(), 1, n, f_) == n;
  }

  bool parseFooter() {
#ifdef _WIN32
    _fseeki64(f_, 0, SEEK_END);
    int64_t fsz = _ftelli64(f_);
#else
    fseeko(f_, 0, SEEK_END);
    int64_t fsz = ftello(f_);
#endif
    std::string tail;
    if (fsz < 12 || !readAt(fsz - 8, 8, tail)) return false;
    if (memcmp(tail.data() + 4, "PAR1", 4) != 0) return false;
    uint32_t flen;
    memcpy(&flen, tail.data(), 4);
    if ((int64_t)flen + 12 > fsz) return false;
    std::string fbuf;
    if (!readAt(fsz - 8 - (int64_t)flen, flen, fbuf)) return false;

    rdetail::TR r{(const uint8_t*)fbuf.data(),
                  (const uint8_t*)fbuf.data() + fbuf.size()};
    int16_t last = 0, fid;
    uint8_t t;
    while (r.ok && r.fieldHeader(last, fid, t)) {
      if (fid == 2 && t == 9) {  // schema
        uint8_t et;
        uint64_t n = r.listHeader(et);
        for (uint64_t i = 0; i < n && r.ok; ++i) {
          // SchemaElement
          int16_t l2 = 0, f2;
          uint8_t t2;
          int type = -1, numCh = 0;
          bool required = false;
          while (r.ok && r.fieldHeader(l2, f2, t2)) {
            if (f2 == 1) type = (int)r.zig();
            else if (f2 == 3) required = (r.zig() == 0);
            else if (f2 == 4) names_.emplace_back(r.binary());
            else if (f2 == 5) numCh = (int)r.zig();
            else r.skip(t2);
          }
          if (i == 0) {
            names_.clear();  // root's name isn't a column
            continue;
          }
          if (numCh > 0) return false;  // nested: unsupported
          if (type == T_I96 || type == T_F32) return false;
          types_.push_back(type);
          required_.push_back(required);
        }
      } else if (fid == 3 && t == 6) {
        totalRows_ = r.zig();
      } else if (fid == 4 && t == 9) {  // row groups
        uint8_t et;
        uint64_t n = r.listHeader(et);
        for (uint64_t g = 0; g < n && r.ok; ++g) {
          RgInfo rg;
          int16_t l2 = 0, f2;
          uint8_t t2;
          while (r.ok && r.fieldHeader(l2, f2, t2)) {
            if (f2 == 1 && t2 == 9) {  // ColumnChunk list
              uint8_t et3;
              uint64_t nc = r.listHeader(et3);
              for (uint64_t ci = 0; ci < nc && r.ok; ++ci) {
                ChunkInfo ck;
                int16_t l3 = 0, f3;
                uint8_t t3;
                while (r.ok && r.fieldHeader(l3, f3, t3)) {
                  if (f3 == 3 && t3 == 12) {  // ColumnMetaData
                    int16_t l4 = 0, f4;
                    uint8_t t4;
                    while (r.ok && r.fieldHeader(l4, f4, t4)) {
                      switch (f4) {
                        case 1: ck.type = (int)r.zig(); break;
                        case 4: ck.codec = (int)r.zig(); break;
                        case 5: ck.numValues = r.zig(); break;
                        case 7: ck.compSize = r.zig(); break;
                        case 9: ck.dataOff = r.zig(); break;
                        case 11: ck.dictOff = r.zig(); break;
                        default: r.skip(t4);
                      }
                    }
                  } else {
                    r.skip(t3);
                  }
                }
                rg.chunks.push_back(ck);
              }
            } else if (f2 == 3 && t2 == 6) {
              rg.rows = r.zig();
            } else {
              r.skip(t2);
            }
          }
          rgs_.push_back(std::move(rg));
        }
      } else {
        r.skip(t);
      }
    }
    if (!r.ok || types_.empty() || names_.size() != types_.size()) return false;
    for (auto& rg : rgs_)
      if (rg.chunks.size() != types_.size()) return false;
    return true;
  }

  bool inflate(const std::string& src, size_t off, size_t comp, size_t uncomp,
               int codec, std::string& dst) {
    if (codec == C_UNCOMPRESSED) {
      dst.assign(src, off, comp);
      return comp == uncomp;
    }
    if (codec != C_ZSTD) return false;
    dst.resize(uncomp);
    size_t got = ZSTD_decompressDCtx(dctx_, dst.data(), uncomp, src.data() + off, comp);
    return !ZSTD_isError(got) && got == uncomp;
  }

  bool readChunk(const ChunkInfo& ck, int64_t rgRows, RCol& col) {
    col.pqtype = ck.type;
    col.def.reserve((size_t)rgRows);
    int64_t start = ck.dictOff >= 0 && ck.dictOff < ck.dataOff ? ck.dictOff : ck.dataOff;
    std::string buf;
    if (!readAt(start, (size_t)ck.compSize, buf)) return false;

    // dictionary storage (decoded on demand)
    std::vector<int32_t> di32;
    std::vector<int64_t> di64;
    std::vector<double> df64;
    std::vector<std::string_view> dbytes;
    std::string dictArena;

    size_t pos = 0;
    int64_t rowsDone = 0;
    std::string page;
    while (rowsDone < ck.numValues) {
      // ── page header ──
      rdetail::TR r{(const uint8_t*)buf.data() + pos,
                    (const uint8_t*)buf.data() + buf.size()};
      int ptype = -1, uncomp = 0, comp = 0, pvals = 0, penc = -1;
      bool hasCrc = false;
      uint32_t crc = 0;
      int16_t last = 0, fid;
      uint8_t t;
      while (r.ok && r.fieldHeader(last, fid, t)) {
        switch (fid) {
          case 1: ptype = (int)r.zig(); break;
          case 2: uncomp = (int)r.zig(); break;
          case 3: comp = (int)r.zig(); break;
          case 4: crc = (uint32_t)r.zig(); hasCrc = true; break;
          case 5:
          case 7: {  // data_page_header / dictionary_page_header
            int16_t l2 = 0, f2;
            uint8_t t2;
            while (r.ok && r.fieldHeader(l2, f2, t2)) {
              if (f2 == 1) pvals = (int)r.zig();
              else if (f2 == 2) penc = (int)r.zig();
              else r.skip(t2);
            }
            break;
          }
          default: r.skip(t);
        }
      }
      if (!r.ok) return false;
      size_t headLen = (size_t)(r.p - ((const uint8_t*)buf.data() + pos));
      pos += headLen;
      if (pos + (size_t)comp > buf.size()) return false;
      if (hasCrc) {
        uint32_t got = crc32(buf.data() + pos, (size_t)comp);
        if (got != crc) {
          fprintf(stderr,
                  "minipq reader [%s]: PAGE CRC MISMATCH (stored %08x, computed "
                  "%08x) — file is corrupt\n",
                  path_.c_str(), crc, got);
          return false;
        }
      }
      if (!inflate(buf, pos, (size_t)comp, (size_t)uncomp,
                   ck.codec, page))
        return false;
      pos += (size_t)comp;

      if (ptype == P_DICT) {
        if (penc != E_PLAIN && penc != E_PLAIN_DICT) return false;
        const char* d = page.data();
        size_t n = page.size();
        switch (ck.type) {
          case T_I32:
            di32.resize(pvals);
            if (n < (size_t)pvals * 4) return false;
            memcpy(di32.data(), d, (size_t)pvals * 4);
            break;
          case T_I64:
            di64.resize(pvals);
            if (n < (size_t)pvals * 8) return false;
            memcpy(di64.data(), d, (size_t)pvals * 8);
            break;
          case T_F64:
            df64.resize(pvals);
            if (n < (size_t)pvals * 8) return false;
            memcpy(df64.data(), d, (size_t)pvals * 8);
            break;
          case T_BA: {
            dictArena = std::move(page);
            page = std::string();
            size_t off2 = 0;
            for (int k = 0; k < pvals; ++k) {
              if (off2 + 4 > dictArena.size()) return false;
              uint32_t L;
              memcpy(&L, dictArena.data() + off2, 4);
              off2 += 4;
              if (off2 + L > dictArena.size()) return false;
              dbytes.emplace_back(dictArena.data() + off2, L);
              off2 += L;
            }
            break;
          }
          default: return false;
        }
        continue;
      }
      if (ptype != P_DATA) return false;  // V2 / index pages: unsupported

      // ── def levels (present only for OPTIONAL leaves) ──
      size_t off = 0;
      std::vector<uint32_t> defs;
      if (curOptional_) {
        if (off + 4 > page.size()) return false;
        uint32_t dlLen;
        memcpy(&dlLen, page.data() + off, 4);
        off += 4;
        if (off + dlLen > page.size()) return false;
        if (!rdetail::decodeHybrid((const uint8_t*)page.data() + off, dlLen, 1,
                                   (size_t)pvals, defs))
          return false;
        off += dlLen;
      } else {
        defs.assign((size_t)pvals, 1);
      }
      size_t defined = 0;
      for (size_t k = 0; k < (size_t)pvals; ++k) defined += defs[k];

      // ── values ──
      const uint8_t* vp = (const uint8_t*)page.data() + off;
      size_t vlen = page.size() - off;
      if (penc == E_PLAIN) {
        if (!appendPlain(col, vp, vlen, defs, defined)) return false;
      } else if (penc == E_RLE_DICT || penc == E_PLAIN_DICT) {
        if (!vlen) return false;
        int bw = vp[0];
        std::vector<uint32_t> idx;
        idx.reserve(defined);
        if (!rdetail::decodeHybrid(vp + 1, vlen - 1, bw, defined, idx)) return false;
        if (!appendDict(col, idx, defs, di32, di64, df64, dbytes)) return false;
      } else if (penc == E_DELTA_BP) {
        if (ck.type != T_I32) return false;
        std::vector<int32_t> vals;
        vals.reserve(defined);
        if (!rdetail::decodeDeltaI32(vp, vlen, defined, vals)) return false;
        size_t vi = 0;
        for (size_t k = 0; k < (size_t)pvals; ++k) {
          col.def.push_back((uint8_t)defs[k]);
          col.vi32.push_back(defs[k] ? vals[vi++] : 0);
        }
      } else {
        return false;
      }
      rowsDone += pvals;
    }
    if (ck.type == T_BA) {
      // offs built incrementally by appenders; ensure rows+1 sentinel
      if (col.offs.size() != (size_t)rowsDone + 1) return false;
    }
    return rowsDone == ck.numValues;
  }

  bool appendPlain(RCol& col, const uint8_t* vp, size_t vlen,
                   const std::vector<uint32_t>& defs, size_t defined) {
    size_t vi = 0;
    switch (col.pqtype) {
      case T_I32: {
        if (vlen < defined * 4) return false;
        for (auto dfl : defs) {
          col.def.push_back((uint8_t)dfl);
          int32_t v = 0;
          if (dfl) { memcpy(&v, vp + vi * 4, 4); ++vi; }
          col.vi32.push_back(v);
        }
        break;
      }
      case T_I64: {
        if (vlen < defined * 8) return false;
        for (auto dfl : defs) {
          col.def.push_back((uint8_t)dfl);
          int64_t v = 0;
          if (dfl) { memcpy(&v, vp + vi * 8, 8); ++vi; }
          col.vi64.push_back(v);
        }
        break;
      }
      case T_F64: {
        if (vlen < defined * 8) return false;
        for (auto dfl : defs) {
          col.def.push_back((uint8_t)dfl);
          double v = 0;
          if (dfl) { memcpy(&v, vp + vi * 8, 8); ++vi; }
          col.vf64.push_back(v);
        }
        break;
      }
      case T_BOOL: {
        if (vlen < (defined + 7) / 8) return false;
        for (auto dfl : defs) {
          col.def.push_back((uint8_t)dfl);
          uint8_t v = 0;
          if (dfl) { v = (vp[vi / 8] >> (vi % 8)) & 1; ++vi; }
          col.vb1.push_back(v);
        }
        break;
      }
      case T_BA: {
        if (col.offs.empty()) col.offs.push_back(0);
        size_t off = 0;
        for (auto dfl : defs) {
          col.def.push_back((uint8_t)dfl);
          if (dfl) {
            if (off + 4 > vlen) return false;
            uint32_t L;
            memcpy(&L, vp + off, 4);
            off += 4;
            if (off + L > vlen) return false;
            col.arena.append((const char*)vp + off, L);
            off += L;
          }
          col.offs.push_back(col.arena.size());
        }
        break;
      }
      default: return false;
    }
    return true;
  }

  bool appendDict(RCol& col, const std::vector<uint32_t>& idx,
                  const std::vector<uint32_t>& defs, std::vector<int32_t>& di32,
                  std::vector<int64_t>& di64, std::vector<double>& df64,
                  std::vector<std::string_view>& dbytes) {
    size_t vi = 0;
    switch (col.pqtype) {
      case T_I32:
        for (auto dfl : defs) {
          col.def.push_back((uint8_t)dfl);
          if (dfl) { if (idx[vi] >= di32.size()) return false; col.vi32.push_back(di32[idx[vi++]]); }
          else col.vi32.push_back(0);
        }
        break;
      case T_I64:
        for (auto dfl : defs) {
          col.def.push_back((uint8_t)dfl);
          if (dfl) { if (idx[vi] >= di64.size()) return false; col.vi64.push_back(di64[idx[vi++]]); }
          else col.vi64.push_back(0);
        }
        break;
      case T_F64:
        for (auto dfl : defs) {
          col.def.push_back((uint8_t)dfl);
          if (dfl) { if (idx[vi] >= df64.size()) return false; col.vf64.push_back(df64[idx[vi++]]); }
          else col.vf64.push_back(0);
        }
        break;
      case T_BA:
        if (col.offs.empty()) col.offs.push_back(0);
        for (auto dfl : defs) {
          col.def.push_back((uint8_t)dfl);
          if (dfl) {
            if (idx[vi] >= dbytes.size()) return false;
            auto v = dbytes[idx[vi++]];
            col.arena.append(v.data(), v.size());
          }
          col.offs.push_back(col.arena.size());
        }
        break;
      default: return false;
    }
    return true;
  }

  std::string path_;
  FILE* f_ = nullptr;
  ZSTD_DCtx* dctx_ = nullptr;
  std::vector<std::string> names_;
  std::vector<int> types_;
  std::vector<bool> required_;
  std::vector<RgInfo> rgs_;
  size_t nextRg_ = 0;
  int64_t totalRows_ = 0;
  // per-column flag set by next() before each readChunk (def-level presence)
  bool curOptional_ = true;
};

}  // namespace minipq
