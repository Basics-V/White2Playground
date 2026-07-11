from re import sub, findall, DOTALL
from argparse import ArgumentParser
from pathlib import Path
from yaml import load, SafeLoader

DECLARATION_PATTERN = r"\b[A-Za-z_][A-Za-z0-9_<>:]*\s+([A-Za-z_][A-Za-z0-9_]*)\s*\([^)]*\)\s*[{;]"
CALL_PATTERN = r"\b(?!(?:if|while|for|switch|return|void|int|char|else|catch)\b)([A-Za-z_][A-Za-z0-9_]*)\s*\("
STANDALONE_PATTERN = r"\bFULL_COPY_[a-zA-Z0-9_]*"

blacklist = ["volatile", "callFunc", "sizeof", "printf", "Printf", "vsnprintf"]
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

def strip_comments(text):
    text = sub(r"//.*", "", text)
    text = sub(r"/\*.*?\*/", "", text, flags = DOTALL)
    return text

def parse_cpp(file_path):
    with open(file_path, "r") as file:
        code = strip_comments(file.read())

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

def curate_yml(esdb_paths):
    esdb = {}
    for path in esdb_paths:
        with open(path, "r") as file:
            esdb |= load(file, Loader = SafeLoader)

    segments = []
    out = {"Segments":[], "Symbols":[]}
    for symbol in esdb["Symbols"]:
        if symbol["Name"] in final_matches or symbol["Name"].startswith("__aeabi"):
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
            file.write("    Segment: 0x%X\n" % symbol["updated_segment"])
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
    final_esdb = curate_yml([ Path(esdb) for esdb in args.input ])

    # Write the ESDB
    output_yml(args.output, final_esdb)
