// https://www.luogu.org/problem/show?pid=1197
// [JSOI2008]星球大战

#include <cassert>
#include <cstdio>
#include <map>
#include <utility>
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

typedef pair<int, int> PII;

vector<PII> edges(200000);
vector<int> stars(400000, -1);

class Solution {
private:
    int N, M;
    int K;

public:
    Solution() {
        scanf("%d %d", &N, &M);
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &edges[i].first, &edges[i].second);
        }

        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            int s;
            scanf("%d", &s);
            stars[s] = i;
        }
    }

    void solve() {
        vector<vector<int> > destroyedEdges(K+1);
        for (int i = 0; i < M; i++) {
            int u = edges[i].first;
            int v = edges[i].second;
            int k1 = (stars[u] >= 0 ? stars[u] : K);
            int k2 = (stars[v] >= 0 ? stars[v] : K);
            int k = min(k1, k2);
            destroyedEdges[k].push_back(i);
        }

        UnionFind uf(N);
        int count = N;
        vector<int> ans(K+1);
        for (int k = K; k >= 0; k--) {
            for (int i = 0; i < (int)destroyedEdges[k].size(); i++) {
                PII e = edges[destroyedEdges[k][i]];
                int u = e.first;
                int v = e.second;
                if (uf.find(u) != uf.find(v)) {
                    count--;
                    uf.join(u, v);
                }
            }
            ans[k] = count;
        }

        for (int k = 0; k <= K; k++) {
            printf("%d\n", ans[k]-k);
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
