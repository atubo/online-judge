// https://www.luogu.org/problemnew/show/P1084
// 疫情控制

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to, wt;
    };

    vector<int> head;
    int eidx;
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

// note it's 1-indexed
class SegmentTree {
    int N;
    int *val, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val = new int[4*N]{};
        lazy = new int[4*N]{};
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
    int query(int a, int b) {
        return query(1, a, b, 1, N);
    }

private:
    // add t to range [a, b], current node range is [l, r]
    void update(int k, int t, int l, int r, int a, int b) {
        if (a > b) return;
        pushDown(k, l, r);
        if (a <= l && r <= b) {
            val[k] = (t == 1 ? r-l+1 : 0);
            lazy[k] = t;
            return;
        }
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k,   t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        val[k] = val[2*k] + val[2*k+1];
    }

    void pushDown(int k, int l, int r) {
        if (!lazy[k] || l == r) return;
        lazy[2*k] = lazy[k];
        lazy[2*k+1] = lazy[k];
        int mid = (l + r) / 2;
        val[2*k] = (lazy[k] == 1 ? mid - l + 1 : 0);
        val[2*k+1] = (lazy[k] == 1 ? r - mid : 0);
        lazy[k] = 0;
    }

    // query range sum in [a, b], current node is [L, R]
    int query(int k, int a, int b, int L, int R) {
        if (!k) return 0;
        if (b < L || a > R) return 0;
        pushDown(k, L, R);
        if (a <= L && R <= b) return val[k];
        int sum = 0;
        int mid = (L + R) / 2;
        if (a <= mid) sum += query(2*k, a, b, L, mid);
        if (mid < b)  sum += query(2*k+1, a, b, mid+1, R);
        return sum;
    }
};

const int MAXN = 50010;
int N, M;
int64_t dist[MAXN];
int depth[MAXN], fa[MAXN][16];
int64_t maxdist;
int troops[MAXN], anc[MAXN], L[MAXN], R[MAXN];
int root_children, curr_rc, curr_leaf_id;

void dfs(const Graph &g, int u, int f, int64_t dst, int dpt) {
    if (f == 0) {
        root_children++;
        curr_rc = u;
    }
    L[u] = curr_leaf_id;
    maxdist = max(maxdist, dst);
    fa[u][0] = f;
    dist[u] = dst;
    depth[u] = dpt;
    bool is_leaf = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (v != f) {
            dfs(g, v, u, dst+w, dpt+1);
            is_leaf = false;
        }
    }
    if (is_leaf) {
        curr_leaf_id++;
    }
    if (u != 0) anc[u] = curr_rc;
    R[u] = curr_leaf_id - 1;
}

void build() {
    for (int k = 1; k < 16; k++) {
        for (int u = 0; u < N; u++) {
            if (depth[u] < (1<<k)) continue;
            fa[u][k] = fa[fa[u][k-1]][k-1];
        }
    }
}

int moveDist(int t, int64_t d) {
    for (int k = 15; k >= 0; k--) {
        if (fa[t][k] != -1 && dist[t] - dist[fa[t][k]] <= d) {
            d -= (dist[t] - dist[fa[t][k]]);
            t = fa[t][k];
        }
    }
    return t;
}

bool cover(vector<int64_t> &res, vector<int64_t> &req) {
    if (req.empty()) return true;
    sort(res.begin(), res.end());
    sort(req.begin(), req.end());

    int p = 0, q = 0;
    while (true) {
        while (p < (int)res.size() && res[p] < req[q]) p++;
        if (p == (int)res.size()) return false;
        q++;
        p++;
        if (q == (int)req.size()) return true;
    }
    assert(0);
    return false;
}


bool check(int64_t d, const Graph &g, SegmentTree &st) {
    st.update(1, 1, curr_leaf_id);
    vector<int64_t> res;
    for (int i = 0; i < M; i++){
        int t = troops[i];
        int p = moveDist(t, d);
        if (p != 0) {
            st.update(-1, L[p]+1, R[p]+1);
        } else {
            int q = anc[t];
            int64_t rg = d - dist[t];
            if (rg < dist[q] && st.query(L[q]+1, R[q]+1)) {
                st.update(-1, L[q]+1, R[q]+1);
            } else {
               res.push_back(rg);
            }
        } 
    }

    vector<int64_t> req;
    for (int eidx = g.head[0]; ~eidx; eidx = g.E[eidx].next) {
        int u = g.E[eidx].to;
        int64_t w = g.E[eidx].wt;
        if (st.query(L[u]+1, R[u]+1)) req.push_back(w);
    }

    bool ans = cover(res, req);
    
    return ans;
}

bool cmp(int x, int y) {
    return dist[x] > dist[y];
}

int main() {
    memset(fa, -1, sizeof(fa));
    scanf("%d", &N);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g.addEdge(u, v, w);
        g.addEdge(v, u, w);
    }

    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int x;
        scanf("%d", &x);
        x--;
        troops[i] = x;
    }
    dfs(g, 0, -1, 0, 0);

    build();

    if (M < root_children) {
        printf("-1");
        return 0;
    }

    sort(troops, troops+M, cmp);

    SegmentTree st(curr_leaf_id);
    int64_t lo = -1, hi = 2*maxdist;
    while (lo < hi-1) {
        int64_t mid = (lo + hi) / 2;
        if (check(mid, g, st)) hi = mid;
        else lo = mid;
    }
    printf("%ld", hi);

    return 0;
}
