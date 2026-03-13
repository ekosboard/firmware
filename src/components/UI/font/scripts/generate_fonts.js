import fs from "fs";
import { execSync } from "child_process";
import path from "path";

// ------------------------------------------------------------
// Config
// ------------------------------------------------------------

const FONT_TTF = "./SymbolsNerdFontMono-Regular.ttf";
const SYMBOLS_FILE = "./icons.symbols.txt";
const OUTPUT_DIR = "./generated";

const SIZES = [16, 18, 22, 24, 28, 32, 48, 64, 96, 128];
const BPP = 1;

// ------------------------------------------------------------
// Helpers
// ------------------------------------------------------------

function hexToDecimal(str) {
    // "0xE302" -> 58114
    return parseInt(str.trim(), 16);
}

function patchInclude(filePath) {
    let content = fs.readFileSync(filePath, "utf8");

    content = content.replace(
        /#ifdef LV_LVGL_H_INCLUDE_SIMPLE[\s\S]*?#endif/g,
        '#include "UI.h"'
    );

    fs.writeFileSync(filePath, content);
}

// ------------------------------------------------------------
// Load & parse symbols
// ------------------------------------------------------------

const raw = fs.readFileSync(SYMBOLS_FILE, "utf8");

const codepoints = raw
    .split(",")
    .map(s => s.trim())
    .filter(Boolean)
    .map(hexToDecimal);

// sécurité : dédup + tri
const uniqueSorted = [...new Set(codepoints)].sort((a, b) => a - b);

const rangeArg = uniqueSorted.join(",");

console.log(`🔤 ${uniqueSorted.length} symbols loaded`);

// ------------------------------------------------------------
// Ensure output dir
// ------------------------------------------------------------

fs.mkdirSync(OUTPUT_DIR, { recursive: true });

// ------------------------------------------------------------
// Generate fonts
// ------------------------------------------------------------

for (const size of SIZES) {
    const outFile = `symbol_nerdfont_${size}.c`;
    const fallback = `symbol_nerdfont_${size}`;
    const outPath = path.join(OUTPUT_DIR, outFile);

    const cmd = `
npx lv_font_conv \
--bpp ${BPP} \
--size ${size} \
--no-compress \
--font ${FONT_TTF} \
--range ${rangeArg} \
--format lvgl \
-o ${outPath} \
--lv-fallback ${fallback}
`.trim();

    console.log(`🛠️  Generating ${outFile}`);
    execSync(cmd, { stdio: "inherit" });
    patchInclude(outPath);
}

console.log("✅ All fonts generated successfully");

