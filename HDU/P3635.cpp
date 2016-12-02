// http://acm.hdu.edu.cn/showproblem.php?pid=3635
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
        parent[u] = v;
        size[v] += size[u];
        rank[u] = 1;
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
        if (parent[k] != k) {
            int oldp = parent[k];
            parent[k] = find(parent[k]);
            rank[k] += rank[oldp];
        }
        return parent[k];
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }

    int mergeCount(int u) {
        find(u);
        return rank[u];
    }
};

void solve() {
    int N, q;
    scanf("%d %d", &N, &q);
    UnionFind uf(N);
    char t;
    int a, b;
    while (q--) {
        cin >> t;
        if (t == 'T') {
            scanf("%d %d", &a, &b);
            a--; b--;
            if (uf.find(a) != uf.find(b)) {
                uf.join(a, b);
            }
        } else {
            scanf("%d", &a);
            a--;
            int x = uf.find(a);
            int y = uf.count(a);
            int z = uf.mergeCount(a);
            printf("%d %d %d\n", x+1, y, z);
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++) {
        printf("Case %d:\n", i);
        solve();
    }
    return 0;
}
