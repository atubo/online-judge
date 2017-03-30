// https://www.luogu.org/problem/show?pid=2255
// [USACO14JAN]记录奥林比克Recording the M…

#include <bits/stdc++.h>
using namespace std;


namespace MincostMaxflowNS {
    // need to set up these values
    // note it is required S < other nodes < T (see code in SPFA)
    const int INF = 1000000;
    const int MAXM = 250000, MAXN = 500;
    int S, T, EC = -1;

    struct Edge {
        Edge *next, *op;
        int t, c, v;    // node, residual, cost
    } ES[MAXM], *V[MAXN];

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

using PII = pair<int, int>;
const int MAXN = 160;
int N;
PII A[MAXN];

int main() {
    using namespace MincostMaxflowNS;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d %d", &A[i].first, &A[i].second);
    }

    S = 0;
    int SP = 1;
    int TP = 2 * N + 2;
    T = 2 * N + 3;

    addEdge(S, SP, 0, 2);
    addEdge(TP, T, 0, 2);

    for (int i = 1; i <= N; i++) {
        int p = 2 * i;
        int q = p + 1;
        addEdge(SP, p, 0, 1);
        addEdge(p, q, -1, 1);
        addEdge(q, TP, 0, 1);

        for (int j = 1; j <= N; j++) {
            if (i == j || A[i].second > A[j].first) continue;
            int p2 = 2 * j;
            addEdge(q, p2, 0, 1);
        }
    }

    printf("%d\n", -mincostFlow());
    return 0;
}
