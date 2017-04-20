// https://www.luogu.org/problem/show?pid=1955
// 程序自动分析

#include <bits/stdc++.h>
using namespace std;
using TI = tuple<int, int, int>;


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

int N;
const int MAXN = 200010;
TI C[MAXN];

int main() {
    int tests;
    scanf("%d", &tests);
    while (tests--) {
        scanf("%d", &N);
        vector<int> A(2*N);
        for (int i = 0; i < N; i++) {
            int x, y, e;
            scanf("%d%d%d", &x, &y, &e);
            C[i] = make_tuple(e, x, y);
            A[2*i] = x;
            A[2*i+1] = y;
        }
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        int m = A.size();
        UnionFind uf(m);
        sort(C, C+N, greater<TI>());
        int idx = 0;
        for (; idx < N; idx++) {
            int e, x, y;
            tie(e, x, y) = C[idx];
            if (e == 0) break;
            x = lower_bound(A.begin(), A.end(), x) - A.begin();
            y = lower_bound(A.begin(), A.end(), y) - A.begin();
            if (uf.find(x) != uf.find(y)) {
                uf.join(x, y);
            }
        }
        bool conflict = false;
        for (; idx < N; idx++) {
            int e, x, y;
            tie(e, x, y) = C[idx];
            assert(e == 0);
            x = lower_bound(A.begin(), A.end(), x) - A.begin();
            y = lower_bound(A.begin(), A.end(), y) - A.begin();
            if (uf.find(x) == uf.find(y)) {
                conflict = true;
                break;
            }
        }
        printf(conflict ? "NO\n" : "YES\n");
    }
    return 0;
}
