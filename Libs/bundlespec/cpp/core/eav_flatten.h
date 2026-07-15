// Native property-tree value model + EAV flatten — a faithful port of
// Speckle.Sdk EavExtraction.FlattenProperties / WalkPropertiesNative (the Dictionary
// path). Same paths, {name,value} parameter handling, units/idn, Material Quantities,
// MAX_DEPTH, depth-0 exclusions, and the InferType/ToText/ToNum quirks.
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <charconv>
#include <cmath>
#include <cstdint>
#include <cctype>

// ── value model ──────────────────────────────────────────────────────────────
struct PDict;
enum class VT : uint8_t { Null, Bool, Long, Double, Float, Str, Dict };

struct PVal {
  VT t = VT::Null;
  bool b = false;
  long long i = 0;
  double d = 0;
  float f = 0;
  std::string s;
  std::shared_ptr<PDict> dict;

  static PVal Bool(bool v) {
    PVal p;
    p.t = VT::Bool;
    p.b = v;
    return p;
  }
  static PVal Long(long long v) {
    PVal p;
    p.t = VT::Long;
    p.i = v;
    return p;
  }
  static PVal Dbl(double v) {
    PVal p;
    p.t = VT::Double;
    p.d = v;
    return p;
  }
  static PVal Flt(float v) {
    PVal p;
    p.t = VT::Float;
    p.f = v;
    return p;
  }
  static PVal Str(std::string v) {
    PVal p;
    p.t = VT::Str;
    p.s = std::move(v);
    return p;
  }
  static PVal Map(std::shared_ptr<PDict> v) {
    PVal p;
    p.t = VT::Dict;
    p.dict = std::move(v);
    return p;
  }

  bool isScalar() const {
    return t == VT::Bool || t == VT::Long || t == VT::Double ||
           t == VT::Float || t == VT::Str;
  }
};

struct PDict {
  std::vector<std::pair<std::string, PVal>>
      items;  // insertion order (Dictionary parity)

  bool contains(const std::string& k) const {
    for (auto& kv : items)
      if (kv.first == k) return true;
    return false;
  }
  const PVal* find(const std::string& k) const {
    for (auto& kv : items)
      if (kv.first == k) return &kv.second;
    return nullptr;
  }
  // first-writer-wins (managed TryAdd)
  void tryAdd(const std::string& k, PVal v) {
    if (contains(k)) return;
    items.emplace_back(k, std::move(v));
  }
  void set(const std::string& k, PVal v) {
    for (auto& kv : items)
      if (kv.first == k) {
        kv.second = std::move(v);
        return;
      }
    items.emplace_back(k, std::move(v));
  }
  void remove(const std::string& k) {
    for (auto it = items.begin(); it != items.end(); ++it)
      if (it->first == k) {
        items.erase(it);
        return;
      }
  }
};

// ── eav row ──────────────────────────────────────────────────────────────────
struct EavRow {
  std::string path;
  std::string valueText;
  std::optional<double> valueNum;
  std::string type;  // "string" | "number" | "boolean"
  std::optional<std::string> units;
  std::optional<std::string> idn;
};

