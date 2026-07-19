// minipq — a minimal, dependency-free (zstd only) Parquet WRITER covering exactly
// the bundle subset: flat schemas, nullable {int32,int64,double,bool,utf8,binary},
// ZSTD compression, V1 data pages. Encodings: DELTA_BINARY_PACKED for int32,
// dictionary (PLAIN dict page + RLE_DICTIONARY data pages, plain fallback) for
// utf8/double, PLAIN for the rest — mirroring the PqTable/Arrow writer policy.
//
// POC replacement for parquet::arrow inside PqTable. No statistics, no nested
// types, no column/offset indexes — all optional per the format spec.
#pragma once
#include <sys/stat.h>
#include <zstd.h>

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "crc32.h"
#include "minipq_io.h"  // LOCAL: UTF-8-safe fopen/file-size (see README.md)
#include "thrift_compact.h"

namespace minipq {

enum class T { I32, I64, F64, BOOL, UTF8, BIN };

// Column encoding policy (decided per column at table-open, like WriterProperties).
enum class Enc {
  PLAIN,
  DELTA_I32,  // DELTA_BINARY_PACKED
  DICT,       // dictionary attempt with plain fallback per row group
};

struct Field {
  std::string name;
  T t;
  Enc enc;
};

// parquet.thrift enum values (wire constants — do not touch).
namespace pq {
enum Type { BOOLEAN = 0, INT32 = 1, INT64 = 2, DOUBLE = 5, BYTE_ARRAY = 6 };
enum Encoding {
  PLAIN = 0,
  RLE = 3,
  DELTA_BINARY_PACKED = 5,
  RLE_DICTIONARY = 8,
};
enum PageType { DATA_PAGE = 0, DICTIONARY_PAGE = 2 };
enum { CODEC_ZSTD = 6, REP_OPTIONAL = 1, CONV_UTF8 = 0 };
}  // namespace pq

inline int pqType(T t) {
  switch (t) {
    case T::I32: return pq::INT32;
    case T::I64: return pq::INT64;
    case T::F64: return pq::DOUBLE;
    case T::BOOL: return pq::BOOLEAN;
    default: return pq::BYTE_ARRAY;
  }
}

// ── low-level encoders ─────────────────────────────────────────────────────────

// RLE / bit-packed hybrid (parquet's levels + dictionary-index encoding).
// Whole-buffer greedy encoder: precompute run lengths, emit RLE for runs >= 8,
// bit-packed groups (exact multiples of 8 mid-stream, zero-padded only at the
// very end — the decoder stops at the page's value count) for the rest.
template <typename V>
inline std::string encodeRleHybrid(const V* v, size_t n, int bw) {
  std::string out;
  auto uvarint = [&](uint64_t x) {
    while (x >= 0x80) { out.push_back((char)(0x80 | (x & 0x7f))); x >>= 7; }
    out.push_back((char)x);
  };
  auto emitRle = [&](uint32_t val, size_t count) {
    uvarint((uint64_t)count << 1);
    for (int i = 0; i < (bw + 7) / 8; ++i)
      out.push_back((char)((val >> (8 * i)) & 0xff));
  };
  auto emitPacked = [&](size_t from, size_t to) {  // [from,to): multiple of 8, or tail
    size_t lit = to - from, padded = (lit + 7) & ~size_t(7);
    uvarint(((padded / 8) << 1) | 1);
    uint64_t acc = 0;
    int accBits = 0;
    uint32_t mask = bw >= 32 ? 0xffffffffu : ((1u << bw) - 1);
    for (size_t i = 0; i < padded; ++i) {
      uint32_t val = (from + i < to) ? ((uint32_t)v[from + i] & mask) : 0;
      acc |= (uint64_t)val << accBits;
      accBits += bw;
      while (accBits >= 8) {
        out.push_back((char)(acc & 0xff));
        acc >>= 8;
        accBits -= 8;
      }
    }
    if (accBits > 0) out.push_back((char)(acc & 0xff));
  };
  if (!n) return out;
  // run length at each index (backward pass)
  std::vector<uint32_t> rl(n);
  rl[n - 1] = 1;
  for (size_t i = n - 1; i-- > 0;)
    rl[i] = (v[i] == v[i + 1]) ? rl[i + 1] + 1 : 1;
  size_t i = 0;
  while (i < n) {
    if (rl[i] >= 8) {
      emitRle((uint32_t)v[i], rl[i]);
      i += rl[i];
    } else {
      // literals until an 8-aligned position that starts a long run, or the end
      size_t start = i;
      while (i < n && !(rl[i] >= 8 && (i - start) % 8 == 0)) ++i;
      emitPacked(start, i);
    }
  }
  return out;
}

// Definition levels for a flat nullable column: bit width 1, prefixed with the
// 4-byte LE length (data page V1 framing).
inline std::string encodeDefLevels(const uint8_t* defined, size_t n) {
  std::string rle = encodeRleHybrid(defined, n, 1);
  std::string out;
  uint32_t len = (uint32_t)rle.size();
  out.append((const char*)&len, 4);
  out.append(rle);
  return out;
}

inline int bitsFor(uint64_t v) {
  int b = 0;
  while (v) { ++b; v >>= 1; }
  return b ? b : 1;
}

// DELTA_BINARY_PACKED for int32 (wrapping 32-bit arithmetic, per parquet-mr).
// Block 128 values / 4 miniblocks of 32.
inline std::string encodeDeltaI32(const int32_t* v, size_t n) {
  std::string out;
  auto uvarint = [&](uint64_t x) {
    while (x >= 0x80) { out.push_back((char)(0x80 | (x & 0x7f))); x >>= 7; }
    out.push_back((char)x);
  };
  auto zz32 = [&](int32_t x) { uvarint(((uint32_t)x << 1) ^ (uint32_t)(x >> 31)); };
  uvarint(128);  // block size
  uvarint(4);    // miniblocks per block
  uvarint(n);    // total value count
  zz32(n ? v[0] : 0);  // first value
  if (n <= 1) return out;

  std::vector<int32_t> deltas(n - 1);
  for (size_t i = 1; i < n; ++i)
    deltas[i - 1] = (int32_t)((uint32_t)v[i] - (uint32_t)v[i - 1]);  // wrapping

  size_t pos = 0, total = deltas.size();
  while (pos < total) {
    size_t blockN = total - pos < 128 ? total - pos : 128;
    int32_t minD = deltas[pos];
    for (size_t i = 1; i < blockN; ++i)
      if (deltas[pos + i] < minD) minD = deltas[pos + i];
    zz32(minD);
    // per-miniblock bit widths (0 for miniblocks past the data)
    uint8_t bws[4] = {0, 0, 0, 0};
    uint32_t adj[128];
    for (size_t i = 0; i < blockN; ++i)
      adj[i] = (uint32_t)deltas[pos + i] - (uint32_t)minD;  // wrapping, >= 0
    for (int mb = 0; mb < 4; ++mb) {
      size_t s = mb * 32;
      if (s >= blockN) break;
      size_t e = s + 32 < blockN ? s + 32 : blockN;
      uint32_t mx = 0;
      for (size_t i = s; i < e; ++i)
        if (adj[i] > mx) mx = adj[i];
      bws[mb] = mx ? (uint8_t)bitsFor(mx) : 0;
    }
    for (int mb = 0; mb < 4; ++mb) out.push_back((char)bws[mb]);
    // miniblock payloads: bit-packed LSB-first, full 32 values (pad zeros)
    for (int mb = 0; mb < 4; ++mb) {
      size_t s = mb * 32;
      if (s >= blockN) break;  // trailing empty miniblocks: no data
      int bw = bws[mb];
      if (!bw) continue;
      uint64_t acc = 0;
      int accBits = 0;
      for (size_t i = 0; i < 32; ++i) {
        uint32_t val = (s + i < blockN) ? adj[s + i] : 0;
        acc |= (uint64_t)(bw >= 32 ? val : (val & ((1u << bw) - 1))) << accBits;
        accBits += bw;
        while (accBits >= 8) {
          out.push_back((char)(acc & 0xff));
          acc >>= 8;
          accBits -= 8;
        }
      }
      if (accBits > 0) out.push_back((char)(acc & 0xff));
    }
    pos += blockN;
  }
  return out;
}

// ── column buffer (one row group's worth of one column) ───────────────────────
struct ColBuf {
  T t;
  std::vector<uint8_t> defined;  // per ROW: 1 = value present
  // values are stored densely for non-null rows only:
  std::vector<int32_t> i32;
  std::vector<int64_t> i64;
  std::vector<double> f64;
  std::vector<uint8_t> b1;
  std::string arena;                // utf8/binary bytes
  std::vector<uint32_t> lens;       // utf8/binary per-value lengths
  size_t valueBytes = 0;            // arena growth tracker

