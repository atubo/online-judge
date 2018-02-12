// https://www.luogu.org/problemnew/show/P2153
// [SDOI2009]晨跑

#include <bits/stdc++.h>
using namespace std;

class MincostMaxflow {
    // NOTE
    // 1. set up the following values
    // 2. nodes are 0-indexed
    // 3. MAXM must be twice the number of edges you added
    // 4. call init() before you use it again
public:
    const static int INF = 100000000;
    const static int MAXM = 42000;

    MincostMaxflow(int N_):N(N_), Q(N_) {
        V = new Edge*[N]{};
        ES = new Edge[MAXM]{};
        sp = new int[N]{};
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

    void addEdge(int a, int b, int cost, int capacity) {
        Edge e1 = {V[a], 0, b, capacity, cost}, e2 = {V[b], 0, a, 0, -cost};
        ES[++EC] = e1; V[a] = &ES[EC];
        ES[++EC] = e2; V[b] = &ES[EC];
        V[a]->op = V[b]; V[b]->op = V[a];
    }

    struct FlowCost {
        int flow, cost;
        FlowCost& operator += (const FlowCost &other) {
            flow += other.flow;
            cost += other.cost;
            return *this;
        }
    };

    // returns maxflow, mincost
    pair<int, int> mincostFlow(int s, int t) {
        FlowCost fc{};
        while (SPFA(s, t)) {
            fc += argument(t);
        }
        return make_pair(fc.flow, fc.cost);
    }

private:
    int N;
    struct Edge {
        Edge *next, *op;
        int t, c, v;    // node, residual, cost
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


    int *sp, *prev;
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

    FlowCost argument(int t) {
        int i, low = INF, cost = 0;
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

int in(int i) {
    return 2*i-1;
}

int out(int i) {
    return 2*i;
}

int N, M;
int main() {
    scanf("%d%d", &N, &M);
    int S = 0, T = 2*N+1;
    MincostMaxflow flow(T+1);
    flow.addEdge(S, in(1), 0, MincostMaxflow::INF);
    flow.addEdge(out(N), T, 0, MincostMaxflow::INF);
    flow.addEdge(in(1), out(1), 0, MincostMaxflow::INF);
    flow.addEdge(in(N), out(N), 0, MincostMaxflow::INF);
    for (int i = 2; i < N; i++) {
        flow.addEdge(in(i), out(i), 0, 1);
    }
    int days = 0, dist = 0 ;
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (a == 1 && b == N) {
            days++;
            dist += c;
        } else {
            flow.addEdge(out(a), in(b), c, 1);
        }
    }

    auto res = flow.mincostFlow(S, T);
    printf("%d %d\n", res.first + days, res.second + dist);
    return 0;
}
