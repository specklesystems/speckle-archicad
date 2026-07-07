// GENERATED FROM spec/bundle-spec.sql — DO NOT EDIT.
// Run `npm run generate` (or node codegen/generate-all.mjs) to refresh.
#pragma once
#include <cstdint>

namespace bundlespec {

constexpr int kSchemaVersion = 5;

enum class Rel : int {
  DISPLAY = 1,
  SOLID = 2,
  SUBELEMENT = 3,
  DEFINES = 4,
  HAS_MATERIAL = 5,
  HAS_COLOR = 6,
  ON_LEVEL = 7,
  DISPLAY_INSTANCE = 8,
  DEFINES_INSTANCE = 9,
  IN_COLLECTION = 10,
  IN_MODEL = 11,
  IN_ROOM = 12,
  IN_SYSTEM = 14,
  CONNECTS_TO = 21,
  BOUNDS = 23,
};

enum class NodeKind : int {
  DEFINITION = 1,
  INSTANCE = 2,
  MATERIAL = 3,
  COLOR = 4,
  LEVEL = 5,
  CONTAINER = 7,
};

struct RelTypeRow { int id; const char* name; const char* src_ns; const char* dst_ns; const char* status; };
struct NodeKindRow { int id; const char* name; const char* subtype_values; };

// The catalog producers write into envelope.rel_types / envelope.node_kinds
// (live + reserved; retired ids are omitted but never reused).
static const RelTypeRow kRelTypes[] = {
  {1, "DISPLAY", "object", "geometry", "live"},
  {2, "SOLID", "object", "geometry", "reserved"},
  {3, "SUBELEMENT", "object", "object", "live"},
  {4, "DEFINES", "node", "geometry", "live"},
  {5, "HAS_MATERIAL", "geometry", "node", "live"},
  {6, "HAS_COLOR", "geometry|object", "node", "live"},
  {7, "ON_LEVEL", "object", "node", "live"},
  {8, "DISPLAY_INSTANCE", "object", "node", "live"},
  {9, "DEFINES_INSTANCE", "node", "node", "live"},
  {10, "IN_COLLECTION", "object", "node", "live"},
  {11, "IN_MODEL", "object", "node", "live"},
  {12, "IN_ROOM", "object", "object", "live"},
  {14, "IN_SYSTEM", "object", "node", "live"},
  {21, "CONNECTS_TO", "object", "object", "live"},
  {23, "BOUNDS", "object", "object", "live"},
};
static const NodeKindRow kNodeKinds[] = {
  {1, "DEFINITION", nullptr},
  {2, "INSTANCE", nullptr},
  {3, "MATERIAL", nullptr},
  {4, "COLOR", nullptr},
  {5, "LEVEL", nullptr},
  {7, "CONTAINER", "Collection,Model,MEP System,Network"},
};

}  // namespace bundlespec
