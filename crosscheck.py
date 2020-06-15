#!/usr/bin/python
import string
import random
from random import randint
import time
import os

def rand_str(size, chars=string.ascii_lowercase):
    return ''.join(random.choice(chars) for _ in range(size))

def rand_array(size, lo=-10000, hi=10000):
    ret = []
    for i in range(size):
        ret.append(random.randint(lo, hi))
    return ret

def rand_matrix(row, col, lo=-10000, hi=10000):
    ret = []
    for i in range(row):
        ret.append(rand_array(col, lo, hi))
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

def rand_binary_tree(size):
    """each node has either 0 or 2 children"""
    adj = [[] for i in range(size)]
    sz = 1
    leaves = set()
    leaves.add(0)
    while sz < size:
        u = random.sample(leaves, 1)[0]
        leaves.remove(u)
        adj[u].append(sz)
        adj[sz].append(u)
        adj[u].append(sz+1)
        adj[sz+1].append(u)
        leaves.add(sz)
        leaves.add(sz+1)
        sz += 2
    return adj

def rand_bigint(size):
    ret = chr(ord('0') + randint(1, 9))
    for i in range(size-1):
        ret += chr(ord('0') + randint(0, 9))
    return ret

def print_graph_edges(f, adj):
    # Note here index is from 1
    N = len(adj)
    for u in range(N):
        for v in adj[u]:
            if u < v:
                f.write("%d %d\n" % (u+1, v+1))

def print_tree_dfs(f, adj, root):
    # 1-indexed, print all father-son edges

    def dfs(f, adj, u, fa):
        for v in adj[u]:
            if v != fa:
                f.write("%d %d\n" % (u+1, v+1))
                dfs(f, adj, v, u)

    dfs(f, adj, 0, -1)

def rand_directed_graph(n, m):
    # node 0 can reach all other nodes
    # return list of edges
    adj = rand_tree(n)
    ret = []
    def dfs(adj, u, fa, edges):
        for v in adj[u]:
            if v != fa:
                edges.append((u, v))
                dfs(adj, v, u, edges)
    dfs(adj, 0, -1, ret)
    for _ in range(m-n+1):
        u = randint(0, n-1)
        v = randint(0, n-1)
        ret.append((u, v))
    return ret

def print_weighted_graph_edges(f, adj, lo, hi):
    """Given adj, this function adds random weight and print the graph"""
    # Note here index is from 1
    N = len(adj)
    for u in range(N):
        for v in adj[u]:
            if u < v:
                w = randint(lo, hi)
                if randint(1, 2) == 1:
                    f.write("%d %d %d\n" % (v+1, u+1, w))
                else:
                    f.write("%d %d %d\n" % (u+1, v+1, w))


def print_array(f, a):
    for x in a:
        f.write("%d " % x)
    f.write("\n")

def print_matrix(f, m):
    for a in m:
        print_array(f, a)

def rand_range(low, hi):
    x = randint(low, hi)
    y = randint(low, hi)
    if x > y:
        x, y = y, x
    return x, y

def swap(s, i, j):
    lst = list(s)
    lst[i], lst[j] = lst[j], lst[i]
    return ''.join(lst)

def build_directed_tree(lo, hi):
    """ build a directed tree that ensures hi is reachable from lo"""
    ret = set()
    for lo in range(1, hi):
        u = randint(lo+1, hi)
        ret.add((lo, u))
    return ret

def build_graph(n, m):
    """ build a directed graph that ensures hi is reachable from lo"""
    ret = build_directed_tree(1, n)
    for i in range(m-n+1):
        u = randint(1, n)
        v = randint(1, n)
        while v == u or (u, v) in ret:
            u = randint(1, n)
            v = randint(1, n)
        ret.add((u, v))
    return ret

def build_undirected_simple_graph(n, m):
    """ build a connected undirected simple graph """
    ret = rand_tree(n)
    for i in range(m-n+1):
        u = randint(0, n-1)
        v = randint(0, n-1)
        while u == v or ret[u].count(v) > 0:
            u = randint(0, n-1)
            v = randint(0, n-1)
        ret[u].append(v)
        ret[v].append(u)
    return ret

def build_undirected_graph(n, m):
    """ build a connected undirected graph """
    adj = rand_tree(n)
    edges = []
    for i in range(n):
        for j in adj[i]:
            if i < j:
                edges.append((i, j))
    for i in range(m-n+1):
        u = randint(0, n-1)
        v = randint(0, n-1)
        edges.append((u, v))
    return edges

def print_weighted_undirected_graph(f, edges, lo, hi):
    for e in edges:
        w = randint(lo, hi)
        f.write("%d %d %d\n" % (e[0]+1, e[1]+1, w))

def generate_father_array(adj):
    def dfs(adj, u, fa, ret):
        ret[u] = fa
        for v in adj[u]:
            if v != fa:
                dfs(adj, v, u, ret)
    ret = [0 for i in range(len(adj))]
    dfs(adj, 0, -1, ret)
    return ret

def generate_input(size):
    os.system("rm -f input.txt")
    with open("input.txt", "w") as f:
        n = size

def compare_double():
    with open('out1.txt') as f1:
        with open('out2.txt') as f2:
            x1 = float(f1.readline())
            x2 = float(f2.readline())
            if abs(x1 - x2) > 0.01:
                return 1
    return 0


def one_test(size):
    generate_input(size)
    exit(0)
    ret = os.system("bench <input.txt> out1.txt")
    if ret != 0:
        print "Bench error"
        exit(1)
    ret = os.system("P2146 <input.txt > out2.txt")
    if ret != 0:
        print "Test error"
        exit(1)
    ret = os.system("diff out1.txt out2.txt")
    return ret == 0

def test_suite():
    for size in range(5, 100):
        print "size = "  + str(size)
        for t in range(100):
            ok = one_test(size)
            if not ok:
                print("diff!")
                exit(0)

test_suite()

#generate_input(250000)