  void clear() {
    defined.clear();
    i32.clear();
    i64.clear();
    f64.clear();
    b1.clear();
    arena.clear();
    lens.clear();
    valueBytes = 0;
  }
  size_t numValues() const {
    switch (t) {
      case T::I32: return i32.size();
      case T::I64: return i64.size();
      case T::F64: return f64.size();
      case T::BOOL: return b1.size();
      default: return lens.size();
    }
  }
};

// Per-column-chunk bookkeeping for the footer.
struct ChunkMeta {
  int64_t dataPageOffset = 0;
  int64_t dictPageOffset = -1;
  int64_t compressedSize = 0;
  int64_t uncompressedSize = 0;
  int64_t numValues = 0;  // rows incl nulls
  std::vector<int32_t> encodings;
  // Statistics — int32 index columns only (object/path/type K, node ids, rel
  // src/dst): min/max enables row-group pruning on the postpass-sorted eav.
  // String/double stats stay deliberately absent (that's where Arrow burned CPU).
  bool hasMinMax = false;
  int32_t minV = 0, maxV = 0;
  int64_t nullCount = -1;  // -1 = no statistics struct at all
};

struct RowGroupMeta {
  std::vector<ChunkMeta> chunks;
  int64_t numRows = 0;
};

// ── the writer ─────────────────────────────────────────────────────────────────
class Table {
 public:
  Table(const std::string& path, std::vector<Field> fields,
        int64_t flushRows = 200000, int64_t flushBytes = 0, int zstdLevel = 1)
      : path_(path),
        fields_(std::move(fields)),
        flushRows_(flushRows),
        flushBytes_(flushBytes),
        zstdLevel_(zstdLevel) {
    cols_.resize(fields_.size());
    for (size_t i = 0; i < fields_.size(); ++i) cols_[i].t = fields_[i].t;
    f_ = openUtf8(path, "wb");  // LOCAL: was fopen (ANSI codepage on Windows)
    if (!f_) {
      fprintf(stderr, "minipq: cannot open %s\n", path.c_str());
      ok_ = false;
      return;
    }
    write("PAR1", 4);
    zctx_ = ZSTD_createCCtx();
  }
  ~Table() {
    complete();
    if (zctx_) ZSTD_freeCCtx(zctx_);
  }

