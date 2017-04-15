// https://daniu.luogu.org/problem/show?pid=2881
// [USACO07MAR]排名的牛Ranking the Cows

#include <bits/stdc++.h>
using namespace std;


// Note: be sure it's DAG
class TopologicalSort {
public:
    int N, M;
    vector<vector<int> > adj;
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
    TopologicalSort() {
        scanf("%d%d", &N, &M);
        adj.resize(N);
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--; v--;
            adj[u].push_back(v);
        }
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

class Mask {
    // 1000-bit
    static const int SZ = 32;
private:
    unsigned int bits[SZ];
public:
    Mask() {
        memset(bits, 0, sizeof(bits));
    }

    void set(int i) {
        bits[i/32] |= (1 << (i%32));
    }

    void unset(int i) {
        bits[i/32] &= ~(1 << (i%32));
    }

    int get(int i) const {
        // return 0 or 1
        return (bits[i/32] >> (i%32)) & 1;
    }

    Mask& operator |= (const Mask &other) {
        for (int i = 0; i < SZ; i++) {
            bits[i] |= other.bits[i];
        }
        return *this;
    }

    int popcount() {
        int ret = 0;
        for (int i = 0; i < SZ; i++) {
            ret += __builtin_popcount(bits[i]);
        }
        return ret;
    }
};


int main() {
    TopologicalSort ts;
    const int N = ts.N;
    ts.sort();

    vector<Mask> masks(N);
    for (int i = 0; i < N; i++) {
        masks[i].set(i);
    }
    int ret = 0;
    for (int i = N-1; i >= 0; i--) {
        int u = ts.topo[i];
        for (int v: ts.adj[u]) {
            masks[u] |= masks[v];
        }
        ret += (N-i) - masks[u].popcount();
    }
    printf("%d\n", ret);

    return 0;
}
