// https://www.luogu.org/problem/show?pid=3623
// [APIO2008]免费道路

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
        ncomp--;
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
        ncomp = N;
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
    int ncomp;
};

using PII = pair<int, int>;

int N, M, K;

int main() {
    scanf("%d%d%d", &N, &M, &K);
    vector<PII> pebble;
    vector<PII> cement;

    for (int i = 0; i < M; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        u--; v--;
        if (c == 0) pebble.push_back(make_pair(u, v));
        else cement.push_back(make_pair(u, v));
    }

    UnionFind uf(N);
    for (const PII &p: cement) {
        int u, v;
        tie(u, v) = p;
        if (uf.find(u) != uf.find(v)) {
            uf.join(u, v);
        }
    }

    int remain = K;
    set<int> picked;
    for (int i = 0; i < (int)pebble.size(); i++) {
        if (remain == 0 || uf.ncomp == 1) break;
        int u, v;
        tie(u, v) = pebble[i];
        if (uf.find(u) != uf.find(v)) {
            uf.join(u, v);
            picked.insert(i);
            remain--;
        }
    }

    if (uf.ncomp > 1) {
        printf("no solution\n");
        return 0;
    }

    uf.reset();

    vector<PII> ret;
    for (int x: picked) {
        ret.push_back(pebble[x]);
        int u = pebble[x].first;
        int v = pebble[x].second;
        assert(uf.find(u) != uf.find(v));
        uf.join(u, v);
    }

    for (int i = 0; i < (int)pebble.size(); i++) {
        if (remain == 0) break;
        if (picked.count(i) > 0) continue;
        int u = pebble[i].first;
        int v = pebble[i].second;
        if (uf.find(u) != uf.find(v)) {
            uf.join(u, v);
            ret.push_back(pebble[i]);
            remain--;
        }
    }

    if (remain > 0) {
        printf("no solution\n");
        return 0;
    }

    for (const PII &p: cement) {
        if (uf.ncomp == 1) break;
        int u, v;
        tie(u, v) = p;
        if (uf.find(u) != uf.find(v)) {
            uf.join(u, v);
            ret.push_back(p);
        }
    };

    for (int i = 0; i < (int)ret.size(); i++) {
        int u = ret[i].first;
        int v = ret[i].second;
        int c = (i >= K);
        printf("%d %d %d\n", u+1, v+1, c);
    }

    return 0;
}
