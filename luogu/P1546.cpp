// https://www.luogu.org/problem/show?pid=1546
// 最短网络 Agri-Net

#include <algorithm>
#include <cassert>
#include <cstdio>
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

typedef pair<int, pair<int, int> > Edge; // (weight, (u, v))

class Solution {
private:
    int N;
    vector<Edge> edges;

public:
    Solution() {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int w;
                scanf("%d", &w);
                edges.push_back(make_pair(w, make_pair(i, j)));
            }
        }
    }

    void solve() {
        printf("%d\n", kruskal());
    }

    int kruskal() {
        int ans = 0;
        UnionFind uf(N);
        sort(edges.begin(), edges.end());
        for (int i = 0; i < (int)edges.size(); i++) {
            Edge edge = edges[i];
            int w, u, v;
            w = edge.first;
            u = edge.second.first;
            v = edge.second.second;
            if (uf.find(u) == uf.find(v)) continue;
            ans += w;
            uf.join(u, v);
        }

        return ans;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
