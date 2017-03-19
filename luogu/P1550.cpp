// https://www.luogu.org/problem/show?pid=1550
// [USACO08OCT]打井Watering Hole

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

    void link(int u, int v) {
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);

        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

using TI = tuple<int, int, int>;
const int MAXN = 310;
int N;
int W[MAXN];

int main() {
    scanf("%d", &N);
    int ret = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d",&W[i]);
        ret += W[i];
    }

    vector<TI> edges;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int p;
            scanf("%d", &p);
            if (i >= j) continue;
            edges.push_back(make_tuple(p, i, j));
        }
    }

    sort(edges.begin(), edges.end());

    UnionFind uf(N);
    for (const TI& e: edges) {
        int w, u, v;
        tie(w, u, v) = e;
        int up = uf.find(u);
        int vp = uf.find(v);
        if (up == vp || w >= max(W[up], W[vp])) continue;
        uf.join(u, v);
        int maxw = max(W[up], W[vp]);
        int minw = min(W[up], W[vp]);
        W[uf.find(u)] = minw;
        ret -= (maxw - w);
    }

    printf("%d\n", ret);
    return 0;
}
