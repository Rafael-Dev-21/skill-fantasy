import math

tables = [
    { "name": "cos", "fn": math.cos, "ab": True },
    { "name": "sin", "fn": math.sin, "ab": True },
#    { "name": "tan", "fn": math.tan },
]


#print("class Tables {")

#for item in tables:
#    print(f"  private static final int[] {item['name']} = new int[] {'{'}")
#    for i in range(0, 256):
#        x = i / 128 * math.pi
#        val = int(item['fn'](x)*256)
#        if i == 255:
#            print(f"    {val}")
#        else:
#            print(f"    {val},")
#    print("  };")

#    print(f"  public static final int {item['name']}(int x) {'{'}")
#    print(f"    return {item['name']}[x&255];")
#    print("  }")

#print("}")

print("#include \"lut.h\"")

for item in tables:
    print(f"const int {item['name']}_lut[256] = {'{'}")
    for i in range(0, 256):
        x = i / 128.0 * math.pi if item['ab'] else i / 128.0 - 1
        val = int(item['fn'](x)*256) if item['ab'] else int(item['fn'](x)*128/math.pi)
        if i == 255:
            print(f"  {val}")
        else:
            print(f"  {val},")
    print("};")

    print(f"int lut_{item['name']}8(int x)")
    print("{")
    print(f"  return {item['name']}_lut[x&255];")
    print("}")

    print(f"int lut_{item['name']}16(int x)")
    print("{")
    print("int t, y, a, b;");
    print("  t = x & 255;")
    print("  y = x >> 8;")
    print(f"  a = lut_{item['name']}8(y);")
    print(f"  b = lut_{item['name']}8(y+1);")
    print("  return (a * (256 - t) / 256) + (b * t / 256);")
    print("}")
