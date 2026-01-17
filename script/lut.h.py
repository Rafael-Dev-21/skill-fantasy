import math

tables = [
    { "name": "cos" },
    { "name": "sin" },
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

print("#pragma once")

for item in tables:
    print(f"int lut_{item['name']}8(int x);")
    print(f"int lut_{item['name']}16(int x);")
