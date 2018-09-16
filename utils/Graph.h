#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

struct DirectedGraphNode {
    int label;
    std::vector<DirectedGraphNode*> neighbors;
    DirectedGraphNode(int x): label(x) {};
};

typedef std::vector<DirectedGraphNode*> Graph;

Graph readGraph() {
    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < n; i++) {
        g[i] = new DirectedGraphNode(i);
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        g[u]->neighbors.push_back(g[v]);
    }
    return g;
}

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode*> neighbors;
    UndirectedGraphNode(int x): label(x) {}
};


#endif
