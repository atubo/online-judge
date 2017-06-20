// https://www.luogu.org/problem/show?pid=2170
// 选学霸

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

int N, M, K;

int main() {
    scanf("%d%d%d", &N, &M, &K);
    UnionFind uf(N);
    for (int i = 0; i < K; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        if (uf.find(u) != uf.find(v)) uf.join(u, v);
    }
    map<int, int> cnt;
    for (int i = 0; i < N; i++) {
        cnt[uf.find(i)]++;
    }

    vector<int> A;
    for (const auto& p: cnt) {
        A.push_back(p.second);
    }
    sort(A.begin(), A.end());

    vector<bool> dp(N+1, false);
    dp[0] = true;
    int tot = 0;
    for (int x: A) {
        for (int i = tot; i >= 0; i--) {
            dp[i+x] = dp[i+x] || dp[i];
        }
        tot += x;
    }

    int ret = 0;
    for (int d = 0; d <= min(M, N-M); d++) {
        if (dp[M-d]) {
            ret = M-d;
            break;
        } else if (dp[M+d]) {
            ret = M+d;
            break;
        }
    }

    printf("%d\n", ret);

    return 0;
}