namespace eav {

constexpr int MAX_DEPTH = 10;

inline bool isFinite(double d) { return !std::isnan(d) && !std::isinf(d); }

// regex ".-.-" : any char, '-', any char, '-'  (rejects UUID-like from numeric inference)
inline bool uuidLike(const std::string& s) {
  for (size_t i = 0; i + 3 < s.size(); ++i)
    if (s[i + 1] == '-' && s[i + 3] == '-') return true;
  return false;
}

inline std::string toLowerAscii(const std::string& s) {
  std::string o = s;
  for (auto& c : o) c = (char)std::tolower((unsigned char)c);
  return o;
}

inline std::string trim(const std::string& s) {
  size_t a = 0, b = s.size();
  while (a < b && std::isspace((unsigned char)s[a])) ++a;
  while (b > a && std::isspace((unsigned char)s[b - 1])) --b;
  return s.substr(a, b - a);
}

// .NET double/float .ToString("R"): shortest round-trippable digits, formatted fixed when the
// scientific exponent E is in [-4, upper) (upper=15 double / 7 float — matches .NET's G/R rule),
// else scientific with uppercase 'E', explicit sign, >=2 exponent digits.
template <typename T>
inline std::string numToR(T v) {
  if (v == 0) return "0";
  bool neg = v < 0;
  char buf[64];
  auto res = std::to_chars(buf, buf + sizeof(buf), neg ? -v : v,
                           std::chars_format::scientific);
  std::string sci(buf, res.ptr);  // e.g. "3e-04", "1.5e+00"
  size_t epos = sci.find('e');
  std::string mant = sci.substr(0, epos);
  int E = std::stoi(sci.substr(epos + 1));
  std::string digits;
  for (char c : mant)
    if (c != '.') digits += c;
  int nd = (int)digits.size();
  int upper = sizeof(T) == 4 ? 7 : 15;

  std::string out;
  if (E >= -4 && E < upper) {
    int pointPos = E + 1;  // digits before the decimal point
    if (pointPos <= 0)
      out = "0." + std::string((size_t)(-pointPos), '0') + digits;
    else if (pointPos >= nd)
      out = digits + std::string((size_t)(pointPos - nd), '0');
    else
      out = digits.substr(0, pointPos) + "." + digits.substr(pointPos);
  } else {
    out = digits.substr(0, 1);
    if (nd > 1) out += "." + digits.substr(1);
    int ae = E < 0 ? -E : E;
    std::string es = std::to_string(ae);
    if (es.size() < 2) es = "0" + es;
    out += "E";
    out += (E < 0 ? '-' : '+');
    out += es;
  }
  return neg ? "-" + out : out;
}

inline bool tryParseDouble(const std::string& s, double& out) {
  std::string t = trim(s);
  if (t.empty()) return false;
  // allow leading + (to_chars/from_chars rejects '+')
  const char* p = t.c_str();
  if (*p == '+') ++p;
  auto end = t.c_str() + t.size();
  auto res = std::from_chars(p, end, out);
  return res.ec == std::errc() && res.ptr == end && isFinite(out);
}

inline std::string inferType(const PVal& v) {
  switch (v.t) {
    case VT::Bool:
      return "boolean";
    case VT::Double:
      return isFinite(v.d) ? "number" : "string";
    case VT::Float:
      return isFinite(v.f) ? "number" : "string";
    case VT::Long:
      return "number";
    case VT::Str: {
      std::string lower = toLowerAscii(v.s);
      if (lower == "true" || lower == "false") return "boolean";
      std::string t = trim(v.s);
      if (t.empty() || uuidLike(t)) return "string";
      double d;
      return tryParseDouble(t, d) ? "number" : "string";
    }
    default:
      return "string";
  }
}

inline std::string toText(const PVal& v) {
  switch (v.t) {
    case VT::Bool:
      return v.b ? "true" : "false";
    case VT::Str:
      return v.s;
    case VT::Double:
      return numToR(v.d);
    case VT::Float:
      return numToR(v.f);
    case VT::Long:
      return std::to_string(v.i);
    default:
      return "";
  }
}

inline std::optional<double> toNum(const PVal& v) {
  switch (v.t) {
    case VT::Long:
      return (double)v.i;
    case VT::Double:
      return isFinite(v.d) ? std::optional<double>(v.d) : std::nullopt;
    case VT::Float:
      return isFinite(v.f) ? std::optional<double>((double)v.f) : std::nullopt;
    case VT::Str: {
      double d;
      return tryParseDouble(v.s, d) ? std::optional<double>(d) : std::nullopt;
    }
    default:
      return std::nullopt;
  }
}

inline void makeRow(const std::string& path, const PVal& v,
                    std::optional<std::string> units,
                    std::optional<std::string> idn, std::vector<EavRow>& rows) {
  std::string type = inferType(v);
  std::optional<double> num = (type == "number") ? toNum(v) : std::nullopt;
  rows.push_back(
      EavRow{path, toText(v), num, type, std::move(units), std::move(idn)});
}

// Producer-shape options. The defaults reproduce the Revit/Navis-shaped walk the
// managed SDK defined (and the converters baseline depends on); producers whose
// property trees are user-definable (archicad) disable the key-name special-cases
// so a user group that happens to be called "Material Quantities" isn't swallowed.
struct WalkOptions {
  // Skip {…}.Type Parameters.Structure subtrees (Revit type-parameter noise).
  bool skipTypeParamsStructure = true;
  // Treat a depth-anywhere "Material Quantities" dict as reserved: walk() skips it
  // and flatten() emits it through the dedicated materialQuantities() shape.
  bool materialQuantitiesSpecialCase = true;
};

inline void walk(const PDict& obj, const std::string& prefix, int depth,
                 std::vector<EavRow>& rows,
                 const std::vector<std::string>* excluded,
                 const WalkOptions& opts = WalkOptions()) {
  if (depth >= MAX_DEPTH) return;
  for (const auto& kv : obj.items) {
    const std::string& key = kv.first;
    const PVal& val = kv.second;

    if (depth == 0 && excluded) {
      bool skip = false;
      for (auto& e : *excluded)
        if (e == key) {
          skip = true;
          break;
        }
      if (skip) continue;
    }
    if (val.t == VT::Null) continue;

    std::string path = prefix + "." + key;

    if (val.t == VT::Dict) {
      const PDict& rec = *val.dict;
      // parameter pattern { name, value }
      const PVal* nameV = rec.find("name");
      const PVal* valueV = rec.find("value");
      if (nameV && valueV) {
        if (!valueV->isScalar()) continue;
        std::optional<std::string> units, idn;
        if (const PVal* u = rec.find("units"); u && u->t == VT::Str)
          units = u->s;
        if (const PVal* i = rec.find("internalDefinitionName");
            i && i->t == VT::Str)
          idn = i->s;
        makeRow(path, *valueV, units, idn, rows);
        continue;
      }
      if (opts.skipTypeParamsStructure && key == "Structure" &&
          prefix.size() >= 16 &&
          prefix.compare(prefix.size() - 16, 16, ".Type Parameters") == 0)
        continue;
      if (opts.materialQuantitiesSpecialCase && key == "Material Quantities")
        continue;  // handled separately (flatten()'s materialQuantities pass)
      walk(rec, path, depth + 1, rows, nullptr, opts);
      continue;
    }

    if (val.isScalar()) makeRow(path, val, std::nullopt, std::nullopt, rows);
  }
}

// Material Quantities (Revit): properties.Material Quantities.{cat}.{matName}.{area|volume}
inline void materialQuantities(const PDict& mq, std::vector<EavRow>& rows) {
  for (const auto& mp : mq.items) {
    if (mp.second.t != VT::Dict) continue;
    const PDict& mat = *mp.second.dict;
    std::string category = "Unknown";
    if (const PVal* c = mat.find("materialCategory"); c && c->t == VT::Str)
      category = c->s;
    for (const char* kind : {"area", "volume"}) {
      const PVal* q = mat.find(kind);
      if (!q || q->t != VT::Dict) continue;
      const PVal* value = q->dict->find("value");
      if (!value || !value->isScalar()) continue;
      std::optional<std::string> units;
      if (const PVal* u = q->dict->find("units"); u && u->t == VT::Str)
        units = u->s;
      makeRow("properties.Material Quantities." + category + "." + mp.first +
                  "." + kind,
              *value, units, std::nullopt, rows);
    }
  }
}

// FlattenProperties: rootScalars (bare paths) + walk under "properties." + Material Quantities.
inline void flatten(
    const PDict& properties,
    const std::vector<std::pair<std::string, PVal>>& rootScalars,
    const std::vector<std::string>* excluded, std::vector<EavRow>& rows,
    const WalkOptions& opts = WalkOptions()) {
  for (const auto& kv : rootScalars)
    if (kv.second.isScalar())
      makeRow(kv.first, kv.second, std::nullopt, std::nullopt, rows);

  walk(properties, "properties", 0, rows, excluded, opts);

  if (opts.materialQuantitiesSpecialCase) {
    if (const PVal* mq = properties.find("Material Quantities");
        mq && mq->t == VT::Dict)
      materialQuantities(*mq->dict, rows);
  }
}

}  // namespace eav