  bool ok() const { return ok_; }
  int64_t rowCount() const { return totalRows_; }

  // ── appenders (PqTable vocabulary) ──
  void putInt(int c, int32_t v) {
    cols_[c].defined.push_back(1);
    cols_[c].i32.push_back(v);
  }
  void putIntNull(int c) { cols_[c].defined.push_back(0); }
  void putInt64(int c, int64_t v) {
    cols_[c].defined.push_back(1);
    cols_[c].i64.push_back(v);
  }
  void putStr(int c, const std::string& v) { putStrView(c, v.data(), (int64_t)v.size()); }
  void putStrView(int c, const char* d, int64_t n) {
    auto& b = cols_[c];
    b.defined.push_back(1);
    b.arena.append(d, (size_t)n);
    b.lens.push_back((uint32_t)n);
    b.valueBytes += (size_t)n;
  }
  void putStrNull(int c) { cols_[c].defined.push_back(0); }
  void putDouble(int c, std::optional<double> v) {
    if (v) {
      cols_[c].defined.push_back(1);
      cols_[c].f64.push_back(*v);
    } else {
      cols_[c].defined.push_back(0);
    }
  }
  void putBool(int c, std::optional<bool> v) {
    if (v) {
      cols_[c].defined.push_back(1);
      cols_[c].b1.push_back(*v ? 1 : 0);
    } else {
      cols_[c].defined.push_back(0);
    }
  }
  void putBinary(int c, const uint8_t* d, int64_t n) {
    putStrView(c, (const char*)d, n);
    bufferedBytes_ += n;
  }

