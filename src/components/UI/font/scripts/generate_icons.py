import json
import os
from pathlib import Path

ICONS_DIR = Path("../font_icons/json")
OUT_HEADER = Path("../../include/icons.h")
OUT_LOCK = Path("icons.lock.json")
OUT_SYMBOLS = Path("icons.symbols.txt")


def parse_codepoint(cp: str) -> int:
    if not cp.startswith("U+"):
        raise ValueError(f"Invalid codepoint format: {cp}")
    return int(cp[2:], 16)


def codepoint_to_utf8(cp_int: int) -> str:
    return "".join(f"\\x{b:02X}" for b in chr(cp_int).encode("utf-8"))


icons_global = {}
symbols_set = set()

for file in ICONS_DIR.glob("*.icons.json"):
    domain = file.stem.replace(".icons", "")
    with open(file, "r", encoding="utf-8") as f:
        data = json.load(f)

    for name, entry in data.items():
        if "codepoint" not in entry:
            raise RuntimeError(f"{file}: missing codepoint for {name}")

        cp_str = entry["codepoint"]
        cp_int = parse_codepoint(cp_str)

        key = f"{domain}.{name}"
        icons_global[key] = {
            "domain": domain,
            "name": name,
            "codepoint": cp_str,
            "codepoint_int": cp_int
        }

        symbols_set.add(cp_int)

# ---------- icons.lock.json ----------
with open(OUT_LOCK, "w", encoding="utf-8") as f:
    json.dump(
        {
            "icons": icons_global,
            "symbols": sorted(symbols_set)
        },
        f,
        indent=2
    )

# ---------- icons.h ----------
with open(OUT_HEADER, "w", encoding="utf-8") as f:
    f.write("// AUTO-GENERATED FILE — DO NOT EDIT\n\n")
    f.write("#pragma once\n\n")

    for icon in sorted(icons_global.values(), key=lambda x: (x["domain"], x["name"])):
        macro = f'ICON_{icon["domain"].upper()}_{icon["name"].upper()}'
        utf8 = codepoint_to_utf8(icon["codepoint_int"])
        f.write(f'#define {macro} "{utf8}"\n')

# ---------- icons.symbols.txt ----------
with open(OUT_SYMBOLS, "w", encoding="utf-8") as f:
    f.write(",".join(f"0x{cp:X}" for cp in sorted(symbols_set)))

print("Icons generated:")
print(f" - {OUT_HEADER}")
print(f" - {OUT_LOCK}")
print(f" - {OUT_SYMBOLS}")

