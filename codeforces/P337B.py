#!/usr/bin/python
from fractions import Fraction

[a, b, c, d] = map(lambda x: int(x), raw_input().split())
if a * d < b * c:
    (a, b) = (b, a)
    (c, d) = (d, c)
r = Fraction(a*d - b*c, a*d)
print "0/1" if r == 0 else r