  void endRow() {
    ++buffered_;
    if (buffered_ >= flushRows_ || (flushBytes_ > 0 && bufferedBytes_ >= flushBytes_))
      flush();
  }

  void complete() {
    if (completed_ || !ok_) {
      if (f_ && !completed_) { fclose(f_); f_ = nullptr; completed_ = true; }
      return;
    }
    completed_ = true;
    flush();
    writeFooter();
    fclose(f_);
    f_ = nullptr;
    // Post-close integrity gate: the on-disk size must equal every byte this
    // writer accounted for. Catches stdio/OS/RAM-level tail corruption (observed
    // in the wild: the CRT re-emitting 2-17 tail bytes of a prior fwrite under a
    // failing-hardware whale run) that no in-process bookkeeping can see.
    if (int64_t got = fileSize(path_); got != pos_) {
      fprintf(stderr,
              "minipq: SIZE MISMATCH on %s — wrote %lld bytes, file has %lld; "
              "the file is corrupt (hardware/OS-level write fault?)\n",
              path_.c_str(), (long long)pos_, (long long)got);
      ok_ = false;
    }
  }

 private:
  // ── file plumbing ──
  static int64_t fileSize(const std::string& path) {
    return fileSizeUtf8(path);  // LOCAL: was _stat64/stat (ANSI codepage on Windows)
  }

  void write(const void* p, size_t n) {
    if (!ok_) return;
    if (fwrite(p, 1, n, f_) != n) {
      fprintf(stderr, "minipq: short write\n");
      ok_ = false;
    }
    pos_ += (int64_t)n;
  }
  void write(const std::string& s) { write(s.data(), s.size()); }

  std::string compress(const std::string& raw) {
    size_t cap = ZSTD_compressBound(raw.size());
    std::string out;
    out.resize(cap);
    size_t got = ZSTD_compressCCtx(zctx_, out.data(), cap, raw.data(), raw.size(),
                                   zstdLevel_);
    if (ZSTD_isError(got)) {
      fprintf(stderr, "minipq: zstd: %s\n", ZSTD_getErrorName(got));
      ok_ = false;
      return {};
    }
    out.resize(got);
    return out;
  }

  // ── page slicing ──
  // Target uncompressed VALUE bytes per data page (parquet-cpp's default page
  // size). A single value larger than the target (geometry blobs) gets its own
  // page — pages never split a value.
  static constexpr int64_t kPageTargetBytes = 1 << 20;

  // One data page's slice of a chunk: rows [r0,r1), dense values [v0,v1),
  // a0 = arena byte offset of value v0 (UTF8/BIN only).
  struct PageRange {
    size_t r0, r1, v0, v1, a0;
  };

  // Slice rows into page ranges by estimated encoded value bytes.
  // bytesPerValue > 0: fixed-width estimate; 0: use lens (UTF8/BIN).
  static std::vector<PageRange> makeRanges(const ColBuf& b, size_t bytesPerValue) {
    std::vector<PageRange> out;
    size_t n = b.defined.size(), vi = 0, arena = 0;
    PageRange cur{0, 0, 0, 0, 0};
    int64_t acc = 0;
    for (size_t r = 0; r < n; ++r) {
      if (b.defined[r]) {
        size_t len = bytesPerValue ? bytesPerValue : 4 + (size_t)b.lens[vi];
        if (!bytesPerValue) arena += b.lens[vi];
        ++vi;
        acc += (int64_t)len;
      }
      if (acc >= kPageTargetBytes && r + 1 < n) {
        cur.r1 = r + 1;
        cur.v1 = vi;
        out.push_back(cur);
        cur = {r + 1, 0, vi, 0, arena};
        acc = 0;
      }
    }
    cur.r1 = n;
    cur.v1 = vi;
    out.push_back(cur);
    return out;
  }

