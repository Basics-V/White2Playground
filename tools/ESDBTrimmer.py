# No REGEX solution will ever be enough.
# Run nm on the elf and shove that into the final_matches
# if you want an accurate response.
# Sincerely, MCMi460.
from re import sub, findall, DOTALL
from argparse import ArgumentParser
from pathlib import Path
from yaml import load, SafeLoader

DECLARATION_PATTERN = r"\b[A-Za-z_][A-Za-z0-9_<>:]*\s+([A-Za-z_][A-Za-z0-9_]*)\s*(?:\([^)]*\)\s*[{;]|;)"
CALL_PATTERN = r"\b(?!(?:if|while|for|switch|return|void|int|char|else|catch)\b)([A-Za-z_][A-Za-z0-9_]*)\s*\("
STANDALONE_PATTERN = r"\bFULL_COPY_[a-zA-Z0-9_]*"

# (Not a catch-all blacklist... needs manual correction *often*)
blacklist = ["volatile", "callFunc", "sizeof", "printf", "Printf", "func", "args"]
final_matches = []

def sanitize(item):
    item = item.replace(
        "THUMB_BRANCH_LINK_", ""
    ).replace(
        "THUMB_BRANCH_SAFESTACK_", ""
    ).replace(
        "THUMB_BRANCH_", ""
    ).replace(
        "FULL_COPY_", ""
    ).replace(
        "ARM_BRANCH_LINK_", ""
    ).replace(
        "ARM_BRANCH_", ""
    )
    if item.split("_")[-1].startswith("0x"):
        item = "_".join(item.split("_")[:-1])
    if not item in blacklist and not item in final_matches:
        final_matches.append(item)

def parse_cpp(file_path):
    with open(file_path, "r") as file:
        code = sub(
            r"'.*?'", "''", sub(
                r'".*?"', '""', sub(
                    r"/\*.*?\*/", "", sub(
                        r"//.*", "",
                        file.read()),
                    flags = DOTALL)
                )
            )

    declarations = findall(DECLARATION_PATTERN, code)
    calls = findall(CALL_PATTERN, code)
    stand_alones = findall(STANDALONE_PATTERN, code)
    for item in set(declarations + calls + stand_alones):
        sanitize(item)

def parse_asm(file_path):
    with open(file_path, "r") as file:
        code = file.read()

    refs = []
    for line in code.split("\n"):
        if line.startswith("@"):
            continue
        elif line.startswith("FULL_COPY_") and line.endswith(":"):
            refs.append(line.strip().rstrip(":"))
    for ref in set(refs):
        sanitize(ref)

