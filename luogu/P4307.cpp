// https://www.luogu.org/problemnew/show/P4307
// [JSOI2009]球队收益 / 球队预算

#include <bits/stdc++.h>
using namespace std;

class MincostMaxflow {
    // NOTE
    // 1. nodes are 0-indexed
    // 2. call init() before you use it again
public:
    const static int64_t INF = 1e13;

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
    struct Edge {
        Edge *next, *op;
        int t;
        int64_t c, v;    // node, residual, cost
    };

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
const int MAXN = 5010;
int N, M;
int A[MAXN], B[MAXN], C[MAXN], D[MAXN];
int K[MAXN], KS[MAXN];
struct Match {
    int s, t;
} MA[1010];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
    }
    for (int i = 1; i <= M; i++) {
        int s, t;
        scanf("%d%d", &s, &t);
        MA[i] = {s, t};
        K[s]++;
        K[t]++;
    }

    for (int i = 1; i <= N; i++) {
        KS[i] = K[i] + KS[i-1];
    }

    int tot = 0;
    for (int i = 1; i <= N; i++) {
        tot += C[i]*A[i]*A[i] + D[i]*(B[i]+K[i])*(B[i]+K[i]);
    }

    MincostMaxflow flow(N+3*M+2, 7*M);
    const int src = 0, dst = N+3*M+1;

    for (int i = 1; i <= M; i++) {
        flow.addEdge(src, i, 0, 1);
        int s = MA[i].s, t = MA[i].t;
        flow.addEdge(i, M+s, 0, 1);
        flow.addEdge(i, M+t, 0, 1);
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= K[i]; j++) {
            flow.addEdge(M+i, M+N+KS[i-1]+j, 0, 1);
            int cost = C[i] + D[i] + 2*C[i]*(A[i]+j-1) - 2*D[i]*(B[i]+K[i]+1-j);
            flow.addEdge(M+N+KS[i-1]+j, dst, cost, 1);
        }
    }

    auto ret = flow.mincostFlow(src, dst);
    printf("%ld\n", tot + ret.second);

    return 0;
}
