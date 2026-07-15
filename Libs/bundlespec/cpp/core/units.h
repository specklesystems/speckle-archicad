#pragma once
// Units — the one table mapping unit string ↔ uint16 SGEO code ↔ meters factor.
// Consolidates the four prior copies (converters sgeo::unitsCode; archicad
// SgeoEncoder::UnitsCode, SgeoDecoder::UnitsFromCode, ArtifactReceiver::
// UnitsToMetersFactor). Codes mirror Units.GetEncodingFromUnit /
// GetUnitFromEncoding in the managed SDK — this is a cross-producer wire
// contract (SGEO header units field), do not renumber.
#include <cstdint>
#include <string>

namespace units {

struct Row {
  const char* name;
  uint16_t code;
  double toMeters;
};

// Order = code order; code 0 ("none") is the unknown/neutral entry.
inline constexpr Row kTable[] = {
    {"none", 0, 1.0},   {"mm", 1, 0.001},  {"cm", 2, 0.01},
    {"m", 3, 1.0},      {"km", 4, 1000.0}, {"in", 5, 0.0254},
    {"ft", 6, 0.3048},  {"yd", 7, 0.9144}, {"mi", 8, 1609.344},
};

// Unit string → SGEO uint16 code; unknown strings → 0.
inline uint16_t code(const std::string& u) {
  for (const auto& r : kTable)
    if (u == r.name) return r.code;
  return 0;
}

// SGEO uint16 code → unit string; unknown codes → "none".
inline std::string fromCode(uint16_t c) {
  for (const auto& r : kTable)
    if (c == r.code) return r.name;
  return "none";
}

// Unit string → meters factor; empty/"none"/unknown → 1.0 (matches the prior
// archicad receive-path behavior).
inline double toMeters(const std::string& u) {
  if (u.empty()) return 1.0;
  for (const auto& r : kTable)
    if (u == r.name) return r.toMeters;
  return 1.0;
}

}  // namespace units
