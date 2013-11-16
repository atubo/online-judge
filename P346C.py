#!/usr/bin/python

# A segment tree easy to query and update min
class SegmentTreeBU:
    def __init__(self, n, NodeClass):
        self.NodeClass = NodeClass
        self.leaves = [None for i in range(n)]
        self.root = self.build(0, n-1, None)
    def build(self, i, j, parent):
        node = self.NodeClass(i, j, parent)
        if i == j:
            self.leaves[i] = node
        else:
            middle = i + (j-i)/2
            node.left  = self.build(i, middle, node)
            node.right = self.build(middle+1, j, node)
        return node
    def propagateUp(self, node):
        node.update()
        if node.changed and node.parent != None:
            self.propagateUp(node.parent)
    def updateLeaf(self, i, data):
        node = self.leaves[i]
        node.updateData(data)
        if node.changed and node.parent != None:
            self.propagateUp(node.parent)

    def findMin(self):
        return self.root.getVal()

class Node:
    def __init__(self, i, j, parent):
        self.i = i
        self.j = j
        self.parent = parent
        self.left   = None
        self.right  = None
        self.value  = None
    def update(self):
        assert self.left and self.right
        oldValue = self.value
        self.value = min(self.left.value, self.right.value)
        self.changed = (self.value != oldValue)
    def updateData(self, data):
        assert not self.left and not self.right
        oldValue = self.value
        self.value = data
        self.changed = (self.value != oldValue)
    def getVal(self):
        return self.value

def solve():
    n = int(raw_input())
    xList = map(lambda x: int(x), raw_input().split())
    xList = list(set(xList))
    n = len(xList)
    (a, b) = map(lambda x: int(x), raw_input().split())
    ladder = dict()
    for i in range(n):
        x = xList[i]
        for k in range(b//x, a//x+1):
            if x*k not in ladder:
                ladder[x*k] = set()
            ladder[x*k].add(i)

    MAXVAL = 10000000
    tree = SegmentTreeBU(n, Node)
    for i in range(n):
        tree.updateLeaf(i, MAXVAL)

    dist = 0
    if b in ladder:
        for x in ladder[b]:
            tree.updateLeaf(x, 0)
    for i in xrange(b+1, a+1):
        if i in ladder:
            for x in ladder[i]:
                tree.updateLeaf(x, MAXVAL)
        dist = min(dist, tree.findMin()) + 1
        if i in ladder:
            for x in ladder[i]:
                tree.updateLeaf(x, dist)

    print dist

solve()
