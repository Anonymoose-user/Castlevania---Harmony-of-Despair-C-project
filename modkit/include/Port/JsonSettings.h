// Port/JsonSettings.h - the modding settings files as JSON (native port, not
// in the original). Every settings file a mod can ship (data/item/equip_extra,
// data/player/afterimage, data/difficulty/levels, ...) is read as
// <name>.json; jsonSettingsToText turns it into the line format the game's
// readers parse, so each reader stays one simple parser. A <name>.txt is
// still read when there is no .json (mods made before the switch).
//
// Header-only: the player modules (Dll/Player/PlayerTuning.cpp) use it too.
// The JSON shape of each file is chosen by its name (kShapes below) and is
// written by CVHDEdit (tools/cvhdedit/jsonsettings.py, the same table).
#pragma once

#include <ctype.h>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

// Live reload (native/platform/fs.cpp): F5 in the game bumps the generation;
// every settings cache compares it and re-reads its files on the next use.
// Defined in the game executable only (the player modules do not call it).
unsigned settingsGeneration();
void settingsReload();

namespace jsonsettings {

// ---- a small JSON value and parser ------------------------------------------
struct Value {
    enum Kind { Null, Bool, Number, String, Array, Object } kind = Null;
    bool b = false;
    double n = 0.0;
    std::string s;                                         // String; Number keeps its source text
    std::vector<Value> items;                              // Array
    std::vector<std::pair<std::string, Value> > members;   // Object, in file order
};

struct Parser {
    const char* p;
    const char* end;
    const char* start;
    std::string err;

