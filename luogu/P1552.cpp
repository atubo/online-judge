// https://www.luogu.org/problemnew/show/P1552
// [APIO2012]派遣

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
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
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

class PersistentSegmentTree {
public:
    struct Node {
        // L and R are indices of its children
        // real left and right boundaries are not kept in the node
        // to save memory
        int L, R;
        int cnt;
        int64_t sum;

        Node(): L(0), R(0), cnt(0), sum(0) {}
    };

    int N; // number of positions, index is 1-based
    int M; // number of weights, index is 0-based
    int *root;
    Node *T;
    int T_cnt = 1;

    PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
        root = new int[N+1]{};
        T = new Node[(N+1) * int(log2(M)+2)]{};
    }

    ~PersistentSegmentTree() {
        delete[] root;
        delete[] T;
    }

    // for user's convenience
    void insert(int currRootIndex, int prevRootIndex, int x, int t) {
        root[currRootIndex] = root[prevRootIndex];
        insert(root[currRootIndex], x, t, 0, M-1);
    }

    // query in range [start, end]
    int query(int rootIndex, int start, int end) {
        return query(root[rootIndex], start, end, 0, M-1);
    }

    int dispatch(int x, int y, int budget) {
        return dispatch(root[x], root[y], budget, 0, M-1);
    }

private:
    // insert a new weight node x with value t
    // current range is [l, r]
    void insert(int &now, int x, int t, int l, int r) {
        T[T_cnt++] = T[now];
        now = T_cnt-1;
        T[now].cnt++;
        T[now].sum += t;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (x <= mid) insert(T[now].L, x, t, l, mid);
        else          insert(T[now].R, x, t, mid+1, r);
    }

    int64_t query(int node, int start, int end, int l, int r) {
        if (l > r) return 0;
        if (start <= l && r <= end) return T[node].sum;
        int mid = (l + r) / 2;
        int64_t ret = 0;
        if (start <= mid) ret += query(T[node].L, start, end, l, mid);
        if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
        return ret;
    }

    int dispatch(int nodex, int nodey, int budget, int l, int r) {
        if (T[nodey].sum - T[nodex].sum <= budget) {
            return T[nodey].cnt - T[nodex].cnt;
        }
        int leftx = T[nodex].L;
        int lefty = T[nodey].L;
        int rightx = T[nodex].R;
        int righty = T[nodey].R;
        int64_t sumleft = T[lefty].sum - T[leftx].sum;
        int cntleft = T[lefty].cnt - T[leftx].cnt;
        int mid = (l + r) / 2;
        if (sumleft >= budget) {
            return dispatch(leftx, lefty, budget, l, mid);
        } else {
            return cntleft + dispatch(rightx, righty, budget-sumleft, mid+1, r);
        }
    }
};

const int MAXN = 100010;
int N, M;
int B[MAXN], C[MAXN], L[MAXN];
int dfn[MAXN], out[MAXN], rev[MAXN];
int curr;

void dfs(const Graph &g, int u) {
    dfn[u] = curr;
    rev[curr] = u;
    curr++;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        dfs(g, v);
    }
    out[u] = curr - 1;
}

int id(const vector<pair<int, int>>& sc, const pair<int, int> &p) {
    int ret = lower_bound(sc.begin(), sc.end(), p) - sc.begin();
    return ret;
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, N-1);
    vector<pair<int, int>> sorted_c(N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &B[i], &C[i], &L[i]);
        B[i]--;
        if (B[i] >= 0) g.addEdge(B[i], i);
        sorted_c[i] = make_pair(C[i], i);
    }
    dfs(g, 0);
    sort(sorted_c.begin(), sorted_c.end());

    PersistentSegmentTree pst(N, N);
    for (int i = 1; i <= N; i++) {
        int x = rev[i-1];
        int weightid = id(sorted_c, make_pair(C[x], x));
        pst.insert(i, i-1, weightid, C[x]);
    }
    int64_t ans = 0;
    for (int i = 0; i < N; i++) {
        int x = dfn[i] + 1;
        int y = out[i] + 1;
        int64_t d = pst.dispatch(x-1, y, M);
        ans = max(ans, d * L[i]);
    }
    printf("%lld", ans);

    return 0;
}
