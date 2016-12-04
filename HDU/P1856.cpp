// http://acm.hdu.edu.cn/showproblem.php?pid=1856
#include <bits/stdc++.h>
using namespace std;

int maxsize = 1;

class UnionFind {
private:
    const int N;
    vector<int> rank;
    vector<int> parent;

    void makeSet(int k) {
        assert(0 <= k && k < N);

        parent[k] = k;
        rank[k] = 1;
    }

    void link(int u, int v) {
        if (rank[u] > rank[v]) {
            parent[v] = u;
            rank[u] += rank[v];
            maxsize = max(maxsize, rank[u]);
        } else {
            parent[u] = v;
            rank[v] += rank[u];
            maxsize = max(maxsize, rank[v]);
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);

        //init();
    }

    void init() {
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
};

int main() {
    const int NUM_BOYS = 10000000;
    UnionFind uf(NUM_BOYS);
    int n;
    while (cin >> n) {
        uf.init();
        maxsize = 1;
        int a, b;
        while (n--) {
            scanf("%d %d", &a, &b);
            a--; b--;
            if (uf.find(a) != uf.find(b)) uf.join(a, b);
        }
        cout << maxsize << endl;
    }
}
