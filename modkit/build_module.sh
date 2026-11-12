#!/bin/sh
# Build one game module DLL with the CVHD modding kit (Git Bash):
#   sh build_module.sh <player|enemy|shot> <source folder> <dll name> [output folder]
# Writes <output folder>/<dll name>.dll and .pdb (default: the current folder).
set -e
export MSYS2_ARG_CONV_EXCL='*'
[ $# -ge 3 ] || { echo "usage: sh build_module.sh <player|enemy|shot> <source folder> <dll name> [output folder]"; exit 1; }
fam=$1; src=$(cd "$2" && pwd); name=$3; out=${4:-.}
KIT=$(cd "$(dirname "$0")" && pwd)
case "$fam" in player|enemy|shot) ;; *) echo "family must be player, enemy or shot"; exit 1 ;; esac
# find LLVM
LLVM="${LLVM_BIN:-/c/Program Files/LLVM/bin}"
if [ ! -x "$LLVM/clang-cl.exe" ]; then
    p=$(command -v clang-cl.exe 2>/dev/null || command -v clang-cl 2>/dev/null || true)
    [ -n "$p" ] && LLVM=$(dirname "$p") || { echo "ERROR: LLVM not found. Install LLVM (clang-cl, lld-link) to C:/Program Files/LLVM or put its bin folder on PATH."; exit 1; }
fi
for t in clang-cl lld-link llvm-nm; do [ -x "$LLVM/$t.exe" ] || { echo "ERROR: $LLVM/$t.exe missing"; exit 1; }; done
w() { cygpath -m "$1"; }
mkdir -p "$out"; out=$(cd "$out" && pwd)
obj="$out/obj_$name"; mkdir -p "$obj"
CF="-nologo -c -Z7 -O1 -std:c++17 -EHsc -Wno-everything -DCVHD_NATIVE=1 -DCVHD_MODULE=1 -MTd -D_DEBUG"
INC1="-I$(w "$KIT/include")"; INC2="-I$(w "$src")"
list="$obj/sources.txt"
find "$src" -name '*.cpp' > "$list"
[ "$fam" = player ] && echo "$KIT/src/PlayerTuning.cpp" >> "$list"
[ -s "$list" ] || { echo "no .cpp files in $src"; exit 1; }
exports="-export:cvhdModuleInit"
set --
while IFS= read -r f; do
    o="$obj/$(basename "$f").obj"
    echo "compile $(basename "$f")"
    "$LLVM/clang-cl.exe" $CF "$INC1" "$INC2" "$(w "$f")" -Fo"$(w "$o")" </dev/null
    "$LLVM/llvm-nm.exe" --defined-only "$(w "$o")" </dev/null | grep -q ' T cvhdModuleShutdown$' && exports="$exports -export:cvhdModuleShutdown"
    set -- "$@" "$(w "$o")"
done < "$list"
# image base: relocatable, above 4 GB, one 2 MB slot from the name (game uses 0x2..., editor 0x3/0x4...)
crc=$(printf '%s' "$name" | cksum | cut -d' ' -f1)
base=$(printf '0x%X' $((0x500000000 + (crc % 120) * 0x200000)))
echo "link $name.dll (base $base)"
"$LLVM/lld-link.exe" -nologo -dll -debug -out:"$(w "$out/$name.dll")" $exports -base:$base -dynamicbase \
    -highentropyva:no -largeaddressaware "$@" "$(w "$KIT/lib/cvhd_$fam.lib")" libcmtd.lib libcpmtd.lib kernel32.lib
rm -f "$out/$name.lib" "$out/$name.exp"
echo "built $out/$name.dll"
