// https://www.luogu.org/problemnew/show/P4197
// Peaks

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using Multiset = tree<int, null_type, greater_equal<int>, rb_tree_tag,
      tree_order_statistics_node_update>;

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

const int MAXN = 100010;
const int MAXM = 500010;
int N, M, NQ;
int H[MAXN];

struct Road {
    int u, v, w;
    bool operator < (const Road &other) const {
        if (w != other.w) return w < other.w;
        if (u != other.u) return u < other.u;
        return v < other.v;
    }
} R[MAXM];

struct Query {
    int v, x, k, id;
    bool operator < (const Query &other) const {
        if (x != other.x) return x < other.x;
        return id < other.id;
    }
} Q[MAXM];

int ans[MAXM];

void merge(const Road &road, UnionFind &uf, vector<Multiset> &mss) {
    int u = uf.find(road.u);
    int v = uf.find(road.v);
    if (u == v) return;
    uf.join(u, v);
    if (uf.find(u) != u) swap(u, v);
    for (auto it = mss[v].begin(); it != mss[v].end(); ++it) {
        mss[u].insert(*it);
    }
}

int query(const Query query, UnionFind &uf, const vector<Multiset> &mss) {
    int v = uf.find(query.v);
    int k = query.k;
    if (uf.count(v) < k) return -1;
    const auto& ms = mss[v];
    return *ms.find_by_order(k-1);
}

int main() {
    scanf("%d%d%d", &N, &M, &NQ);
    for (int i = 0; i < N; i++) {
        scanf("%d", &H[i]);
    }

    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--;
        R[i] = {a, b, c};
    }

    for (int i = 0; i < NQ; i++) {
        int v, x, k;
        scanf("%d%d%d", &v, &x, &k);
        v--;
        Q[i] = {v, x, k, i};
    }
    vector<Multiset> mss(N);
    for (int i = 0; i < N; i++) {
        mss[i].insert(H[i]);
    }

    UnionFind uf(N);
    sort(R, R+M);
    sort(Q, Q+NQ);

    int last = -1;
    for (int i = 0; i < NQ; i++) {
        int x = Q[i].x;
        while (last < N-1 && R[last+1].w <= x) {
            merge(R[last+1], uf, mss);
            last++;
        }
        ans[Q[i].id] = query(Q[i], uf,mss);
    }

    for (int i = 0; i < NQ; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