def parse_esdbs(esdb_paths, curate = True):
    esdb = {"Segments":[],"Symbols":[]}
    for path in esdb_paths:
        with open(path, "r") as file:
            temp = load(file, Loader = SafeLoader)
            final = {"Segments":[],"Symbols":[]}
            extant_segs = 0
            seg_id_kv = {}
            # Sanitize segments
            for segment in temp["Segments"]:
                if segment["Type"] not in ("EXECUTABLE", "OVERLAY"):
                    continue
                seg_name = segment["Name"]
                try: seg_name = int(seg_name.lstrip("OVL_"))
                except: pass
                if segment["Type"] == "OVERLAY" and not isinstance(seg_name, int):
                    continue # _BSS?
                exists = False
                for segs in esdb["Segments"]:
                    if segs["Name"] == seg_name:
                        final["Segments"].append(
                            {
                                "Name": seg_name,
                                "Type": segment["Type"],
                                "ID": segs["ID"],
                            }
                        )
                        extant_segs += 1
                        exists = True
                        break
                if not exists:
                    final["Segments"].append(
                        {
                            "Name": seg_name,
                            "Type": segment["Type"],
                            "ID": len(final["Segments"]) + len(esdb["Segments"]) - extant_segs,
                        }
                    )
                seg_id_kv[segment["ID"]] = final["Segments"][-1]["ID"]
            
            # Sanitize symbols
            for symbol in temp["Symbols"]:
                # Symbol does not match with a useful segment
                new_seg = seg_id_kv.get(symbol["Segment"], None)
                if new_seg is None:
                    continue
                # Useless symbols
                if symbol["Name"][:4] in ("FUN_", "DAT_", "LAB_", "off_", "loc_", "sub_", "PTR_"):
                    continue
                if not isinstance(symbol["Address"], int):
                    raise ValueError("symbol %s has a non-int address" % symbol["Name"])
                exists = False
                for syms in esdb["Symbols"]:
                    if syms["Address"] == symbol["Address"]:
                        if syms["Segment"] == new_seg:
                            exists = True
                            break
                if not exists:
                    final["Symbols"].append(
                        {
                            "Name": symbol["Name"],
                            "Segment": new_seg,
                            "Address": symbol["Address"],
                        }
                    )

            # Add all of the above to our final ESDB
            #esdb["Segments"] += final["Segments"]
            for fin_seg in final["Segments"]:
                found = False
                for seg in esdb["Segments"]:
                    if fin_seg["ID"] == seg["ID"]:
                        found = True
                        break
                if not found:
                    esdb["Segments"].append(fin_seg)
            esdb["Symbols"] += final["Symbols"]

    if not curate:
        return esdb

    segments = []
    out = {"Segments":[], "Symbols":[]}
    for symbol in esdb["Symbols"]:
        if symbol["Name"] in final_matches or symbol["Name"].startswith("__aeabi"):
            found = False
            for out_sym in out["Symbols"]:
                if out_sym["Name"] == symbol["Name"]:
                    found = True
                    break
            if not found:
                out["Symbols"].append(symbol)
                segments.append(symbol["Segment"])

    segments = set(segments)
    for segment in esdb["Segments"]:
        if segment["ID"] in segments:
            out["Segments"].append(segment)

    # Sort
    out["Segments"] = sorted(out["Segments"], key = lambda el: el["Name"] if isinstance(el["Name"], int) else -1)
    for n, el in enumerate(out["Segments"]):
        to_match = el["ID"]
        el["ID"] = n
        for symbol in out["Symbols"]:
            if symbol["Segment"] == to_match:
                symbol["updated_segment"] = n
    out["Symbols"] = sorted(out["Symbols"], key = lambda el: (el["updated_segment"], el["Address"]))

    return out

def output_yml(file_path, esdb):
    with open(file_path, "w") as file:
        file.write("Segments:\n")
        for segment in esdb["Segments"]:
            file.write("  - ID: 0x%X\n" % segment["ID"])
            file.write("    Name: %s\n" % segment["Name"])
            file.write("    Type: %s\n" % segment["Type"])
        
        file.write("\nSymbols:\n")
        for symbol in esdb["Symbols"]:
            file.write("  - Name: %s\n" % symbol["Name"])
            file.write("    Segment: 0x%X\n" % symbol.get("updated_segment", symbol["Segment"]))
            file.write("    Address: 0x%X\n" % symbol["Address"])

if __name__ == "__main__":
    parser = ArgumentParser(description = "Trims an ESDB file based on specified source files")

    parser.add_argument(
        "-i", "--input", 
        type = str,
        required = True,
        action = "append",
        help = "path to input ESDB(s) (.yml)"
    )
    parser.add_argument(
        "-o", "--output", 
        type = str,
        required = True,
        help = "path to output ESDB (.yml)"
    )
    parser.add_argument(
        "-s", "--source", 
        type = str,
        required = True,
        action = "append",
        help = "path to source(s) (.c/cpp/s)"
    )

    args = parser.parse_args()

    # Read the source files
    for src in [ Path(src) for src in args.source ]:
        match src.suffix:
            case ".cpp" | ".c":
                parse_cpp(src.resolve())
            case ".s":
                parse_asm(src.resolve())
            case _:
                raise ValueError("unknown file type of file: %s" % src.resolve())

    # Read the ESDBs
    final_esdb = parse_esdbs([ Path(esdb) for esdb in args.input ])

    # Write the ESDB
    output_yml(args.output, final_esdb)
