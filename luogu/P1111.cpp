// https://www.luogu.org/problem/show?pid=1111
// 修复公路
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
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

typedef pair<int, pair<int, int> > TIII; // weight -> (u, v)

class Kruskal {
public:
    static int mst(vector<TIII>& edges, int N) {
        typedef vector<TIII>::const_iterator Iter;
        UnionFind uf(N);
        sort(edges.begin(), edges.end());
        int ans = 0;
        for (Iter it = edges.begin(); it != edges.end(); it++) {
            int w = it->first;
            int u = it->second.first;
            int v = it->second.second;
            if (uf.find(u) == uf.find(v)) continue;
            ans = w;
            uf.join(u, v);
        }
        return ans;
    }
};

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    UnionFind uf(N);
    vector<TIII> edges;
    int ncomp = N;
    int x, y, t;
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &x, &y, &t);
        x--; y--;
        if (uf.find(x) != uf.find(y)) {
            ncomp--;
            uf.join(x, y);
        }
        edges.push_back(make_pair(t, make_pair(x, y)));
    }
    if (ncomp > 1) {
        cout << "-1" << endl;
    } else {
        cout << Kruskal::mst(edges, N) << endl;
    }

    return 0;
}