  // ── PLAIN value encoders ──
  static std::string plainValues(const ColBuf& b, size_t vFrom, size_t vTo,
                                 size_t arenaFrom) {
    std::string out;
    switch (b.t) {
      case T::I32:
        out.append((const char*)(b.i32.data() + vFrom), (vTo - vFrom) * 4);
        break;
      case T::I64:
        out.append((const char*)(b.i64.data() + vFrom), (vTo - vFrom) * 8);
        break;
      case T::F64:
        out.append((const char*)(b.f64.data() + vFrom), (vTo - vFrom) * 8);
        break;
      case T::BOOL: {
        out.resize((vTo - vFrom + 7) / 8, 0);
        for (size_t i = vFrom; i < vTo; ++i)
          if (b.b1[i]) out[(i - vFrom) / 8] |= (char)(1 << ((i - vFrom) % 8));
        break;
      }
      default: {  // UTF8 / BIN: u32 LE length + bytes
        size_t off = arenaFrom;
        for (size_t i = vFrom; i < vTo; ++i) {
          uint32_t L = b.lens[i];
          out.append((const char*)&L, 4);
          out.append(b.arena.data() + off, L);
          off += L;
        }
      }
    }
    return out;
  }

  // ── page writers ──
  // crc: CRC-32 over the page bytes as written (i.e. the compressed payload) —
  // after the RAM-corruption findings this is load-bearing, not decoration.
  void writePageHeader(int type, size_t uncomp, size_t comp, int64_t numRows,
                       int encoding, uint32_t crc) {
    thrift::Writer w;
    w.i32Field(1, type);
    w.i32Field(2, (int32_t)uncomp);
    w.i32Field(3, (int32_t)comp);
    w.i32Field(4, (int32_t)crc);
    if (type == pq::DATA_PAGE) {
      w.structFieldBegin(5);
      w.i32Field(1, (int32_t)numRows);
      w.i32Field(2, encoding);
      w.i32Field(3, pq::RLE);  // def level encoding
      w.i32Field(4, pq::RLE);  // rep level encoding (none present; flat schema)
      w.structFieldEnd();
    } else {  // dictionary page
      w.structFieldBegin(7);
      w.i32Field(1, (int32_t)numRows);  // here: number of dict entries
      w.i32Field(2, pq::PLAIN);
      w.structFieldEnd();
    }
    w.stop();
    write(w.buf);
  }

  // One data page: def levels + encoded values, zstd'd together (V1 framing).
  void writeDataPage(ChunkMeta& cm, const std::string& values, const uint8_t* defined,
                     size_t rows, int encoding) {
    std::string raw = encodeDefLevels(defined, rows);
    raw += values;
    std::string comp = compress(raw);
    if (cm.dataPageOffset == 0) cm.dataPageOffset = pos_;
    size_t headStart = pos_;
    writePageHeader(pq::DATA_PAGE, raw.size(), comp.size(), (int64_t)rows, encoding,
                    crc32(comp.data(), comp.size()));
    size_t headLen = pos_ - headStart;
    write(comp);
    cm.uncompressedSize += (int64_t)(raw.size() + headLen);
    cm.compressedSize += (int64_t)(comp.size() + headLen);
  }

