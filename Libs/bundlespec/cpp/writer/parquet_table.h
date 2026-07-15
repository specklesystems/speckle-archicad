// Generic columnar Parquet table writer over Apache Arrow (zstd, row-group buffered).
// Mirrors the .NET ParquetTableWriter: append rows in schema-column order, flush a
// row group every N rows, stream to disk at bounded memory. Replaces the hand-rolled
// .NET writer — Arrow owns the format.
#pragma once
#include <arrow/api.h>
#include <arrow/io/file.h>
#include <parquet/arrow/writer.h>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <cstdint>
#include <cstdio>

class PqTable {
 public:
  // flushRows mirrors DEFAULT_ROWGROUP_ROWS (200k) in the .NET writer.
  // flushBytes: also flush when buffered binary bytes exceed this (0 = disabled). Mirrors the
  // .NET GeometriesParquetWriter byte budget so huge mesh blobs don't accumulate in RAM.
  PqTable(const std::string& path, std::shared_ptr<arrow::Schema> schema,
          int64_t flushRows = 200000, int64_t flushBytes = 0)
      : schema_(std::move(schema)),
        flushRows_(flushRows),
        flushBytes_(flushBytes) {
    for (const auto& f : schema_->fields()) {
      builders_.push_back(makeBuilder(f->type()));
    }
    auto outRes = arrow::io::FileOutputStream::Open(path);
    if (!outRes.ok()) {
      fail("open " + path, outRes.status());
      return;
    }
    out_ = *outRes;
    // Integer columns in the bundle are dense indices (object/path/type/geometry K, node ids, rel
    // src/dst/ord) — sequential or low-cardinality. Parquet's default dictionary encoding wastes
    // space on them (e.g. an all-unique object_index → a 36 KB dictionary vs 75 B with delta), so
    // give every int32 column DELTA_BINARY_PACKED + no dictionary (matches the managed writer).
    parquet::WriterProperties::Builder pb;
    pb.compression(parquet::Compression::ZSTD);
    for (const auto& f : schema_->fields()) {
      if (f->type()->id() == arrow::Type::INT32) {
        pb.disable_dictionary(f->name());
        pb.encoding(f->name(), parquet::Encoding::DELTA_BINARY_PACKED);
      } else if (f->name() == "application_id" || f->name() == "id") {
        // High-cardinality id columns: the dictionary is dead weight (every value unique); PLAIN
        // lets ZSTD exploit the shared GUID structure directly (matches the managed writer).
        pb.disable_dictionary(f->name());
      }
    }
    auto props = pb.build();
    auto wprops = parquet::ArrowWriterProperties::Builder().build();
    auto wRes = parquet::arrow::FileWriter::Open(
        *schema_, arrow::default_memory_pool(), out_, props, wprops);
    if (!wRes.ok()) {
      fail("FileWriter::Open " + path, wRes.status());
      return;
    }
    writer_ = std::move(*wRes);
  }

  bool ok() const { return ok_; }

  // Column appenders (call in schema order, then endRow()).
  void putInt(int col, int32_t v) {
    static_cast<arrow::Int32Builder*>(builders_[col].get())->Append(v).ok();
  }
  void putIntNull(int col) {
    static_cast<arrow::Int32Builder*>(builders_[col].get())->AppendNull().ok();
  }
  void putInt64(int col, int64_t v) {
    static_cast<arrow::Int64Builder*>(builders_[col].get())->Append(v).ok();
  }
  void putStr(int col, const std::string& v) {
    static_cast<arrow::StringBuilder*>(builders_[col].get())->Append(v).ok();
  }
  // Zero-copy variant for readers streaming cells straight back out (bundle_merge).
  void putStrView(int col, const char* data, int64_t len) {
    static_cast<arrow::StringBuilder*>(builders_[col].get())
        ->Append(data, (int32_t)len)
        .ok();
  }
  void putStrNull(int col) {
    static_cast<arrow::StringBuilder*>(builders_[col].get())->AppendNull().ok();
  }
  void putDouble(int col, std::optional<double> v) {
    auto* b = static_cast<arrow::DoubleBuilder*>(builders_[col].get());
    if (v)
      b->Append(*v).ok();
    else
      b->AppendNull().ok();
  }
  void putBool(int col, std::optional<bool> v) {
    auto* b = static_cast<arrow::BooleanBuilder*>(builders_[col].get());
    if (v)
      b->Append(*v).ok();
    else
      b->AppendNull().ok();
  }
  void putBinary(int col, const uint8_t* data, int64_t len) {
    static_cast<arrow::BinaryBuilder*>(builders_[col].get())
        ->Append(data, (int32_t)len)
        .ok();
    bufferedBytes_ += len;
  }

  void endRow() {
    ++buffered_;
    if (buffered_ >= flushRows_ ||
        (flushBytes_ > 0 && bufferedBytes_ >= flushBytes_))
      flush();
  }

  void complete() {
    if (completed_) return;
    completed_ = true;
    flush();
    if (writer_) writer_->Close().ok();
    if (out_) out_->Close().ok();
  }

  int64_t rowCount() const { return totalRows_; }

 private:
  void flush() {
    if (buffered_ == 0) return;
    std::vector<std::shared_ptr<arrow::Array>> arrays;
    arrays.reserve(builders_.size());
    for (auto& b : builders_) {
      std::shared_ptr<arrow::Array> a;
      if (!b->Finish(&a).ok()) {
        ok_ = false;
        return;
      }
      arrays.push_back(a);
    }
    auto table = arrow::Table::Make(schema_, arrays);
    auto st = writer_->WriteTable(*table, buffered_);
    if (!st.ok()) {
      fail("WriteTable", st);
      return;
    }
    totalRows_ += buffered_;
    buffered_ = 0;
    bufferedBytes_ = 0;
  }

  static std::unique_ptr<arrow::ArrayBuilder> makeBuilder(
      const std::shared_ptr<arrow::DataType>& t) {
    switch (t->id()) {
      case arrow::Type::INT32:
        return std::make_unique<arrow::Int32Builder>();
      case arrow::Type::INT64:
        return std::make_unique<arrow::Int64Builder>();
      case arrow::Type::DOUBLE:
        return std::make_unique<arrow::DoubleBuilder>();
      case arrow::Type::BOOL:
        return std::make_unique<arrow::BooleanBuilder>();
      case arrow::Type::STRING:
        return std::make_unique<arrow::StringBuilder>();
      case arrow::Type::BINARY:
        return std::make_unique<arrow::BinaryBuilder>();
      default:
        return std::make_unique<arrow::StringBuilder>();
    }
  }

  void fail(const std::string& what, const arrow::Status& st) {
    fprintf(stderr, "PqTable error [%s]: %s\n", what.c_str(),
            st.ToString().c_str());
    ok_ = false;
  }

  std::shared_ptr<arrow::Schema> schema_;
  std::vector<std::unique_ptr<arrow::ArrayBuilder>> builders_;
  std::shared_ptr<arrow::io::FileOutputStream> out_;
  std::unique_ptr<parquet::arrow::FileWriter> writer_;
  int64_t flushRows_, flushBytes_ = 0, buffered_ = 0, bufferedBytes_ = 0,
                      totalRows_ = 0;
  bool ok_ = true, completed_ = false;
};
