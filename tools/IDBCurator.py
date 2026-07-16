from sys import stdin

segments = []
symbols = []

funcIdx = 0

def new_segment(start, a, end, b, name):
    del a, b
    stype = "null"
    try:
        int(name.lstrip("OVL_"))
        stype = "OVERLAY"
    except:
        if name == "ARM9":
            stype = "EXECUTABLE"
    segments.append(
        {
            "start": int(start, 16),
            "end": int(end, 16),
            "name": name,
            "id": len(segments),
            "type": stype,
        }
    )

def new_symbol(address, name):
    address = int(address, 16)
    if address == 0:
        return

    # Search for corresponding segment
    segment = None
    for seg in segments:
        if seg["start"] <= address <= seg["end"]:
            segment = seg
    if segment is None:
        #raise AssertionError("0x%X: %s missing segment!" % (address, name))
        return

    # Add symbol
    symbols.append(
        {
            "Address": address,
            "Name": name,
            "Segment": segment,
        }
    )

if __name__ == "__main__":
    for line in stdin:
        line = line.strip()
        if line.isspace():
            continue
        if line.startswith("==>"):
            funcIdx += 1
            continue

        if funcIdx == 1:
            if " - " not in line:
                continue
            new_segment(*line.split(" "))
        elif funcIdx == 2:
            if ": " not in line:
                continue
            new_symbol(*line.split(": "))

    print("Segments:")
    for segment in segments:
        print("  - ID: 0x%X" % segment["id"])
        print("    Name: %s" % segment["name"])
        print("    Type: %s" % segment["type"])

    print()
    print("Symbols:")
    for symbol in symbols:
        print("  - Name: %s" % symbol["Name"])
        print("    Segment: 0x%X" % symbol["Segment"]["id"])
        print("    Address: 0x%X" % symbol["Address"])
