// https://www.luogu.org/problem/show?pid=2024
// 食物链
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

int PRED(int x) {return 3*x;}
int SELF(int x) {return 3*x+1;}
int PREY(int x) {return 3*x+2;}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    UnionFind uf(3*N);
    int ans = 0;
    int t, x, y;
    while (K--) {
        scanf("%d %d %d", &t, &x, &y);
        x--; y--;
        if (x >= N || y >= N) {
            ans++;
            continue;
        }
        if (t == 1) {
            if (uf.find(SELF(x)) == uf.find(PREY(y)) ||
                uf.find(SELF(x)) == uf.find(PRED(y))) {
                ans++;
                continue;
            } else if (uf.find(SELF(x)) != uf.find(SELF(y))) {
                uf.join(PRED(x), PRED(y));
                uf.join(SELF(x), SELF(y));
                uf.join(PREY(x), PREY(y));
            }
        } else {
            if (uf.find(SELF(x)) == uf.find(SELF(y)) ||
                uf.find(SELF(x)) == uf.find(PREY(y))) {
                ans++;
                continue;
            } else if (uf.find(SELF(x)) != uf.find(PRED(y))) {
                uf.join(SELF(x), PRED(y));
                uf.join(PREY(x), SELF(y));
                uf.join(PRED(x), PREY(y));
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
