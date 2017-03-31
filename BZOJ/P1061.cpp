// http://www.lydsy.com/JudgeOnline/problem.php?id=1061
// 1061: [Noi2008]志愿者招募

#include <cstdio>
#include <cstring>

using namespace std;

namespace MincostMaxflowNS {
    // need to set up these values
    // note it is required S < other nodes < T (see code in SPFA)
    const int INF = 1000000;
    const int MAXM = 50000, MAXN = 2000;
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

const int MAXN = 1010;
int D[MAXN];

int main() {
    using namespace MincostMaxflowNS;
    int N, M;
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &D[i]);
    }

    S = 0;
    T = N + 2;
    for (int i = 1; i <= M; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(a, b+1, c, INF);
    }

    for (int i = 1; i <= N+1; i++) {
        int c = D[i] - D[i-1];
        if (c >= 0) addEdge(S, i, 0, c);
        else addEdge(i, T, 0, -c);
        if (i > 1) addEdge(i, i-1, 0, INF);
    }

    printf("%d\n", mincostFlow());
    return 0;
}
