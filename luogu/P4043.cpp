// https://www.luogu.org/problemnew/show/P4043
// [AHOI2014/JSOI2014]支线剧情

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

    int N;
    struct Edge {
        Edge *next, *op;
        int t;
        int64_t c, v;    // node, residual, cost
    };

    Edge *ES;
    Edge **V;
private:
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

const int MAXM = 6000;
const int MAXN = 310;
int N;
int in_deg[MAXN], out_deg[MAXN];

int main() {
    scanf("%d", &N);
    Graph g(N+2, MAXM);
    for (int i = 1; i <= N; i++) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            int b, t;
            scanf("%d%d", &b, &t);
            g.addEdge(i, b, t);
            out_deg[i]++;
            in_deg[b]++;
        }
    }
    for (int u = 1; u <= N; u++) {
        if (out_deg[u] < in_deg[u]) {
            g.addEdge(u, N+1, 0);
            if (out_deg[u] == 0) {
                in_deg[N+1] += in_deg[u];
                out_deg[u] = in_deg[u];
            }
        }
    }

    MincostMaxflow mc(N+3, MAXM);
    mc.addEdge(N+1, 1, 0, MincostMaxflow::INF);
    const int src = 0, dst = N+2;
    int tot = 0;
    for (int u = 1; u <= N+1; u++) {
        if (out_deg[u] > in_deg[u]) {
            mc.addEdge(u, dst, 0, out_deg[u]-in_deg[u]);
        } else if (out_deg[u] < in_deg[u]) {
            mc.addEdge(src, u, 0, in_deg[u]-out_deg[u]);
        }
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            tot += w;
            mc.addEdge(u, v, w, MincostMaxflow::INF);
        }
    }

    auto flow = mc.mincostFlow(src, dst);
    printf("%ld\n", tot + flow.second);

    return 0;
}
