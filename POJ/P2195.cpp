// http://poj.org/problem?id=2195
// Going Home

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
using namespace std;


namespace MincostMaxflowNS {
    // need to set up these values
    // note it is required S < other nodes < T (see code in SPFA)
    // note MAXM must be twice the number of edges you added
    const int INF = 1000000;
    const int MAXM = 25000, MAXN = 300;
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

typedef pair<int, int> PII;
const int NMAX = 110;
PII H[NMAX], men[NMAX];
char line[NMAX];

int dist(int i, int j) {
    return abs(men[i].first - H[j].first) + abs(men[i].second - H[j].second);
}

int main() {
    using namespace MincostMaxflowNS;
    int N, M;
    while (true) {
        scanf("%d%d", &N, &M);
        if (N == 0 && M == 0) break;
        int nh = 0, nm = 0;
        for (int i = 0; i < N; i++) {
            scanf("%s", line);
            for (int j = 0; j < M; j++) {
                if (line[j] == 'H') {
                    H[nh++] = make_pair(i, j);
                } else if (line[j] == 'm') {
                    men[nm++] = make_pair(i, j);
                }
            }
        }

        S = 0;
        T = 2 * nm + 1;
        init();

        for (int i = 1; i <= nm; i++) {
            addEdge(S, i, 0, 1);
        }
        for (int i = nm + 1; i <= 2*nm; i++) {
            addEdge(i, T, 0, 1);
        }

        for (int i = 0; i < nm; i++) {
            for (int j = 0; j < nm; j++) {
                addEdge(i+1, nm+j+1, dist(i, j), 1);
            }
        }

        printf("%d\n", mincostFlow());
    }

    return 0;
}
