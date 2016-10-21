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
        m = 2 * n
        f.write("%d %d\n" % (n, m))
        print_array(f, rand_array(n))
        print_array(f, rand_array(n))
        for i in range(m):
            t = random.randint(1, 2)
            if t == 1:
                x = random.randint(1, n)
                y = random.randint(1, n)
                k = random.randint(1, min(n+1-x, n+1-y))
                f.write("1 %d %d %d" % (x, y, k))
            else:
                f.write("2 %d" % random.randint(1, n))
            f.write("\n")


def one_test(size):
    generate_input(size)
    os.system("bench <input.txt> out1.txt")
    os.system("P292E <input.txt > out2.txt")
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
