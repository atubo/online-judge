import random
from random import randint

def rand_tree_edges(size):
    """return tree edges, 0 indexed"""
    ret = []
    for u in range(1, size):
        v = randint(0, u-1)
        ret.append((u, v))
    return ret

def rand_dag(n, m):
    """
    nodes are 0 indexed, returns edges
    note the graph is not necessarily connected
    """
    nodes = [i for i in range(n)]
    random.shuffle(nodes)
    s = set()
    for _ in range(m):
        u = randint(0, n-1)
        v = randint(0, n-1)
        if u > v:
            u, v = v, u
        while u == v or (u, v) in s:
            u = randint(0, n-1)
            v = randint(0, n-1)
            if u > v:
                u, v = v, u
        s.add((u, v))
    ret = set()
    for (u, v) in s:
        ret.add((nodes[u], nodes[v]))
    return ret
