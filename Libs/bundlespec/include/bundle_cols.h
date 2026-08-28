// GENERATED FROM spec/bundle-spec.sql — DO NOT EDIT.
// Run `npm run generate` (or node codegen/generate-all.mjs) to refresh.
#pragma once

// Column index of every produced table's parquet field, in spec order (matches
// bundle_schemas.h field order 1:1). NOTE: camera_views has columns named
// `near`/`far` — on Windows include this header BEFORE <windows.h> or compile
// with WIN32_LEAN_AND_MEAN/#undef near,far (windef.h defines them as macros).

namespace bundlespec::col::camera_views {
inline constexpr int view = 0;
inline constexpr int name = 1;
inline constexpr int is_default = 2;
inline constexpr int ord = 3;
inline constexpr int pos_x = 4;
inline constexpr int pos_y = 5;
inline constexpr int pos_z = 6;
inline constexpr int forward_x = 7;
inline constexpr int forward_y = 8;
inline constexpr int forward_z = 9;
inline constexpr int up_x = 10;
inline constexpr int up_y = 11;
inline constexpr int up_z = 12;
inline constexpr int target_x = 13;
inline constexpr int target_y = 14;
inline constexpr int target_z = 15;
inline constexpr int units = 16;
inline constexpr int is_ortho = 17;
inline constexpr int fov = 18;
inline constexpr int lens_mm = 19;
inline constexpr int ortho_height = 20;
inline constexpr int aspect = 21;
inline constexpr int near = 22;
inline constexpr int far = 23;
inline constexpr int columnCount = 24;
}  // namespace bundlespec::col::camera_views

namespace bundlespec::col::eav {
inline constexpr int object_index = 0;
inline constexpr int path_index = 1;
inline constexpr int value_string = 2;
inline constexpr int value_double = 3;
inline constexpr int value_boolean = 4;
inline constexpr int unit = 5;
inline constexpr int internal_definition_name = 6;
inline constexpr int columnCount = 7;
}  // namespace bundlespec::col::eav

namespace bundlespec::col::geometries {
inline constexpr int geometry_index = 0;
inline constexpr int content = 1;
inline constexpr int id = 2;
inline constexpr int type = 3;
inline constexpr int columnCount = 4;
}  // namespace bundlespec::col::geometries

namespace bundlespec::col::model {
inline constexpr int path = 0;
inline constexpr int value_string = 1;
inline constexpr int value_double = 2;
inline constexpr int value_boolean = 3;
inline constexpr int unit = 4;
inline constexpr int columnCount = 5;
}  // namespace bundlespec::col::model

namespace bundlespec::col::nodes {
inline constexpr int id = 0;
inline constexpr int kind = 1;
inline constexpr int name = 2;
inline constexpr int def_ref = 3;
inline constexpr int transform = 4;
inline constexpr int units = 5;
inline constexpr int subtype = 6;
inline constexpr int argb = 7;
inline constexpr int opacity = 8;
inline constexpr int metalness = 9;
inline constexpr int roughness = 10;
inline constexpr int emissive = 11;
inline constexpr int ior = 12;
inline constexpr int elevation = 13;
inline constexpr int gh_topology = 14;
inline constexpr int columnCount = 15;
}  // namespace bundlespec::col::nodes

namespace bundlespec::col::object_type {
inline constexpr int object_index = 0;
inline constexpr int type_index = 1;
inline constexpr int columnCount = 2;
}  // namespace bundlespec::col::object_type

namespace bundlespec::col::objects {
inline constexpr int object_index = 0;
inline constexpr int application_id = 1;
inline constexpr int columnCount = 2;
}  // namespace bundlespec::col::objects

namespace bundlespec::col::paths {
inline constexpr int path_index = 0;
inline constexpr int path = 1;
inline constexpr int columnCount = 2;
}  // namespace bundlespec::col::paths

namespace bundlespec::col::property_set_definitions {
inline constexpr int set_name = 0;
inline constexpr int set_key = 1;
inline constexpr int set_description = 2;
inline constexpr int field_name = 3;
inline constexpr int field_bucket_id = 4;
inline constexpr int data_type = 5;
inline constexpr int default_string = 6;
inline constexpr int default_double = 7;
inline constexpr int default_boolean = 8;
inline constexpr int unit = 9;
inline constexpr int description = 10;
inline constexpr int applies_to = 11;
inline constexpr int columnCount = 12;
}  // namespace bundlespec::col::property_set_definitions

namespace bundlespec::col::relations {
inline constexpr int rel = 0;
inline constexpr int src = 1;
inline constexpr int dst = 2;
inline constexpr int ord = 3;
inline constexpr int columnCount = 4;
}  // namespace bundlespec::col::relations

namespace bundlespec::col::scene_views {
inline constexpr int view = 0;
inline constexpr int name = 1;
inline constexpr int is_default = 2;
inline constexpr int ord = 3;
inline constexpr int source = 4;
inline constexpr int ref = 5;
inline constexpr int columnCount = 6;
}  // namespace bundlespec::col::scene_views

namespace bundlespec::col::structural_results {
inline constexpr int object_index = 0;
inline constexpr int element_name = 1;
inline constexpr int location = 2;
inline constexpr int result_type = 3;
inline constexpr int load_case = 4;
inline constexpr int component = 5;
inline constexpr int position_label = 6;
inline constexpr int station = 7;
inline constexpr int step = 8;
inline constexpr int value = 9;
inline constexpr int value_text = 10;
inline constexpr int columnCount = 11;
}  // namespace bundlespec::col::structural_results

namespace bundlespec::col::type_eav {
inline constexpr int type_index = 0;
inline constexpr int path_index = 1;
inline constexpr int value_string = 2;
inline constexpr int value_double = 3;
inline constexpr int value_boolean = 4;
inline constexpr int unit = 5;
inline constexpr int internal_definition_name = 6;
inline constexpr int columnCount = 7;
}  // namespace bundlespec::col::type_eav

namespace bundlespec::col::types {
inline constexpr int type_index = 0;
inline constexpr int type_key = 1;
inline constexpr int columnCount = 2;
}  // namespace bundlespec::col::types
