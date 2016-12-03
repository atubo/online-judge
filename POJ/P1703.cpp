// http://poj.org/problem?id=1703
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

void solve() {
    int N, M;
    scanf("%d %d", &N, &M);
    char str[10];
    int a, b;
    UnionFind uf(2*N);
    while (M--) {
        scanf("%s %d %d", str, &a, &b);
        a--; b--;
        if (str[0] == 'D') {
            if (uf.find(2*a) != uf.find(2*b+1)) {
                assert(uf.find(2*a) != uf.find(2*b));
                uf.join(2*a, 2*b+1);
                uf.join(2*a+1, 2*b);
            }
        } else {
            if (uf.find(2*a) == uf.find(2*b)) {
                printf("In the same gang.\n");
            } else if (uf.find(2*a) == uf.find(2*b+1)) {
                printf("In different gangs.\n");
            } else {
                printf("Not sure yet.\n");
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
