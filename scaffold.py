#!/usr/bin/python
import string
import random
import time
import os

def rand_str(size):
    chars = string.ascii_lowercase;
    return ''.join(random.choice(chars) for _ in range(size))

def rand_array(size):
    ret = []
    for i in range(size):
        ret.append(random.randint(0, 10000))
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
        f.write("%d\n" % n)
        print_array(f, rand_array(n))
        #m = random.randint(n, 2*n)
        m = 1000
        f.write("%d\n" % m)
        for i in range(m):
            t = random.randint(1, 2)
            l = random.randint(1, n)
            r = random.randint(l, n)
            f.write("%d %d %d" % (t, l, r))
            if t == 2:
                f.write(" %d" % random.randint(1, 100000))
            f.write("\n")


def one_test(size):
    generate_input(size)
    os.system("bench <input.txt> out1.txt")
    os.system("P242E <input.txt > out2.txt")
    rt = os.system("diff out1.txt out2.txt")
    return rt == 0

def test_suite():
    for size in range(100000, 1000001):
        print "size = "  + str(size)
        for t in range(1, 100):
            ok = one_test(size)
            if not ok:
                print("diff!")
                exit(0)

test_suite()

#generate_input(5)