  // Dictionary attempt for UTF8/F64 chunks. Returns false -> caller writes plain.
  bool tryDict(ColBuf& b, ChunkMeta& cm) {
    constexpr size_t kMaxUnique = 65535, kMaxDictBytes = 1 << 20;
    std::vector<uint32_t> idx;
    idx.reserve(b.numValues());
    std::string dictPayload;
    size_t unique = 0;

    if (b.t == T::UTF8 || b.t == T::BIN) {
      std::unordered_map<std::string_view, uint32_t> map;
      map.reserve(1024);
      size_t off = 0, dictBytes = 0;
      for (size_t i = 0; i < b.lens.size(); ++i) {
        std::string_view v(b.arena.data() + off, b.lens[i]);
        off += b.lens[i];
        auto [it, ins] = map.try_emplace(v, (uint32_t)unique);
        if (ins) {
          ++unique;
          dictBytes += 4 + v.size();
          if (unique > kMaxUnique || dictBytes > kMaxDictBytes) return false;
          uint32_t L = (uint32_t)v.size();
          dictPayload.append((const char*)&L, 4);
          dictPayload.append(v.data(), v.size());
        }
        idx.push_back(it->second);
      }
    } else {  // F64: key on the bit pattern
      std::unordered_map<uint64_t, uint32_t> map;
      map.reserve(1024);
      for (double d : b.f64) {
        uint64_t bits;
        memcpy(&bits, &d, 8);
        auto [it, ins] = map.try_emplace(bits, (uint32_t)unique);
        if (ins) {
          ++unique;
          if (unique > kMaxUnique) return false;
          dictPayload.append((const char*)&d, 8);
        }
        idx.push_back(it->second);
      }
    }
    if (unique == 0 && !idx.empty()) return false;

    // dict page
    cm.dictPageOffset = pos_;
    std::string comp = compress(dictPayload);
    size_t headStart = pos_;
    writePageHeader(pq::DICTIONARY_PAGE, dictPayload.size(), comp.size(),
                    (int64_t)unique, pq::PLAIN, crc32(comp.data(), comp.size()));
    size_t headLen = pos_ - headStart;
    write(comp);
    cm.uncompressedSize += (int64_t)(dictPayload.size() + headLen);
    cm.compressedSize += (int64_t)(comp.size() + headLen);

    // data pages: 1-byte bit width + RLE/bit-packed indices, sliced per page
    int bw = bitsFor(unique ? unique - 1 : 0);
    size_t bpv = (size_t)((bw + 7) / 8);
    for (const auto& pr : makeRanges(b, bpv ? bpv : 1)) {
      std::string values;
      values.push_back((char)bw);
      values += encodeRleHybrid(idx.data() + pr.v0, pr.v1 - pr.v0, bw);
      writeDataPage(cm, values, b.defined.data() + pr.r0, pr.r1 - pr.r0,
                    pq::RLE_DICTIONARY);
    }
    cm.encodings = {pq::RLE, pq::PLAIN, pq::RLE_DICTIONARY};
    return true;
  }

  void flush() {
    if (buffered_ == 0 || !ok_) return;
    RowGroupMeta rg;
    rg.numRows = buffered_;
    for (size_t c = 0; c < cols_.size(); ++c) {
      ColBuf& b = cols_[c];
      ChunkMeta cm;
      cm.numValues = (int64_t)b.defined.size();
      if (b.t == T::I32) {
        cm.nullCount = (int64_t)(b.defined.size() - b.i32.size());
        if (!b.i32.empty()) {
          cm.hasMinMax = true;
          cm.minV = cm.maxV = b.i32[0];
          for (int32_t v : b.i32) {
            if (v < cm.minV) cm.minV = v;
            if (v > cm.maxV) cm.maxV = v;
          }
        }
      }
      bool done = false;
      if (fields_[c].enc == Enc::DICT && b.numValues() > 0)
        done = tryDict(b, cm);
      if (!done) {
        if (fields_[c].enc == Enc::DELTA_I32) {
          for (const auto& pr : makeRanges(b, 4)) {
            std::string values =
                encodeDeltaI32(b.i32.data() + pr.v0, pr.v1 - pr.v0);
            writeDataPage(cm, values, b.defined.data() + pr.r0, pr.r1 - pr.r0,
                          pq::DELTA_BINARY_PACKED);
          }
          cm.encodings = {pq::RLE, pq::DELTA_BINARY_PACKED};
        } else {
          size_t bpv = (b.t == T::I32) ? 4
                       : (b.t == T::BOOL) ? 1
                       : (b.t == T::UTF8 || b.t == T::BIN) ? 0
                                                           : 8;
          for (const auto& pr : makeRanges(b, bpv)) {
            std::string values = plainValues(b, pr.v0, pr.v1, pr.a0);
            writeDataPage(cm, values, b.defined.data() + pr.r0, pr.r1 - pr.r0,
                          pq::PLAIN);
          }
          cm.encodings = {pq::RLE, pq::PLAIN};
        }
      }
      rg.chunks.push_back(cm);
      b.clear();
    }
    groups_.push_back(std::move(rg));
    totalRows_ += buffered_;
    buffered_ = 0;
    bufferedBytes_ = 0;
  }

