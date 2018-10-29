// https://www.luogu.org/problemnew/show/P2504
// [HAOI2006]聪明的猴子

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
        size[k] = 1;
    }

    int link(int u, int v) {
        if (u == v) return u;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
            return u;
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            return v;
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);

        reset();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

const int MAXN = 1010;

struct Edge {
    int ds, u, v;
    bool operator < (const Edge &other) const {
        return ds < other.ds;
    }
} edges[MAXN*MAXN/2];

int M, N;
int D[510];
int X[MAXN], Y[MAXN];

int main() {
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &D[i]);
        D[i] *= D[i];
    }
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &X[i], &Y[i]);
    }
    int curr = 0;
    for (int u = 0; u < N; u++) {
        for (int v = u+1; v < N; v++) {
            int dx = X[u] - X[v];
            int dy = Y[u] - Y[v];
            int ds = dx*dx + dy*dy;
            edges[curr++] = {ds, u, v};
        }
    }
    sort(edges, edges+curr);

    UnionFind uf(N);
    int maxds = 0;
    for (int i = 0; i < curr; i++) {
        auto e = edges[i];
        if (uf.find(e.u) != uf.find(e.v)) {
            uf.join(e.u, e.v);
            maxds = max(maxds, e.ds);
        }
    }

    int ans = 0;
    for (int i = 0; i < M; i++) {
        if (D[i] >= maxds) ans++;
    }
    printf("%d\n", ans);
    return 0;
}
