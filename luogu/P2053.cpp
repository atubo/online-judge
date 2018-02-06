// https://www.luogu.org/problemnew/show/P2053
// [SCOI2007]修车

#include <bits/stdc++.h>
using namespace std;

namespace MincostMaxflowNS {
    // NOTE
    // 1. set up the following values
    // 2. it is required S < other nodes < T (see code in SPFA)
    // 3. MAXM must be twice the number of edges you added
    // 4. call init() before you use it again
    const int INF = 100000;
    const int MAXM = 80000, MAXN = 1000;
    int S, T, EC = -1;

    struct Edge {
        Edge *next, *op;
        int t, c, v;    // node, residual, cost
    } ES[MAXM], *V[MAXN];

    void init() {
        EC = -1;
        memset(V, 0, sizeof(V));
    }

    struct Queue {
        int Q[MAXN], QH, QL, Size;
        bool inq[MAXN];

        void ins(int v) {
            if (++QL >= MAXN) QL = 0;
            Q[QL] = v;
            inq[v] = true;
            Size++;
        }

        int pop() {
            int r = Q[QH];
            inq[r] = false;
            Size--;
            if (++QH >= MAXN) QH = 0;
            return r;
        }

        void reset() {
            memset(Q, 0, sizeof(Q));
            QH = Size = 0;
            QL = -1;
        }
    } Q;


    int sp[MAXN], prev[MAXN];
    Edge *path[MAXN];

    void addEdge(int a, int b, int v, int c) {
        Edge e1 = {V[a], 0, b, c, v}, e2 = {V[b], 0, a, 0, -v};
        ES[++EC] = e1; V[a] = &ES[EC];
        ES[++EC] = e2; V[b] = &ES[EC];
        V[a]->op = V[b]; V[b]->op = V[a];
    }

    bool SPFA() {
        int u, v;
        for (u = S; u <= T; u++) sp[u] = INF;
        Q.reset();
        Q.ins(S);
        sp[S] = 0; prev[S] = -1;
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
        return sp[T] != INF;
    }

    int argument() {
        int i, cost = INF, flow = 0;
        Edge *e;
        for (i = T; prev[i] != -1; i = prev[i]) {
            e = path[i];
            if (e->c < cost) cost = e->c;
        }
        for (i = T; prev[i] != -1; i = prev[i]) {
            e = path[i];
            e->c -= cost; e->op->c += cost;
            flow += e->v * cost;
        }
        return flow;
    }

    int mincostFlow() {
        int flow = 0;
        while (SPFA()) {
            flow += argument();
        }
        return flow;
    }
}

const int MAXN = 62, MAXM = 10;
int M, N;
int C[MAXN][MAXM];

int car(int i) {return i;}
int tech(int i, int j) {return N + (i-1)*N + j;}

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            scanf("%d", &C[i][j]);
        }
    }
    int S = 0, T = N + N*M + 1;
    MincostMaxflowNS::S = S;
    MincostMaxflowNS::T = T;

    for (int i = 1; i <= N; i++) {
        MincostMaxflowNS::addEdge(S, car(i), 0, 1);
        for (int j = 1; j <= M; j++) {
            for (int k = 1; k <= N; k++) {
                MincostMaxflowNS::addEdge(car(i), tech(j, k), k * C[i][j], 1);
                if (i == 1) MincostMaxflowNS::addEdge(tech(j, k), T, 0, 1);
            }
        }
    }
    printf("%.2f", double(MincostMaxflowNS::mincostFlow())/N);
    return 0;
}
