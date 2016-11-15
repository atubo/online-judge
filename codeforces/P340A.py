#!/usr/bin/python
def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

(x, y, a, b) = map(lambda x: int(x), raw_input().split())
g = gcd(x, y)
z = (x/g) * (y/g) * g
print b//z - (a-1)//z
