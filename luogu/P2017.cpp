// https://www.luogu.org/problem/show?pid=2017
// [USACO09DEC]晕牛Dizzy Cows

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
    };

    vector<int> head;
    vector<Edge> E;
    int eidx;
    int N;

    Graph(int N_, int M):N(N_) {
        head.resize(N);
        E.resize(M);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

// Note: be sure it's DAG
class TopologicalSort {
public:
    vector<int> topo;  // topologically sorted result

private:
    void topologicalSortUtil(const Graph &g, int v, bool visited[],
                             stack<int> &order) {
        visited[v] = true;

        for (int i = g.head[v]; i != -1; i = g.E[i].next) {
            int m = g.E[i].to;
            if (!visited[m]) {
                topologicalSortUtil(g, m, visited, order);
            }
        }

        order.push(v);
    }

public:
    TopologicalSort() {}

    void sort(const Graph &g) {
        const int N = g.N;
        topo.resize(N);

        stack<int> order;
        bool visited[N];
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                topologicalSortUtil(g, i, visited, order);
            }
        }

        int i = 0;
        while (!order.empty()) {
            topo[i++] = order.top();
            order.pop();
        }
    }
};

using PII = pair<int, int>;

int main() {
    int N, P1, P2;
    scanf("%d%d%d", &N, &P1, &P2);
    Graph g(N, P1);
    int a, b;
    for (int i = 0; i < P1; i++) {
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b);
    }

    vector<PII> undirected;
    for (int i = 0; i < P2; i++) {
        scanf("%d%d", &a, &b);
        a--; b--;
        undirected.push_back(make_pair(a, b));
    }

    TopologicalSort topo;
    topo.sort(g);

    for (const auto& e: undirected) {
        tie(a, b) = e;
        if (topo.topo[a] > topo.topo[b]) swap(a, b);
        printf("%d %d\n", a+1, b+1);
    }
    return 0;
}
