// https://www.luogu.org/problem/show?pid=2212
// [USACO14MAR]浇地Watering the Fields

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

using TIII = tuple<int, int, int>;  // (weight, u, v)

int cost, ncomp;

class Kruskal {
public:
    static void mst(vector<TIII>& edges, int N) {
        ncomp = N;
        UnionFind uf(N);
        sort(edges.begin(), edges.end());
        for (const TIII& e: edges) {
            int w, u, v;
            tie(w, u, v) = e;
            if (uf.find(u) == uf.find(v)) continue;
            ncomp--;
            uf.join(u, v);
            cost += w;
        }
    }
};

const int MAXN = 2010;
int X[MAXN], Y[MAXN];
int N, C;

int dist(int i, int j) {
    int dx = X[i] - X[j];
    int dy = Y[i] - Y[j];
    return dx*dx + dy*dy;
}

int main() {
    scanf("%d%d", &N, &C);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &X[i], &Y[i]);
    }

    vector<TIII> edges;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            int d = dist(i, j);
            if (d >= C) {
                edges.push_back(make_tuple(d, i, j));
            }
        }
    }

    Kruskal::mst(edges, N);

    printf("%d\n", ncomp == 1 ? cost : -1);
    return 0;
}
