#!/usr/bin/python

def main():
    N, K = map(lambda(x): int(x), raw_input().split())
    if K == 1:
        print N
        return
    A = map(lambda(x): int(x), raw_input().split())
    d = {x: True for x in A}
    ret = 0
    for x in sorted(d):
        if d[x]:
            ret += 1
            if x * K in d:
                d[x * K] = False
    print ret

main()
