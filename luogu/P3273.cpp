// https://www.luogu.org/problemnew/show/P3273
// [SCOI2011]棘手的操作

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    const int N;
    vector<int> rank;
    vector<int> parent;
    vector<int> size;
    vector<vector<int>> ch;

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
            ch[u].push_back(v);
            return u;
        } else {
            parent[u] = v;
            size[v] += size[u];
            if (rank[u] == rank[v]) {
                rank[v]++;
            }
            ch[v].push_back(u);
            return v;
        }
    }

public:
    UnionFind(int n): N(n) {
        rank.resize(N);
        parent.resize(N);
        size.resize(N);
        ch.resize(N);

        reset();
    }

    void reset() {
        for (int i = 0; i < N; i++) {
            makeSet(i);
        }
    }

    int find(int k) {
        while (parent[k] != k) k = parent[k];
        return k;
    }

    int join(int u, int v) {
        return link(find(u), find(v));
    }

    int count(int u) {
        return size[find(u)];
    }
};
const int MAXN = 300010;
int A[MAXN];

// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *val, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val = new int64_t[4*N]{};
        lazy = new int64_t[4*N]{};
    }

    ~SegmentTree() {
        delete[] val;
        delete[] lazy;
    }
    // add t to range [a, b]
    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    int64_t query(int a, int b) {
        return query(1, a, b, 1, N);
    }

    void print() {
        for (int i = 1; i <= N; i++) {
            printf("%lld ", query(i, i));
        }
        printf("\n");
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] += t;
            lazy[k] += t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val[k] = max(val[2*k], val[2*k+1]);
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] += lazy[k];
        lazy[2*k+1] += lazy[k];
        val[2*k] += lazy[k];
        val[2*k+1] += lazy[k];
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [L, R]
    int64_t query(int k, int a, int b, int L, int R) {
        if (!k) return INT_MIN;
        if (b < L || a > R) return INT_MIN;
        pushDown(k, L, R);
        if (a <= L && R <= b) return val[k];
        int64_t res = INT_MIN;
        int mid = (L + R) / 2;
        if (a <= mid) res = max(res, query(2*k, a, b, L, mid));
        if (mid < b)  res = max(res, query(2*k+1, a, b, mid+1, R));
        return res;
    }
};

int N, Q;
int dfn[MAXN];
bool vis[MAXN];
int curr = 1;

void dfs(const UnionFind &uf, int u) {
    vis[u] = true;
    dfn[u] = curr;
    curr++;
    for (int v: uf.ch[u]) {
        dfs(uf, v);
    }
}


struct Op {
    int type, node, size, v;
} op[MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    UnionFind uf(N);

    scanf("%d", &Q);
    char line[10];
    int x, y;
    for (int i = 0; i < Q; i++) {
        scanf("%s", line);
        if (line[0] == 'U') {
            scanf("%d%d", &x, &y);
            x--; y--;
            uf.join(x, y);
            op[i] = {0};
        } else if (line[0] == 'A' && line[1] == '1') {
            scanf("%d%d", &x, &y);
            op[i] = {1, x-1, 1, y};
        } else if (line[0] == 'A' && line[1] == '2') {
            scanf("%d%d", &x, &y);
            x--;
            int u = uf.find(x);
            op[i] = {2, u, uf.size[u], y};
        } else if (line[0] == 'A' && line[1] == '3') {
            scanf("%d", &x);
            op[i] = {3, -1, 0, x};
        } else if (line[0] == 'F' && line[1] == '1') {
            scanf("%d", &x);
            op[i] = {4, x-1, 1};
        } else if (line[0] == 'F' && line[1] == '2') {
            scanf("%d", &x);
            x--;
            int u = uf.find(x);
            op[i] = {5, u, uf.size[u]};
        } else if (line[0] == 'F' && line[1] == '3') {
            op[i] = {6};
        }
    }

    for (int u = 0; u < N; u++) {
        if (!vis[u]) dfs(uf, uf.find(u));
    }

    SegmentTree st(N);
    for (int i = 0; i < N; i++) {
        st.update(A[i], dfn[i], dfn[i]);
    }

    for (int i = 0; i < Q; i++) {
        int left, right;
        Op p = op[i];
        switch (op[i].type) {
            case 0:
                break;
            case 1:
                left = dfn[p.node];
                st.update(p.v, left, left);
                break;
            case 2:
                left = dfn[p.node];
                right = left + p.size - 1;
                st.update(p.v, left, right);
                break;
            case 3:
                st.update(p.v, 1, N);
                break;
            case 4:
                left = dfn[p.node];
                printf("%lld\n", st.query(left, left));
                break;
            case 5:
                left = dfn[p.node];
                right = left + p.size - 1;
                printf("%lld\n", st.query(left, right));
                break;
            case 6:
                printf("%lld\n", st.query(1, N));
                break;

            default:
                assert(0);
                break;
        }
    }

    return 0;
}
