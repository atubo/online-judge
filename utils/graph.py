import random
from random import randint

def rand_tree_edges(size):
    """return tree edges, 0 indexed"""
    ret = []
    for u in range(1, size):
        v = randint(0, u-1)
        ret.append((u, v))
    return ret