  // ── footer ──
  void writeFooter() {
    thrift::Writer w;
    w.i32Field(1, 1);  // version
    // 2: schema — root + one leaf per column
    w.listFieldBegin(2, thrift::CT_STRUCT, fields_.size() + 1);
    {
      w.structElemBegin();  // root
      w.binaryField(4, "schema");
      w.i32Field(5, (int32_t)fields_.size());
      w.structElemEnd();
      for (auto& f : fields_) {
        w.structElemBegin();
        w.i32Field(1, pqType(f.t));
        w.i32Field(3, pq::REP_OPTIONAL);
        w.binaryField(4, f.name);
        if (f.t == T::UTF8) w.i32Field(6, pq::CONV_UTF8);
        w.structElemEnd();
      }
    }
    w.i64Field(3, totalRows_);
    // 4: row groups
    w.listFieldBegin(4, thrift::CT_STRUCT, groups_.size());
    for (auto& rg : groups_) {
      w.structElemBegin();
      w.listFieldBegin(1, thrift::CT_STRUCT, rg.chunks.size());
      int64_t rgBytes = 0;
      for (size_t c = 0; c < rg.chunks.size(); ++c) {
        auto& cm = rg.chunks[c];
        rgBytes += cm.uncompressedSize;
        w.structElemBegin();  // ColumnChunk
        w.i64Field(2, cm.dataPageOffset);
        w.structFieldBegin(3);  // ColumnMetaData
        w.i32Field(1, pqType(fields_[c].t));
        w.listFieldBegin(2, thrift::CT_I32, cm.encodings.size());
        for (int e : cm.encodings) w.listElemI32(e);
        w.listFieldBegin(3, thrift::CT_BINARY, 1);
        w.listElemBinary(fields_[c].name);
        w.i32Field(4, pq::CODEC_ZSTD);
        w.i64Field(5, cm.numValues);
        w.i64Field(6, cm.uncompressedSize);
        w.i64Field(7, cm.compressedSize);
        w.i64Field(9, cm.dataPageOffset);
        if (cm.dictPageOffset >= 0) w.i64Field(11, cm.dictPageOffset);
        if (cm.nullCount >= 0) {  // 12: Statistics (int32 columns)
          w.structFieldBegin(12);
          w.i64Field(3, cm.nullCount);
          if (cm.hasMinMax) {
            w.binaryField(5, std::string((const char*)&cm.maxV, 4));  // max_value
            w.binaryField(6, std::string((const char*)&cm.minV, 4));  // min_value
          }
          w.structFieldEnd();
        }
        w.structFieldEnd();
        w.structElemEnd();
      }
      w.i64Field(2, rgBytes);
      w.i64Field(3, rg.numRows);
      w.structElemEnd();
    }
    w.binaryField(6, "minipq 0.1");
    // 7: column_orders — TYPE_DEFINED_ORDER per leaf. Readers refuse to trust
    // min_value/max_value statistics unless the file declares its sort order.
    w.listFieldBegin(7, thrift::CT_STRUCT, fields_.size());
    for (size_t i = 0; i < fields_.size(); ++i) {
      w.structElemBegin();      // ColumnOrder union
      w.structFieldBegin(1);    // 1: TYPE_ORDER (empty struct)
      w.structFieldEnd();
      w.structElemEnd();
    }
    w.stop();

    write(w.buf);
    uint32_t len = (uint32_t)w.buf.size();
    write(&len, 4);
    write("PAR1", 4);
  }

  std::string path_;
  std::vector<Field> fields_;
  std::vector<ColBuf> cols_;
  std::vector<RowGroupMeta> groups_;
  FILE* f_ = nullptr;
  ZSTD_CCtx* zctx_ = nullptr;
  int64_t pos_ = 0, flushRows_, flushBytes_, buffered_ = 0, bufferedBytes_ = 0,
          totalRows_ = 0;
  int zstdLevel_;
  bool ok_ = true, completed_ = false;
};

}  // namespace minipq
