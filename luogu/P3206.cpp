// https://www.luogu.org/problemnew/show/P3206
// [HNOI2010]城市建设

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    int id;
    bool operator < (const Edge &other) const {
        if (w < other.w) return true;
        if (w > other.w) return false;
        return id < other.id;
    }
};

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

    void reset(int n, const Edge *e) {
        for (int i = 0; i < n; i++) {
            parent[e[i].u] = e[i].u;
            parent[e[i].v] = e[i].v;
            size[e[i].u] = size[e[i].v] = 1;
        }
    }

};

const int MAXM = 50010, MAXL = 16;
const int inf = ~0u >> 1;

int W[MAXM], mp[MAXM];
Edge edge[MAXL][MAXM], d[MAXM], t[MAXM];
int64_t ans[MAXM];

struct Query {
    int e, w;
} que[MAXM];

int64_t contract(UnionFind &uf, int &n) {
    int tmp = 0;
    sort(d, d+n);
    for (int i = 0; i < n; i++) {
        if (uf.find(d[i].u) != uf.find(d[i].v)) {
            uf.join(d[i].u, d[i].v);
            t[tmp++] = d[i];
        }
    }

    uf.reset(tmp, t);

    int64_t v = 0;
    for (int i = 0; i < tmp; i++) {
        if (t[i].w != -inf && uf.find(t[i].u) != uf.find(t[i].v)) {
            uf.join(t[i].u, t[i].v);
            v += t[i].w;
        }
    }

    tmp = 0;
    for (int i = 0; i < n; i++) {
        if (uf.find(d[i].u) != uf.find(d[i].v)) {
            t[tmp] = d[i];
            t[tmp].u = uf.find(d[i].u);
            t[tmp].v = uf.find(d[i].v);
            mp[d[i].id] = tmp++;
        }
    }

    uf.reset(n, d);
    n = tmp;
    for (int i = 0; i < tmp; i++) {
        d[i] = t[i];
    }
    return v;
}


void reduce(UnionFind &uf, int &n) {
    int tmp = 0;
    sort(d, d+n);
    for (int i = 0; i != n; i++) {
        if (uf.find(d[i].u) != uf.find(d[i].v)) {
            uf.join(d[i].u, d[i].v);
            t[tmp] = d[i];
            mp[d[i].id] = tmp++;
        } else if (d[i].w == inf) {
            t[tmp] = d[i];
            mp[d[i].id] = tmp++;
        }
    }
    uf.reset(n, d);
    n = tmp;
    for (int i = 0; i < tmp; i++) {
        d[i] = t[i];
    }
}

void divide(UnionFind &uf, int depth, int n, int l, int r, int64_t v) {
    if (l == r) {
        W[que[l].e] = que[l].w;
    }
    for (int i = 0; i < n; i++) {
        edge[depth][i].w = W[edge[depth][i].id];
        d[i] = edge[depth][i];
        mp[d[i].id] = i;
    }

    if (l == r) {
        ans[l] = v;
        sort(d, d+n);
        for (int i = 0; i < n; i++) {
            if (uf.find(d[i].u) != uf.find(d[i].v)) {
                uf.join(d[i].u, d[i].v);
                ans[l] += d[i].w;
            }
        }
        uf.reset(n, d);
        return;
    }

    for (int i = l; i <= r; i++) {
        d[mp[que[i].e]].w = -inf;
    }
    v += contract(uf, n);

    for (int i = l; i <= r; i++) {
        d[mp[que[i].e]].w = inf;
    }
    reduce(uf, n);

    for (int i = 0; i < n; i++) {
        edge[depth+1][i] = d[i];
    }

    int mid = (l + r) / 2;
    divide(uf, depth+1, n, l, mid, v);
    divide(uf, depth+1, n, mid+1, r, v);
}

int N, M, Q;

int main() {
    scanf("%d%d%d", &N, &M, &Q);
    for (int i = 0; i < M; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        x--; y--;
        edge[0][i] = {x, y, z, i};
        W[i] = z;
    }
    for (int i = 0; i < Q; i++) {
        int k, w;
        scanf("%d%d", &k, &w);
        k--;
        que[i] = {k, w};
    }
    UnionFind uf(N);
    divide(uf, 0, M, 0, Q-1, 0);
    for (int i = 0; i < Q; i++) {
        printf("%ld\n", ans[i]);
    }
    return 0;
}
