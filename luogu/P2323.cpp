// https://www.luogu.org/problemnew/show/P2323
// [HNOI2006]公路修建问题

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

    int link(int u, int v) {
        if (u == v) return u;
        if (rank[u] > rank[v]) {
            parent[v] = u;
            size[u] += size[v];
            return u;
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            return v;
        }
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
    }

    int find(int k) {
        if (parent[k] == k) return k;
        int root = find(parent[k]);
        return parent[k] = root;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};

const int MAXN = 10010;
const int MAXM = 20010;

int N, M, K;

struct Highway {
    int a, b, c1, c2;
} H[MAXM];

struct Edge {
    int t, u, v, id;
    bool operator < (const Edge &other) const {
        if (t < other.t) return true;
        if (t > other.t) return false;
        return id < other.id;
    }
} E[MAXM];

struct Selection {
    int t, p;
    bool operator < (const Selection &other) const {
        return t < other.t;
    }
} S[MAXN];

bool feasible(UnionFind &uf, int mid) {
    uf.reset();

    int idx = 0;
    for (int i = 0; i < M; i++) {
        if (H[i].c1 <= mid) {
            E[idx++] = {1, H[i].a, H[i].b, i};
        } else if (H[i].c2 <= mid) {
            E[idx++] = {2, H[i].a, H[i].b, i};
        }
    }
    int sid = 0, cnt = 0;
    sort(E, E+idx);
    for (int i = 0; i < idx; i++) {
        int u = E[i].u, v = E[i].v;
        if (uf.find(u) != uf.find(v)) {
            S[sid++] = {E[i].id, E[i].t};
            if (E[i].t == 1) cnt++;
            uf.join(u, v);
        }
    }
    return uf.count(0) == N && cnt >= K;
}

int main() {
    scanf("%d%d%d", &N, &K, &M);
    M--;
    for (int i = 0; i < M; i++) {
        int a, b, c1, c2;
        scanf("%d%d%d%d", &a, &b, &c1, &c2);
        a--; b--;
        H[i] = {a, b, c1, c2};
    }

    UnionFind uf(N);
    int lo = 0, hi = 30001;
    while (lo < hi - 1) {
        int mid = (lo + hi) / 2;
        if (feasible(uf, mid)) hi = mid;
        else lo = mid;
    }
    printf("%d\n", hi);

    feasible(uf, hi);
    sort(S, S+N-1);
    for (int i = 0; i < N-1; i++) {
        printf("%d %d\n", S[i].t+1, S[i].p);
    }

    return 0;
}
