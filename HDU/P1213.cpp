// http://acm.hdu.edu.cn/showproblem.php?pid=1213
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
        if (parent[k] != k) {
            parent[k] = find(parent[k]);
        }
        return parent[k];
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

int solve() {
    int N, M;
    scanf("%d %d", &N, &M);
    UnionFind uf(N);
    int a, b;
    int ans = N;
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        if (uf.find(a) != uf.find(b)) {
            ans--;
            uf.join(a, b);
        }
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        printf("%d\n", solve());
    }
    return 0;
}

