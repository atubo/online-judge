// https://www.luogu.org/problem/P2137
// Gty的妹子树

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

const int MAXN = 60010;
int B[MAXN], E[MAXN], D[MAXN], W[MAXN], W2[MAXN], WR[MAXN], U[MAXN];

class MergeTree {
private:
    int n_;
    const int *a_;
    int **sorted;

    void build(int depth, int left, int right) {
        if (left == right) {
            sorted[depth][left] = a_[left];
            return;
        }

        int mid = (left + right) / 2;
        build(depth+1, left, mid);
        build(depth+1, mid+1, right);

        int i = left, j = mid + 1, k = left;
        while (i <= mid && j <= right) {
            if (sorted[depth+1][i] <= sorted[depth+1][j]) {
                sorted[depth][k++] = sorted[depth+1][i++];
            } else {
                sorted[depth][k++] = sorted[depth+1][j++];
            }
        }
        while (i <= mid) sorted[depth][k++] = sorted[depth+1][i++];
        while (j <= right) sorted[depth][k++] = sorted[depth+1][j++];
    }

    // find number of elements <= key
    int query(int depth, int left, int right, int qleft, int qright, int key) {
        if (qright < left || qleft > right) return 0;
        if (qleft <= left && right <= qright) {
            auto b = sorted[depth] + left;
            auto e = sorted[depth] + right + 1;
            return upper_bound(b, e, key) - b;
        }

        int mid = (left + right) / 2;
        return query(depth+1, left, mid, qleft, qright, key) +
               query(depth+1, mid+1, right, qleft, qright, key);
    }

public:
    MergeTree() {
        int depth = log2(MAXN)+2;
        sorted = new int*[depth]{};
        for (int i = 0; i < depth; i++) {
            sorted[i] = new int[MAXN]{};
        }
    }

    ~MergeTree() {
        int depth = log2(MAXN)+2;
        for (int i = 0; i < depth; i++) {
            delete[] sorted[i];
        }
        delete[] sorted;
    }

    void build(int *a, int n) {
        a_ = a;
        n_ = n;
        build(0, 0, n_-1);
    }

    // find number of elements > key
    int query(int qleft, int qright, int key) {
        return qright - qleft + 1 - query(0, 0, n_-1, qleft, qright, key);
    }
};

struct Op {
    int t, u, x;
} OP[MAXN/2];

int N, M;
int FA[MAXN][16];
int BLK;
int currIdx;

void dfs(const Graph &g, int u, int fa, int d) {
    B[u] = currIdx++;
    D[u] = d;
    FA[u][0] = fa;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) dfs(g, v, u, d+1);
    }
    E[u] = currIdx-1;
}

void build_fa(int u, int fa) {
    D[u] = D[fa] + 1;
    FA[u][0] = fa;
    for (int i = 1; i < 16; i++) {
        int v = FA[u][i-1];
        if (v == -1) break;
        FA[u][i] = FA[v][i-1];
    }
}

void build_fa(int sz) {
    for (int u = 0; u < sz; u++) {
        for (int i = 1; i < 16; i++) {
            int v = FA[u][i-1];
            if (v == -1) break;
            FA[u][i] = FA[v][i-1];
        }
    }
}

void update_wt(int idx, int sz) {
    if (idx == 0) {
        for (int u = 0; u < sz; u++) {
            int d = B[u];
            U[d] = W[u];
        }
        return;
    }
    for (int i = (idx/BLK-1)*BLK; i < idx; i++) {
        if (OP[i].t != 0) W[OP[i].u] = OP[i].x;
    }
    for (int u = 0; u < sz; u++) {
        int d = B[u];
        U[d] = W[u];
    }
}

void build(Graph &g, MergeTree &mt, int idx, int sz) {
    memset(B, -1, sz*sizeof(int));
    currIdx = 0;
    memset(FA, -1, sizeof(FA));
    dfs(g, 0, -1, 0);
    update_wt(idx, sz);
    mt.build(U, sz);
    build_fa(sz);
}

int up(int u, int d) {
    while (d) {
        int x = __builtin_ctz(d);
        u = FA[u][x];
        if (u == -1) return u;
        d = d - (1<<x);
    }
    return u;
}


void revise(const Graph &g, int idx, int u, int x, int &ans) {
    int sz = 0;
    for (int i = (idx/BLK)*BLK; i < idx; i++) {
        if (OP[i].t == 0) continue;
        int v = OP[i].u;
        if (D[v] < D[u]) continue;
        if (up(v, D[v]-D[u]) != u) continue;
        if (OP[i].t == 1) {
            if (W2[v] == -1) {
                W2[v] = W[v];
                WR[sz++] = v;
            }
            if (W2[v] > x) ans--;
            if (OP[i].x > x) ans++;
            W2[v] = OP[i].x;
        } else {
            if (OP[i].x > x) ans++;
            W2[v] = OP[i].x;
            WR[sz++] = v;
        }
    }
    for (int i = 0; i < sz; i++) {
        W2[WR[i]] = -1;
    }
}


int main() {
    memset(W2, -1, sizeof(W2));
    memset(B, -1, sizeof(B));
    scanf("%d", &N);
    Graph g(MAXN, 2*MAXN);
    MergeTree mt;
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &W[i]);
    }
    int sz = N;
    int lastans = 0;
    scanf("%d", &M);
    BLK = max(3, int(sqrt(M*log2(N))));
    //BLK = int(sqrt(N));
    //printf("BLK=%d\n", BLK);
    for (int i = 0; i < M; i++) {
        if (i % BLK == 0) build(g, mt, i, sz);

        int op, u, x;
        scanf("%d%d%d", &op, &u, &x);
        u ^= lastans;
        x ^= lastans;
        u--;
        if (op == 0) {
            int ret = 0;
            if (B[u] != -1) ret = mt.query(B[u], E[u], x);
            revise(g, i, u, x, ret);
            printf("%d\n", ret);
            lastans = ret;
        } else if (op == 2) {
            g.addEdge(u, sz);
            g.addEdge(sz, u);
            build_fa(sz, u);
            sz++;
        }
        OP[i] = {op, op == 2 ? sz-1: u, x};
    }
    return 0;
}
