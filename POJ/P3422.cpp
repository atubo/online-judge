// http://poj.org/problem?id=3422
// Kaka's Matrix Travels

#include <cstdio>
#include <cstring>
using namespace std;

namespace MincostMaxflowNS {
    // need to set up these values
    // note it requires S < all other node < T
    const int INF = 1e8;
    const int MAXM = 20000, MAXN = 10000;
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

const int MAXN = 52;
int N, K;
int A[MAXN][MAXN];
const int DX[2] = {1, 0};
const int DY[2] = {0, 1};

bool inRange(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < N;
}

int main() {
    using namespace MincostMaxflowNS;

    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    S = 0;
    T = 2 * N * N + 1;

    addEdge(S, 1, 0, K);
    addEdge(T-1, T, 0, K);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int t = i * N + j + 1;
            int b = t + N * N;
            addEdge(t, b, -A[i][j], 1);
            addEdge(t, b, 0, K-1);

            for (int d = 0; d < 2; d++) {
                int k = i + DX[d];
                int l = j + DY[d];
                if (inRange(k, l)) {
                    int nt = k * N + l + 1;
                    addEdge(b, nt, 0, INF);
                }
            }
        }
    }

    printf("%d\n", -mincostFlow());
    return 0;
}
