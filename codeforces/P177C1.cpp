// http://codeforces.com/problemset/problem/177/C1
#include <bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 0;
    }

    void link(int u, int v) {
        if (rank[u] > rank[v]) {
            parent[v] = u;
        } else {
            parent[u] = v;
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);

        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        if (parent[k] != k) {
            parent[k] = find(parent[k]);
        }
        return parent[k];
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }
};


class Solution {
    using PII = pair<int, int>;
private:
    int N, K, M;
    vector<PII> like;
    vector<PII> dislike;
public:
    Solution() {
        cin >> N;
        cin >> K;
        like.resize(K);
        for (int i = 0; i < K; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            like[i] = make_pair(u-1, v-1);
        }
        cin >> M;
        dislike.resize(M);
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            dislike[i] = make_pair(u-1, v-1);
        }
    }

    void solve() {
        UnionFind uf(N);
        for (const PII& p: like) {
            uf.join(p.first, p.second);
        }

        vector<bool> ok(N, true);
        for (const PII& p: dislike) {
            int u = uf.find(p.first), v = uf.find(p.second);
            if (u == v) {
                ok[u] = false;
            }
        }

        vector<int> count(N, 0);
        for (int i = 0; i < N; i++) {
            int u = uf.find(i);
            if (ok[u]) count[u]++;
        }
        int ret = *max_element(count.begin(), count.end());
        cout << ret << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