    int line() const
    {
        int l = 1;
        for (const char* q = start; q < p && q < end; q++) l += *q == '\n';
        return l;
    }
    void ws()
    {
        while (p < end && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n')) p++;
    }
    bool fail(const char* what)
    {
        if (err.empty()) err = std::string(what) + " at line " + std::to_string(line());
        return false;
    }
    bool str(std::string& out)
    {
        if (p >= end || *p != '"') return fail("expected a string");
        p++;
        while (p < end && *p != '"') {
            char c = *p++;
            if (c != '\\') { out += c; continue; }
            if (p >= end) break;
            char e = *p++;
            switch (e) {
            case 'n': out += '\n'; break;
            case 't': out += '\t'; break;
            case 'r': out += '\r'; break;
            case 'u': {
                unsigned cp = 0;
                for (int i = 0; i < 4 && p < end; i++, p++) cp = cp * 16 + (unsigned)(isdigit((unsigned char)*p) ? *p - '0' : (tolower(*p) - 'a' + 10));
                if (cp < 0x80) out += (char)cp;
                else if (cp < 0x800) { out += (char)(0xC0 | (cp >> 6)); out += (char)(0x80 | (cp & 0x3F)); }
                else { out += (char)(0xE0 | (cp >> 12)); out += (char)(0x80 | ((cp >> 6) & 0x3F)); out += (char)(0x80 | (cp & 0x3F)); }
                break;
            }
            default: out += e; break;
            }
        }
        if (p >= end) return fail("unterminated string");
        p++;
        return true;
    }
    bool value(Value& v)
    {
        ws();
        if (p >= end) return fail("unexpected end of file");
        char c = *p;
        if (c == '{') {
            v.kind = Value::Object;
            p++;
            ws();
            if (p < end && *p == '}') { p++; return true; }
            for (;;) {
                ws();
                std::string k;
                if (!str(k)) return false;
                ws();
                if (p >= end || *p != ':') return fail("expected ':'");
                p++;
                v.members.push_back(std::make_pair(k, Value()));
                if (!value(v.members.back().second)) return false;
                ws();
                if (p < end && *p == ',') { p++; continue; }
                if (p < end && *p == '}') { p++; return true; }
                return fail("expected ',' or '}'");
            }
        }
        if (c == '[') {
            v.kind = Value::Array;
            p++;
            ws();
            if (p < end && *p == ']') { p++; return true; }
            for (;;) {
                v.items.push_back(Value());
                if (!value(v.items.back())) return false;
                ws();
                if (p < end && *p == ',') { p++; continue; }
                if (p < end && *p == ']') { p++; return true; }
                return fail("expected ',' or ']'");
            }
        }
        if (c == '"') { v.kind = Value::String; return str(v.s); }
        if (end - p >= 4 && std::string(p, 4) == "true") { v.kind = Value::Bool; v.b = true; v.s = "1"; p += 4; return true; }
        if (end - p >= 5 && std::string(p, 5) == "false") { v.kind = Value::Bool; v.s = "0"; p += 5; return true; }
        if (end - p >= 4 && std::string(p, 4) == "null") { v.kind = Value::Null; p += 4; return true; }
        const char* q = p;
        while (q < end && (isdigit((unsigned char)*q) || *q == '-' || *q == '+' || *q == '.' || *q == 'e' || *q == 'E')) q++;
        if (q == p) return fail("unexpected character");
        v.kind = Value::Number;
        v.s.assign(p, q);
        v.n = strtod(v.s.c_str(), 0);
        p = q;
        return true;
    }
};

inline bool parse(const std::string& text, Value& out, std::string& err)
{
    Parser ps;
    ps.start = ps.p = text.data();
    ps.end = text.data() + text.size();
    if (ps.end - ps.p >= 3 && (unsigned char)ps.p[0] == 0xEF) ps.p += 3;   // UTF-8 byte order mark
    if (!ps.value(out)) { err = ps.err; return false; }
    ps.ws();
    if (ps.p != ps.end) { err = "text after the end at line " + std::to_string(ps.line()); return false; }
    return true;
}

// A value as one token of a line ("" for null, 1/0 for true/false).
inline std::string tok(const Value& v)
{
    if (v.kind == Value::Null) return std::string();
    return v.s;
}

inline const Value* member(const Value& o, const std::string& k)
{
    for (size_t i = 0; i < o.members.size(); i++)
        if (o.members[i].first == k) return &o.members[i].second;
    return 0;
}

// ---- the shapes -------------------------------------------------------------
// shape, then for "fields"/"pipe" the field names in line order.
struct Shape {
    const char* file;     // base name, no extension
    const char* shape;
    const char* fields;   // space separated
};

// map_list   {"key": [a, b]}                -> "key a b"
// map_value  {"key": v}                     -> "key v"
// fields     {"key": {f1: .., f2: ..}}      -> "key f1 f2 ..." (missing trailing fields left off)
// map_kv     {"key": {a: 1, b: 2}}          -> "key a=1 b=2"
// kv         {"a": 1}                       -> "a=1"
// pipe       [{f1: .., ...}]                -> "f1 | f2 | ..."
// names      {"kind/i": {"name", "description"}} -> "kind/i=name|description" (new lines as \n)
// sections   {"all": {k: v}, "<name>": {k: v}}  -> "k v", "[name]", "k v"
// shop       {"maxPerPurchase": n, "prices": {"id": price}, "stock": [{"tab", "add"|"remove": "id or
//            first-last", "price", "unlock"} | {"tab", "range": [first, count]} | {"tab", "clear": true}]}
// Any file may instead be an array of strings: the lines themselves.
static const Shape kShapes[] = {
    {"equip_extra", "map_list", ""},
    {"weapon_shot", "map_value", ""},
    {"magic_shot", "fields", "castAs shot vx vy count vyStep dx dy"},
    {"mod_shots", "fields", "opd anim hitW hitH damage life gravity pierce"},
    {"names", "names", ""},
    {"afterimage", "map_kv", ""},
    {"badges", "map_kv", ""},
    {"characters", "map_kv", ""},
    {"unlock", "kv", ""},
    {"exp", "kv", ""},
    {"se_volume", "kv", ""},
    {"levels", "pipe", "name basedOn hp atk def levelPlus unlockAfter enemySpeed bossSpeed"},
    {"drops", "pipe", "source item rate rare character level mode"},
    {"chest_types", "pipe", "type color gold"},
    {"music", "pipe", "room stage boss boss2"},
    {"state_anims", "pipe", "character motion anim arg"},
    {"chest_lists", "pipe", "room color level character items"},
    {"item_effects", "pipe", "item atk taken enemyDef skillAtk mpRegen block itemLuck slash strike thrust fire ice lightning light dark curse poison stone"},
    {"rules", "kv", ""},
    {"growth", "pipe", "character levelAtk crit str critMode"},
    {"weapon_tuning", "pipe", "item attackSpeed script"},
    {"enemy_tuning", "pipe", "enemy level moveSpeed attackSpeed shotSpeed"},
    {"hard_attacks", "pipe", "enemy level shot every count pause dx dy xStep speed angle aim range"},
    {"damage_boxes", "pipe", "sprite frame x y w h damage"},
    {"character_slots", "pipe", "id slots equipAll freeSlots deny"},
    {"unlocks", "pipe", "level character item itemName effect"},
    {"commands", "pipe", "name character input mp castAs shot vx vy count vyStep dx dy kind weapon script"},
    {"skill_shot", "fields", "castAs shot vx vy count vyStep dx dy"},
    {"skill_variants", "pipe", "item input kind castAs shot vx vy count vyStep dx dy mp name duration fly weightless speed invuln attackW attackH attackDmg drain toggle animIn animIdle animMove animOut timeIn timeOut lookShot dash"},
    {"movement", "sections", ""},
    {"shop_stock", "shop", ""},
};

inline const Shape* shapeOf(const std::string& base)
{
    for (size_t i = 0; i < sizeof(kShapes) / sizeof(kShapes[0]); i++)
        if (base == kShapes[i].file) return &kShapes[i];
    return 0;
}

inline std::vector<std::string> split(const char* s)
{
    std::vector<std::string> out;
    std::string cur;
    for (; *s; s++) {
        if (*s == ' ') { if (!cur.empty()) out.push_back(cur); cur.clear(); }
        else cur += *s;
    }
    if (!cur.empty()) out.push_back(cur);
    return out;
}

// JSON text of settings file `base` (its name without .json) -> the line
// format. False (with err) when it is not valid JSON or not that file's shape.
inline bool toText(const std::string& base, const std::string& json, std::string& out, std::string& err)
{
    Value root;
    if (!parse(json, root, err)) return false;
    out.clear();
    if (root.kind == Value::Array && (root.items.empty() || root.items[0].kind == Value::String)) {
        for (size_t i = 0; i < root.items.size(); i++) out += tok(root.items[i]) + "\n";
        return true;
    }
    const Shape* sh = shapeOf(base);
    if (sh == 0) { err = "no JSON layout is known for " + base; return false; }
    std::string s = sh->shape;
    std::vector<std::string> f = split(sh->fields);
    if (s == "pipe") {
        if (root.kind != Value::Array) { err = "expected a list [ ... ]"; return false; }
        for (size_t i = 0; i < root.items.size(); i++) {
            std::string line;
            for (size_t k = 0; k < f.size(); k++) {
                const Value* v = member(root.items[i], f[k]);
                line += (k ? " | " : "") + (v ? tok(*v) : std::string());
            }
            out += line + "\n";
        }
        return true;
    }
    if (root.kind != Value::Object) { err = "expected an object { ... }"; return false; }
    if (s == "shop") {
        if (const Value* m = member(root, "maxPerPurchase")) out += "maxPerPurchase " + tok(*m) + "\n";
        if (const Value* pr = member(root, "prices"))
            for (size_t i = 0; i < pr->members.size(); i++) out += "price " + pr->members[i].first + " " + tok(pr->members[i].second) + "\n";
        const Value* st = member(root, "stock");
        for (size_t i = 0; st && i < st->items.size(); i++) {
            const Value& e = st->items[i];
            const Value* tab = member(e, "tab");
            const Value* add = member(e, "add");
            const Value* rem = member(e, "remove");
            const Value* rng = member(e, "range");
            const Value* clr = member(e, "clear");
            std::string line = "tab " + (tab ? tok(*tab) : std::string("0"));
            if (add) line += " add " + tok(*add);
            else if (rem) line += " remove " + tok(*rem);
            else if (rng && rng->items.size() == 2) { out += line + " range " + tok(rng->items[0]) + " " + tok(rng->items[1]) + "\n"; continue; }
            else if (clr && clr->b) { out += line + " clear\n"; continue; }
            else continue;
            if (const Value* pr = member(e, "price")) line += " price " + tok(*pr);
            if (const Value* un = member(e, "unlock")) line += " unlock " + tok(*un);
            out += line + "\n";
        }
        return true;
    }
    for (size_t i = 0; i < root.members.size(); i++) {
        const std::string& key = root.members[i].first;
        const Value& v = root.members[i].second;
        if (s == "map_list") {
            std::string line = key;
            for (size_t k = 0; k < v.items.size(); k++) line += " " + tok(v.items[k]);
            if (v.kind != Value::Array) line += " " + tok(v);
            out += line + "\n";
        } else if (s == "map_value" || s == "kv") {
            out += key + (s == "kv" ? "=" : " ") + tok(v) + "\n";
        } else if (s == "fields") {
            std::string line = key;
            std::vector<std::string> vals;
            for (size_t k = 0; k < f.size(); k++) {
                const Value* fv = member(v, f[k]);
                vals.push_back(fv ? tok(*fv) : std::string());
            }
            while (!vals.empty() && vals.back().empty()) vals.pop_back();
            for (size_t k = 0; k < vals.size(); k++) line += " " + (vals[k].empty() ? std::string("0") : vals[k]);
            out += line + "\n";
        } else if (s == "map_kv") {
            std::string line = key;
            for (size_t k = 0; k < v.members.size(); k++) line += " " + v.members[k].first + "=" + tok(v.members[k].second);
            out += line + "\n";
        } else if (s == "names") {
            const Value* n = member(v, "name");
            const Value* d = member(v, "description");
            std::string desc = d ? tok(*d) : std::string();
            std::string esc;
            for (size_t k = 0; k < desc.size(); k++) esc += desc[k] == '\n' ? std::string("\\n") : std::string(1, desc[k]);
            out += key + "=" + (n ? tok(*n) : std::string()) + "|" + esc + "\n";
        } else if (s == "sections") {
            if (key != "all") out += "[" + key + "]\n";
            for (size_t k = 0; k < v.members.size(); k++) out += v.members[k].first + " " + tok(v.members[k].second) + "\n";
        }
    }
    return true;
}

// The base name of a settings path: ".../afterimage.txt" -> "afterimage".
inline std::string baseName(const std::string& path)
{
    size_t slash = path.find_last_of("/\\");
    std::string b = slash == std::string::npos ? path : path.substr(slash + 1);
    size_t dot = b.find_last_of('.');
    return dot == std::string::npos ? b : b.substr(0, dot);
}

// `txtPath` with its .txt replaced by .json.
inline std::string jsonPathOf(const std::string& txtPath)
{
    size_t dot = txtPath.find_last_of('.');
    size_t slash = txtPath.find_last_of("/\\");
    if (dot == std::string::npos || (slash != std::string::npos && dot < slash)) return txtPath + ".json";
    return txtPath.substr(0, dot) + ".json";
}

// Reads settings file `txtPath` (a host path): its .json when there is one
// (converted to lines), else the .txt itself. Errors go to stderr with the
// file and line. False when neither exists or the JSON is bad.
inline bool readFile(const std::string& txtPath, std::string& out)
{
    std::string jp = jsonPathOf(txtPath);
    FILE* f = fopen(jp.c_str(), "rb");
    if (f != 0) {
        std::string json;
        char buf[4096];
        size_t n;
        while ((n = fread(buf, 1, sizeof(buf), f)) > 0) json.append(buf, n);
        fclose(f);
        std::string err;
        if (toText(baseName(txtPath), json, out, err)) return true;
        fprintf(stderr, "[settings] %s: %s (file ignored)\n", jp.c_str(), err.c_str());
        return false;
    }
    f = fopen(txtPath.c_str(), "rb");
    if (f == 0) return false;
    out.clear();
    char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) out.append(buf, n);
    fclose(f);
    return true;
}

}  // namespace jsonsettings
