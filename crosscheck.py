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

def rand_permutation(size):
    ret = [i for i in range(1, size+1)]
    random.shuffle(ret)
    return ret

def rand_tree(size):
    """return adj array, index from 0 to size-1"""
    adj = [[] for i in range(size)]
    for u in range(1, size):
        v = randint(0, u-1)
        adj[u].append(v)
        adj[v].append(u)
    return adj

def print_tree_edges(f, adj):
    # Note here index is from 1
    N = len(adj)
    for u in range(N):
        for v in adj[u]:
            if u < v:
                f.write("%d %d\n" % (u+1, v+1))


def print_array(f, a):
    for x in a:
        f.write("%d " % x)
    f.write("\n")

def generate_input(size):
    os.system("rm input.txt")
    with open("input.txt", "w") as f:
        n = size
        m = size
        f.write("%d %d\n" % (n, m))
        print_array(f, rand_array(n, 1, 1000))
        print_tree_edges(f, rand_tree(n))
        for i in range(m):
            t = randint(1, 2)
            x = randint(1, n)
            if t == 1:
                val = randint(1, 1000)
                f.write("%d %d %d\n" % (t, x, val))
            else:
                f.write("%d %d\n" % (t, x))


def one_test(size):
    generate_input(size)
    os.system("bench <input.txt> out1.txt")
    os.system("P383C <input.txt > out2.txt")
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
