// https://www.luogu.org/problem/show?pid=3420
// [POI2005]SKA-Piggy Banks

#include <bits/stdc++.h>
using namespace std;

using Adj = vector<vector<int> >;

// Note: be sure it's DAG
class TopologicalSort {
public:
    int N;
    const vector<vector<int> >& adj;
    vector<int> topo;  // topologically sorted result

private:
    void topologicalSortUtil(int v, bool visited[],
                             stack<int> &order) {
        visited[v] = true;

        for (int i = 0; i < (int)adj[v].size(); i++) {
            int m = adj[v][i];
            if (!visited[m]) {
                topologicalSortUtil(m, visited, order);
            }
        }

        order.push(v);
    }

public:
    TopologicalSort(int N_, const vector<vector<int> >& adj_): N(N_), adj(adj_) {
        // initialize N and adj
    }

    void sort() {
        topo.resize(N);

        stack<int> order;
        bool visited[N];
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, order);
            }
        }

        int i = 0;
        while (!order.empty()) {
            topo[i++] = order.top();
            order.pop();
        }
    }
};

void dfs(const vector<vector<int> >& g, int u, vector<bool>& visited) {
    visited[u] = true;
    for (int v: g[u]) {
        if (!visited[v]) dfs(g, v, visited);
    }
}

int calcComponent(const vector<vector<int> >& g, int n, const vector<int>& topo) {
    vector<bool> visited(n, false);
    int nc = 0;
    for (int u: topo) {
        if (!visited[u]) {
            dfs(g, u, visited);
            nc++;
        }
    }
    return nc;
}



int main() {
    int N;
    scanf("%d", &N);
    Adj adj(N);
    for (int i = 0; i < N; i++) {
        int u;
        scanf("%d", &u);
        adj[u-1].push_back(i);
    }

    TopologicalSort topo(N, adj);
    topo.sort();

    printf("%d\n", calcComponent(adj, N, topo.topo));
    return 0;
}
