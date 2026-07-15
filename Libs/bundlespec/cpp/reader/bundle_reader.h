#pragma once
// BundleReader — typed row iteration over a finished Speckle bundle (schema_version 5).
// The read-side counterpart of cpp/writer/bundle_writer.h, built on the same
// parquet::arrow primitives the converters merge uses. Consumers: the archicad receive
// path (replacing its DuckDB read_parquet queries + hard-coded schema knowledge) and
// any future bundle tooling.
//
// Column names come from the generated bundle_schemas.h shapes; enum values are
// bundlespec::Rel / bundlespec::NodeKind — no magic numbers on the consumer side.

#include <arrow/api.h>
#include <arrow/io/file.h>
#include <parquet/arrow/reader.h>

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace speckle {

class BundleReader {
 public:
  // Canonical table file suffixes (writer contract: "{base}<suffix>"). These are the
  // one place receive flows should get their file-name knowledge from.
  static constexpr const char* kObjectsSuffix = ".eav.objects.parquet";
  static constexpr const char* kNodesSuffix = ".envelope.nodes.parquet";
  static constexpr const char* kRelationsSuffix = ".envelope.relations.parquet";

  // Geometry shards: "{base}.geometries.parquet" + "{base}.geometries.N.parquet".
  static bool isGeometryShard(const std::string& name) {
    return name.find(".geometries") != std::string::npos &&
           endsWith(name, ".parquet");
  }
  // Any table a geometry-reconstructing receive needs (objects/relations/nodes/shards).
  static bool isReceiveTable(const std::string& name) {
    return isGeometryShard(name) || endsWith(name, kObjectsSuffix) ||
           endsWith(name, kNodesSuffix) || endsWith(name, kRelationsSuffix);
  }

  struct ObjectRow {
    int32_t objectIndex = 0;
    std::string applicationId;
  };
  struct RelationRow {
    int32_t rel = 0, src = 0, dst = 0, ord = 0;
  };
  struct NodeRow {
    int32_t id = 0, kind = 0;
    std::optional<std::string> name;
    std::optional<int32_t> defRef;
    std::optional<std::string> transform, units, subtype;
    std::optional<int32_t> argb;
    std::optional<double> opacity, metalness, roughness, elevation;
  };
  struct GeometryRow {
    int32_t geometryIndex = 0;
    // Points into the current record batch — valid only during the callback; copy to keep.
    const uint8_t* content = nullptr;
    int64_t contentLength = 0;
    std::string id, type;
  };

  // Receive flow: explicit local paths (files usually arrive one-by-one from an
  // artifact download). Any path may be empty if the caller won't iterate that table.
  BundleReader(std::filesystem::path objectsPath,
               std::filesystem::path relationsPath,
               std::filesystem::path nodesPath,
               std::vector<std::filesystem::path> geometryShards)
      : objects_(std::move(objectsPath)),
        relations_(std::move(relationsPath)),
        nodes_(std::move(nodesPath)),
        shards_(std::move(geometryShards)) {}

  // Tools/tests flow: a bundle directory + base name; enumerates the canonical
  // table files and the geometry shard chain ({base}.geometries[.N].parquet).
  static BundleReader open(const std::filesystem::path& bundleDir,
                           const std::string& baseName) {
    std::vector<std::filesystem::path> shards;
    std::filesystem::path canonical =
        bundleDir / (baseName + ".geometries.parquet");
    if (std::filesystem::exists(canonical)) shards.push_back(canonical);
    for (int n = 1;; ++n) {
      std::filesystem::path shard =
          bundleDir / (baseName + ".geometries." + std::to_string(n) +
                       ".parquet");
      if (!std::filesystem::exists(shard)) break;
      shards.push_back(shard);
    }
    return BundleReader(bundleDir / (baseName + kObjectsSuffix),
                        bundleDir / (baseName + kRelationsSuffix),
                        bundleDir / (baseName + kNodesSuffix),
                        std::move(shards));
  }

  void forEachObject(const std::function<void(const ObjectRow&)>& fn) const {
    forEachBatch(objects_, [&](const arrow::RecordBatch& b) {
      auto idx = intCol(b, "object_index");
      auto app = strCol(b, "application_id");
      for (int64_t i = 0; i < b.num_rows(); ++i) {
        ObjectRow r;
        r.objectIndex = idx->Value(i);
        if (!app->IsNull(i)) r.applicationId = app->GetString(i);
        fn(r);
      }
    });
  }

  // Relations, filtered to the given rel ids (empty = all) and sorted by (src, ord)
  // — the ordering receive paths rely on (the old ORDER BY src, ord). Materialized:
  // relations tables are small relative to geometry.
  std::vector<RelationRow> readRelations(
      const std::vector<int>& relFilter = {}) const {
    std::vector<RelationRow> out;
    forEachBatch(relations_, [&](const arrow::RecordBatch& b) {
      auto rel = intCol(b, "rel");
      auto src = intCol(b, "src");
      auto dst = intCol(b, "dst");
      auto ord = intCol(b, "ord");
      for (int64_t i = 0; i < b.num_rows(); ++i) {
        RelationRow r{rel->Value(i), src->Value(i), dst->Value(i),
                      ord->IsNull(i) ? 0 : ord->Value(i)};
        if (!relFilter.empty() &&
            std::find(relFilter.begin(), relFilter.end(), r.rel) ==
                relFilter.end())
          continue;
        out.push_back(r);
      }
    });
    std::stable_sort(out.begin(), out.end(),
                     [](const RelationRow& a, const RelationRow& b) {
                       return a.src != b.src ? a.src < b.src : a.ord < b.ord;
                     });
    return out;
  }

  void forEachNode(const std::function<void(const NodeRow&)>& fn,
                   const std::vector<int>& kindFilter = {}) const {
    forEachBatch(nodes_, [&](const arrow::RecordBatch& b) {
      auto id = intCol(b, "id");
      auto kind = intCol(b, "kind");
      auto name = strCol(b, "name");
      auto defRef = intCol(b, "def_ref");
      auto xf = strCol(b, "transform");
      auto units = strCol(b, "units");
      auto subtype = strCol(b, "subtype");
      auto argb = intCol(b, "argb");
      auto opacity = dblCol(b, "opacity");
      auto metalness = dblCol(b, "metalness");
      auto roughness = dblCol(b, "roughness");
      auto elevation = dblCol(b, "elevation");
      for (int64_t i = 0; i < b.num_rows(); ++i) {
        NodeRow r;
        r.id = id->Value(i);
        r.kind = kind->Value(i);
        if (!kindFilter.empty() &&
            std::find(kindFilter.begin(), kindFilter.end(), r.kind) ==
                kindFilter.end())
          continue;
        if (!name->IsNull(i)) r.name = name->GetString(i);
        if (!defRef->IsNull(i)) r.defRef = defRef->Value(i);
        if (!xf->IsNull(i)) r.transform = xf->GetString(i);
        if (!units->IsNull(i)) r.units = units->GetString(i);
        if (!subtype->IsNull(i)) r.subtype = subtype->GetString(i);
        if (!argb->IsNull(i)) r.argb = argb->Value(i);
        if (!opacity->IsNull(i)) r.opacity = opacity->Value(i);
        if (!metalness->IsNull(i)) r.metalness = metalness->Value(i);
        if (!roughness->IsNull(i)) r.roughness = roughness->Value(i);
        if (!elevation->IsNull(i)) r.elevation = elevation->Value(i);
        fn(r);
      }
    });
  }

  // Streams every geometry row across all shards, in shard order. GeometryRow.content
  // points into the live batch — decode/copy inside the callback.
  void forEachGeometry(const std::function<void(const GeometryRow&)>& fn) const {
    for (const auto& shard : shards_) {
      forEachBatch(shard, [&](const arrow::RecordBatch& b) {
        auto idx = intCol(b, "geometryIndex");
        auto content = binCol(b, "content");
        auto id = strCol(b, "id");
        auto type = strCol(b, "type");
        for (int64_t i = 0; i < b.num_rows(); ++i) {
          GeometryRow r;
          r.geometryIndex = idx->Value(i);
          if (!content->IsNull(i)) {
            arrow::BinaryArray::offset_type len = 0;
            r.content = content->GetValue(i, &len);
            r.contentLength = len;
          }
          if (!id->IsNull(i)) r.id = id->GetString(i);
          if (!type->IsNull(i)) r.type = type->GetString(i);
          fn(r);
        }
      });
    }
  }

  const std::vector<std::filesystem::path>& geometryShards() const {
    return shards_;
  }

 private:
  static bool endsWith(const std::string& s, const std::string& suffix) {
    return s.size() >= suffix.size() &&
           s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
  }

  static void forEachBatch(
      const std::filesystem::path& path,
      const std::function<void(const arrow::RecordBatch&)>& fn) {
    if (path.empty())
      throw std::runtime_error("BundleReader: no path set for requested table");
    auto fileRes = arrow::io::ReadableFile::Open(path.string());
    if (!fileRes.ok())
      throw std::runtime_error("BundleReader: open " + path.string() + ": " +
                               fileRes.status().ToString());
    auto readerRes =
        parquet::arrow::OpenFile(*fileRes, arrow::default_memory_pool());
    if (!readerRes.ok())
      throw std::runtime_error("BundleReader: parquet open " + path.string() +
                               ": " + readerRes.status().ToString());
    std::unique_ptr<parquet::arrow::FileReader> reader =
        std::move(*readerRes);
    auto rbrRes = reader->GetRecordBatchReader();
    if (!rbrRes.ok())
      throw std::runtime_error("BundleReader: batch reader " + path.string() +
                               ": " + rbrRes.status().ToString());
    std::shared_ptr<arrow::RecordBatchReader> rbr = std::move(*rbrRes);
    while (true) {
      std::shared_ptr<arrow::RecordBatch> batch;
      auto st = rbr->ReadNext(&batch);
      if (!st.ok())
        throw std::runtime_error("BundleReader: read " + path.string() + ": " +
                                 st.ToString());
      if (!batch) break;
      fn(*batch);
    }
  }

  template <typename ArrayT>
  static std::shared_ptr<ArrayT> col(const arrow::RecordBatch& b,
                                     const char* name) {
    int idx = b.schema()->GetFieldIndex(name);
    if (idx < 0)
      throw std::runtime_error(std::string("BundleReader: missing column ") +
                               name);
    auto arr = std::dynamic_pointer_cast<ArrayT>(b.column(idx));
    if (!arr)
      throw std::runtime_error(std::string("BundleReader: column ") + name +
                               " has unexpected type " +
                               b.column(idx)->type()->ToString());
    return arr;
  }
  static std::shared_ptr<arrow::Int32Array> intCol(const arrow::RecordBatch& b,
                                                   const char* name) {
    return col<arrow::Int32Array>(b, name);
  }
  static std::shared_ptr<arrow::StringArray> strCol(const arrow::RecordBatch& b,
                                                    const char* name) {
    return col<arrow::StringArray>(b, name);
  }
  static std::shared_ptr<arrow::DoubleArray> dblCol(const arrow::RecordBatch& b,
                                                    const char* name) {
    return col<arrow::DoubleArray>(b, name);
  }
  static std::shared_ptr<arrow::BinaryArray> binCol(const arrow::RecordBatch& b,
                                                    const char* name) {
    return col<arrow::BinaryArray>(b, name);
  }

  std::filesystem::path objects_, relations_, nodes_;
  std::vector<std::filesystem::path> shards_;
};

}  // namespace speckle
