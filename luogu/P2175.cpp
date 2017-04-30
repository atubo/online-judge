// https://www.luogu.org/problem/show?pid=2175
// 小Z的游戏分队

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
        size[k] = (k % 2 == 0);
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

    void join(int u, int v) {
        link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

using Adj = vector<unordered_set<int>>;
using PII = pair<int, int>;
int N;

int main() {
    scanf("%d", &N);
    UnionFind uf(2*N);
    Adj adj(N);
    for (int i = 0; i < N; i++) {
        int j;
        while (scanf("%d", &j) && j) {
            j--;
            adj[i].insert(j);
        }
        for (j = 0; j < N; j++) {
            if (j != i && adj[i].count(j) == 0) {
                int u = 2 * i;
                int up = u + 1;
                int v = 2 * j;
                int vp = v + 1;
                if (uf.find(u) != uf.find(vp)) {
                    uf.join(u, vp);
                    uf.join(up, v);
                }
            }
        }
    }

    set<PII> leaders;
    for (int i = 0; i < N; i++) {
        int u = 2 * i;
        int up = u + 1;
        int ld1 = uf.find(u);
        int ld2 = uf.find(up);
        if (ld1 == ld2) {
            printf("No solution\n");
            return 0;
        } else {
            if (ld1 > ld2) swap(ld1, ld2);
            leaders.insert(make_pair(ld1, ld2));
        }
    }

    int ng = leaders.size();
    vector<PII> gsz(ng+1);
    int gszidx = 1;
    for (const PII &p: leaders) {
        gsz[gszidx++] = make_pair(uf.count(p.first), uf.count(p.second));
    }

    vector<bool> dp(N+1);
    dp[0] = true;
    for (int i = 1; i <= ng; i++) {
        for (int j = N; j >= 0; j--) {
            int sz1 = gsz[i].first;
            int sz2 = gsz[i].second;
            if (j - sz1 >= 0) dp[j] = dp[j-sz1];
            if (j - sz2 >= 0) dp[j] = dp[j] || dp[j-sz2];
        }
    }

    int ret = 0;
    for (int i = 1; i <= N/2; i++) {
        if (dp[i]) ret = i;
    }

    printf("%d %d\n", ret, N - ret);
    return 0;
}
