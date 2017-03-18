// https://www.luogu.org/problem/show?pid=1195
// 口袋的天空

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

using TI = tuple<int, int, int>;

int main() {
   int N, M, K;
   scanf("%d %d %d", &N, &M, &K);

   vector<TI> edges(M);
   for (int i = 0; i < M; i++) {
       int u, v, w;
       scanf("%d %d %d", &u, &v, &w);
       u--; v--;
       edges[i] = make_tuple(w, u, v);
   }
   sort(edges.begin(), edges.end());

   UnionFind uf(N);
   int nc = N;
   int ret = 0;

   for (int i = 0; i < M && nc > K; i++) {
       int u, v, w;
       tie(w, u, v) = edges[i];
       if (uf.find(u) == uf.find(v)) continue;
       uf.join(u, v);
       nc--;
       ret += w;
   }

   if (nc == K) {
       printf("%d\n", ret);
   } else {
       printf("No Answer\n");
   }
   return 0;
}
