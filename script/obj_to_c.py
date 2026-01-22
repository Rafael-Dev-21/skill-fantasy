import sys

def convert_obj_to_c(filename, varname):
    verts = []
    faces = []
    tfacs = []
    texcs1 = []

    with open(filename, 'r') as f:
        for line in f:
            if line.startswith('v '):
                verts.append(line.strip().split()[1:])
            elif line.startswith('vt '):
                texcs1.append(line.strip().split()[1:])
            elif line.startswith('f '):
                face = [f.strip().split('/')[0] for f in line.strip().split()[1:]]
                tfac = [f.strip().split('/')[1] for f in line.strip().split()[1:]]
                faces.extend([int(x) - 1 for x in face])
                tfacs.extend([int(x) - 1 for x in tfac])

    texcs = len(texcs1) * [None]
    for i in range(0, len(faces), 1):
        texcs[faces[i]] = texcs1[tfacs[i]]
    print("#include \"vec.h\"")
    print("#include \"model.h\"")
    print(f"static const v3 {varname}_verts[] = {{")
    for v in verts:
        print(f"  {{ {v[0]}, {v[1]}, {v[2]} }},")
    print("};")
    print(f"static const v2 {varname}_texcs[] = {{")
    for t in texcs:
        if (t): print(f"  {{ {t[0]}, {t[1]} }},")
    print("};")
    print(f"static const size_t {varname}_faces[] = {{")
    for i in range(0, len(faces), 3):
        print(f"  {faces[i+0]}, {faces[i+1]}, {faces[i+2]},")
    print("};")
    print(f"const Model {varname} = {{")
    print(f"  .vert = (v3*) {varname}_verts,")
    print(f"  .texc = (v2*) {varname}_texcs,")
    print(f"  .face = (size_t*) {varname}_faces,")
    print(f"  .vcount = {len(verts)},")
    print(f"  .fcount = {len(faces)},")
    print("};");


if __name__ == "__main__":
    convert_obj_to_c(sys.argv[1], sys.argv[2])
