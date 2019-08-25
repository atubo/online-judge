// https://www.luogu.org/problem/P3588
// [POI2015]PUS

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
        bool wt;
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

public:
    SegmentTree(int N_): N(N_) {
        idx = new int[N+1]{};
        build();
    }

    ~SegmentTree() {
        delete[] idx;
    }

    void connect(Graph &g, int a, int b, int u) {
        if (a > b) return;
        connect(g, 1, 1, N, a, b, u);
    }

    void buildGraph(Graph &g) {
        buildGraph(g, 1, 1, N);
    }

    int *idx;
    int maxidx = 0;

private:
    void build() {
        build(1, 1, N);
    }

    void build(int k, int l, int r) {
        if (l == r) {
            idx[l] = k;
            maxidx = max(maxidx, k);
            return;
        }
        int mid = (l + r) / 2;
        build(2*k, l, mid);
        build(2*k+1, mid+1, r);
    }

    void buildGraph(Graph &g, int k, int l, int r) {
        if (l == r) return;
        g.addEdge(2*k, k, 0);
        g.addEdge(2*k+1, k, 0);
        int mid = (l + r) / 2;
        buildGraph(g, 2*k, l, mid);
        buildGraph(g, 2*k+1, mid+1, r);
    }

    void connect(Graph &g, int k, int l, int r, int a, int b, int u) {
        if (b < l || a > r) return;
        if (a <= l && r <= b) {
            g.addEdge(k, u, 1);
            return;
        }
        int mid = (l + r) / 2;
        if (a <= mid) connect(g, 2*k, l, mid, a, b, u);
        if (mid < b)  connect(g, 2*k+1, mid+1, r, a, b, u);
    }
};

const int INF = 1000000000;
const int MAXN =  100010, MAXM = 200010;
const int MAXSK = 300010;
int N, S, M;
int P[4*MAXN+MAXM];
int U[4*MAXN+MAXM];
int deg[4*MAXN+MAXM];
int V[4*MAXN+MAXM];

bool solve(const Graph &g, int n) {
    for (int u = 1; u <= n; u++) {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            deg[v]++;
        }
    }

    queue<int> q;
    for (int u = 1; u <= n; u++) {
        if (deg[u] == 0) {
            q.push(u);
            V[u] = 1;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (P[u]) {
            if (P[u] < V[u]) return false;
            V[u] = P[u];
        }
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            int x = V[u] + w;
            V[v] = max(V[v], x);
            if (--deg[v] == 0) q.push(v);
        }
    }

    for (int u = 1; u <= n; u++) {
        if (V[u] == 0 || V[u] > INF) return false;
    }

    return true;
}

int main() {
    scanf("%d%d%d", &N, &S, &M);
    SegmentTree st(N);
    for (int i = 0; i < S; i++) {
        int p, d;
        scanf("%d%d", &p, &d);
        P[st.idx[p]] = d;
    }

    Graph g(4*MAXN+MAXM, 20*MAXSK + 4*MAXN);

    int idx = st.maxidx + 1;
    for (int i = 0; i < M; i++) {
        int l, r, k, x;
        scanf("%d%d%d", &l, &r, &k);
        int x0 = l;
        int sn = idx++;
        for (int j = 0; j < k; j++) {
            scanf("%d", &x);
            st.connect(g, x0, x-1, sn);
            g.addEdge(sn, st.idx[x], 0);
            x0 = x + 1;
        }
        st.connect(g, x0, r, sn);
    }
    st.buildGraph(g);

    bool ok = solve(g, idx-1);
    if (ok) {
        printf("TAK\n");
        for (int i = 1; i <= N; i++) {
            printf("%d ", V[st.idx[i]]);
        }
        printf("\n");
    } else {
        printf("NIE\n");
    }

    return 0;
}
