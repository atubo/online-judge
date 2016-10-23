#!/usr/bin/python
import string
import random
from random import randint
import time
import os

def rand_str(size):
    chars = string.ascii_lowercase;
    return ''.join(random.choice(chars) for _ in range(size))

def rand_array(size, lo=-10000, hi=10000):
    ret = []
    for i in range(size):
        ret.append(random.randint(lo, hi))
    return ret

def rand_unique_array(size, lo=1, hi=100000):
    ret = []
    seen = set()
    for i in range(size):
        x = randint(lo, hi)
        while x in seen:
            x = randint(lo, hi)
        ret.append(x)
        seen.add(x)
    return ret

def print_array(f, a):
    for x in a:
        f.write("%d " % x)
    f.write("\n")

def generate_input(size):
    os.system("rm input.txt")
    #a = rand_str(size)
    #a = rand_array(size)
    with open("input.txt", "w") as f:
        n = size
        m = randint(n, 2*n)
        h = sorted(rand_unique_array(n))
        p = sorted(rand_unique_array(m))
        f.write("%d %d\n" % (n, m))
        print_array(f, h)
        print_array(f, p)


def one_test(size):
    generate_input(size)
    os.system("bench <input.txt> out1.txt")
    os.system("P343C <input.txt > out2.txt")
    rt = os.system("diff out1.txt out2.txt")
    return rt == 0

def test_suite():
    for size in range(5, 100):
        print "size = "  + str(size)
        for t in range(1, 100):
            ok = one_test(size)
            if not ok:
                print("diff!")
                exit(0)

test_suite()

#generate_input(5)
