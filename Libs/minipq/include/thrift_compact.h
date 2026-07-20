// Minimal Thrift compact-protocol WRITER — just enough to serialize the parquet
// footer metadata (FileMetaData and friends). Field ids/types must match
// parquet.thrift exactly; this encodes structs/lists/varints per the compact spec.
// No thrift dependency: ~150 lines replaces the generated code + libthrift.
#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace minipq::thrift {

// Compact-protocol wire type ids.
enum CType : uint8_t {
  CT_STOP = 0,
  CT_TRUE = 1,
  CT_FALSE = 2,
  CT_BYTE = 3,
  CT_I16 = 4,
  CT_I32 = 5,
  CT_I64 = 6,
  CT_DOUBLE = 7,
  CT_BINARY = 8,
  CT_LIST = 9,
  CT_SET = 10,
  CT_MAP = 11,
  CT_STRUCT = 12,
};

class Writer {
 public:
  std::string buf;

  void uvarint(uint64_t v) {
    while (v >= 0x80) {
      buf.push_back((char)(0x80 | (v & 0x7f)));
      v >>= 7;
    }
    buf.push_back((char)v);
  }
  void zigzag32(int32_t v) { uvarint(((uint32_t)v << 1) ^ (uint32_t)(v >> 31)); }
  void zigzag64(int64_t v) { uvarint(((uint64_t)v << 1) ^ (uint64_t)(v >> 63)); }

  // Field header: short form (delta 1..15) or long form (0 nibble + zigzag id).
  void fieldBegin(int16_t id, CType t) {
    int delta = id - lastId_;
    if (delta >= 1 && delta <= 15) {
      buf.push_back((char)((delta << 4) | t));
    } else {
      buf.push_back((char)t);
      zigzag32(id);  // spec: i16 zigzag
    }
    lastId_ = id;
  }
  void stop() { buf.push_back((char)CT_STOP); }

  // Scalar fields ------------------------------------------------------------
  void i32Field(int16_t id, int32_t v) {
    fieldBegin(id, CT_I32);
    zigzag32(v);
  }
  void i64Field(int16_t id, int64_t v) {
    fieldBegin(id, CT_I64);
    zigzag64(v);
  }
  void boolField(int16_t id, bool v) {
    // Compact protocol folds the value into the field type.
    fieldBegin(id, v ? CT_TRUE : CT_FALSE);
  }
  void binaryField(int16_t id, const std::string& s) {
    fieldBegin(id, CT_BINARY);
    uvarint(s.size());
    buf.append(s);
  }

  // Structs ------------------------------------------------------------------
  // Nested structs reset the last-field-id counter; save/restore around them.
  void structFieldBegin(int16_t id) {
    fieldBegin(id, CT_STRUCT);
    stack_.push_back(lastId_);
    lastId_ = 0;
  }
  void structFieldEnd() {
    stop();
    lastId_ = stack_.back();
    stack_.pop_back();
  }
  // A struct that is a LIST ELEMENT (no field header; fresh id counter).
  void structElemBegin() {
    stack_.push_back(lastId_);
    lastId_ = 0;
  }
  void structElemEnd() {
    stop();
    lastId_ = stack_.back();
    stack_.pop_back();
  }

  // Lists ----------------------------------------------------------------------
  void listFieldBegin(int16_t id, CType elem, size_t n) {
    fieldBegin(id, CT_LIST);
    listHeader(elem, n);
  }
  void listHeader(CType elem, size_t n) {
    if (n < 15) {
      buf.push_back((char)((n << 4) | elem));
    } else {
      buf.push_back((char)(0xF0 | elem));
      uvarint(n);
    }
  }
  // List elements: i32 enums are zigzag varints, strings are len+bytes.
  void listElemI32(int32_t v) { zigzag32(v); }
  void listElemBinary(const std::string& s) {
    uvarint(s.size());
    buf.append(s);
  }

 private:
  int16_t lastId_ = 0;
  std::vector<int16_t> stack_;
};

}  // namespace minipq::thrift
