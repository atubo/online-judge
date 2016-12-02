// https://www.luogu.org/problem/show?pid=1196
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
        parent[u] = v;
        rank[u] = size[v];
        size[v] += size[u];
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
        rank[k] += rank[parent[k]];
        return parent[k] = root;
    }

    void join(int u, int v) {
        link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }

    int getRank(int u) {
        return rank[u];
    }
};

int main() {
    int T;
    scanf("%d", &T);
    UnionFind uf(30000);
    char c;
    int a, b;
    char str[10];
    while (T--) {
        scanf("%s", str);
        c = str[0];
        scanf("%d %d", &a, &b);
        a--; b--;
        if (c == 'M') {
            if (uf.find(a) != uf.find(b)) {
                uf.join(a, b);
            }
        } else {
            if (uf.find(a) != uf.find(b)) {
                printf("-1\n");
            } else {
                int d = (a == b ? 0 : abs(uf.getRank(a) - uf.getRank(b))-1);
                printf("%d\n", d);
            }
        }
    }
    return 0;
}
