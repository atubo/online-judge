// https://www.luogu.org/problemnew/show/P2488
// [SDOI2011]工作安排

#include <bits/stdc++.h>
using namespace std;

const int64_t INF = 1e13;

struct Edge {
    Edge *next, *op;
    int t;
    int64_t c, v;    // node, residual, cost
};

class MincostMaxflow {
    // NOTE
    // 1. nodes are 0-indexed
    // 2. call init() before you use it again
public:

    MincostMaxflow(int N_, int M):N(N_), Q(N_) {
        V = new Edge*[N]{};
        ES = new Edge[2*M]{};
        sp = new int64_t[N]{};
        prev = new int[N]{};
        path = new Edge*[N]{};
        init();
    }

    ~MincostMaxflow() {
        delete[] V;
        delete[] ES;
        delete[] sp;
        delete[] prev;
        delete[] path;
    }

    void addEdge(int a, int b, int64_t cost, int64_t capacity) {
        Edge e1 = {V[a], 0, b, capacity, cost}, e2 = {V[b], 0, a, 0, -cost};
        ES[++EC] = e1; V[a] = &ES[EC];
        ES[++EC] = e2; V[b] = &ES[EC];
        V[a]->op = V[b]; V[b]->op = V[a];
    }

    struct FlowCost {
        int64_t flow, cost;
        FlowCost& operator += (const FlowCost &other) {
            flow += other.flow;
            cost += other.cost;
            return *this;
        }
    };

    // returns maxflow, mincost
    pair<int64_t, int64_t> mincostFlow(int s, int t) {
        FlowCost fc{};
        while (SPFA(s, t)) {
            fc += augment(t);
        }
        return make_pair(fc.flow, fc.cost);
    }

private:
    int N;
    Edge *ES;
    Edge **V;
    int EC = -1;

    void init() {
        EC = -1;
        memset(V, 0, N * sizeof(Edge*));
    }

    struct Queue {
        Queue(int N_): N(N_) {
            Q = new int[N]{};
            inq = new bool[N]{};
        }

        ~Queue() {
            delete[] Q;
            delete[] inq;
        }

        int N;
        int *Q;
        int QH, QL, Size;
        bool *inq;

        void ins(int v) {
            if (++QL >= N) QL = 0;
            Q[QL] = v;
            inq[v] = true;
            Size++;
        }

        int pop() {
            int r = Q[QH];
            inq[r] = false;
            Size--;
            if (++QH >= N) QH = 0;
            return r;
        }

        void reset() {
            memset(Q, 0, N* sizeof(int));
            QH = Size = 0;
            QL = -1;
        }
    };
    Queue Q;


public:
    int64_t *sp;
    int *prev;
    Edge **path;

    bool SPFA(int s, int t) {
        int u, v;
        for (u = 0; u < N; u++) sp[u] = INF;
        Q.reset();
        Q.ins(s);
        sp[s] = 0; prev[s] = -1;
        while (Q.Size) {
            u = Q.pop();
            for (Edge *k = V[u]; k; k = k->next) {
                v = k->t;
                if (k->c > 0 && sp[u] + k->v < sp[v]) {
                    sp[v] = sp[u] + k->v;
                    prev[v] = u;
                    path[v] = k;
                    if (!Q.inq[v]) Q.ins(v);
                }
            }
        }
        return sp[t] != INF;
    }

    FlowCost augment(int t) {
        int i;
        int64_t low = INF, cost = 0;
        Edge *e;
        for (i = t; prev[i] != -1; i = prev[i]) {
            e = path[i];
            if (e->c < low) low = e->c;
        }
        for (i = t; prev[i] != -1; i = prev[i]) {
            e = path[i];
            e->c -= low; e->op->c += low;
            cost += e->v * low;
        }
        return FlowCost{low, cost};
    }
};

const int MAXN = 260;
int M, N;
int C[MAXN], A[MAXN][MAXN], S[MAXN], T[MAXN][6], W[MAXN][6];
int idx[MAXN];

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &S[i]);
        for (int j = 1; j <= S[i]; j++) {
            scanf("%d", &T[i][j]);
        }
        for (int j = 0; j <= S[i]; j++) {
            scanf("%d", &W[i][j]);
        }
    }

    const int src = 0, dst = N + M + 1;
    MincostMaxflow flow(dst + 1, N + M + N*M);
    for (int i = 0; i < N; i++) {
        int u = i + 1;
        flow.addEdge(src, u, 0, C[i]);
        for (int j = 0; j < M; j++) {
            if (A[j][i] > 0) {
                int v = N + 1 + j;
                flow.addEdge(u, v, 0, INF);
            }
        }
    }

    for (int i = 0; i < M; i++) {
        int u = N + 1 + i;
        int64_t cap = (S[i] == 0 ? INF : T[i][1]);
        flow.addEdge(u, dst, W[i][0], cap);
    }

    int64_t tot_cap = 0, tot_cost = 0;
    while (true) {
        bool ok = flow.SPFA(src, dst);
        if (!ok) break;
        auto f = flow.augment(dst);
        tot_cap += f.flow;
        tot_cost += f.cost;
        Edge *e = flow.path[dst];
        if (e->c == 0) {
            int j = flow.prev[dst] - N - 1;
            int k = ++idx[j];
            e->c = (k == S[j] ? INF : T[j][k+1] - T[j][k]);
            e->v = W[j][k];
            e->op->c = 0;
            e->op->v = -W[j][k];
        }
    }
    printf("%lld", tot_cost);

    return 0;
}
