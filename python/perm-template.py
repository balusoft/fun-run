def perm_1(A):
    if not A:
        return [""]
    out = []
    for p in perm_1(A[1:]):
        print("p:", p)
        for i in range(len(A)):
            print("i:", i, "prefix:", p[i:])
            if p[i:] and p[i:][-1] == A[0]:
                continue
            out.append(p[i:] + A[0] + p[:i])

    return out

print("perm: ", [p for p in perm_1("123")])
print("perm: ", sorted([p for p in perm_1("1233")]))