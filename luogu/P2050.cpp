// https://www.luogu.org/problemnew/show/P2050
// [NOI2012]美食节

#include <bits/stdc++.h>
using namespace std;

vector<int> cook;

class MincostMaxflow {
    // NOTE
    // 1. nodes are 0-indexed
    // 2. call init() before you use it again
public:
    const static int INF = 1000000;

    MincostMaxflow(int N_, int M):N(N_), Q(N_) {
        V = new Edge*[N]{};
        ES = new Edge[2*M]{};
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
            fc += augment(t);
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


public:
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

    FlowCost augment(int t) {
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

const int MAXN = 45, MAXM = 110;
int N, M;
int P[MAXN], totp;
int T[MAXN][MAXM];
int S, D;
int max_cook;
int cooked[MAXM];

void init(MincostMaxflow &flow) {
    for (int i = 0; i < N; i++) {
        flow.addEdge(S, i+1, 0, P[i]);
    }
    for (int i = 0; i < M; i++) {
        int u = N + 1 + i;
        cook[u] = i;
        for (int j = 0; j < N; j++) {
            int v = j + 1;
            flow.addEdge(v, u, T[j][i], 1);
        }
        flow.addEdge(u, D, 0, 1);
    }
    max_cook = N + M;
}

void setup(MincostMaxflow &flow, int last_cook) {
    int u = ++max_cook;
    cook[u] = last_cook;
    for (int i = 0; i < N; i++) {
        flow.addEdge(i+1, u, (cooked[last_cook]+1) * T[i][last_cook], 1);
    }
    flow.addEdge(u, D, 0, 1);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &P[i]);
        totp += P[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &T[i][j]);
        }
    }

    S = 0, D = N + M + totp + 1;
    MincostMaxflow flow(D+1, N + N*M + M + totp*(N+1));
    cook.resize(N + N*M + M + totp*(N+1));

    int ans = 0;
    init(flow);
    flow.SPFA(S, D);
    auto f = flow.augment(D);
    ans += f.cost;

    for (int i = 1; i < totp; i++) {
        int last_cook = cook[flow.prev[D]];
        cooked[last_cook]++;
        setup(flow, last_cook);
        flow.SPFA(S, D);
        f = flow.augment(D);
        ans += f.cost;
    }
    printf("%d\n", ans);

    return 0;
}
