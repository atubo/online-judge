// https://www.luogu.org/problemnew/show/P3159
// [CQOI2012]交换棋子

#include <bits/stdc++.h>
using namespace std;

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

const int DX[8] = {0, -1, -1, -1, 0, 1, 1, 1};
const int DY[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int INF = 1e6;

int N, M;
int src[21][21], dst[21][21], cap[21][21];

int upperId(int i, int j) {
    return i * M + j + 1;
}

int lowerId(int i, int j) {
    return i * M + j + 1 + N * M;
}

bool inRange(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
}

int main() {
    scanf("%d%d", &N, &M);
    int num_src = 0, num_dst = 0;
    char line[30];
    for (int i = 0; i < N; i++) {
        scanf("%s", line);
        for (int j = 0; j < M; j++) {
            src[i][j] = line[j] - '0';
            num_src += src[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        scanf("%s", line);
        for (int j = 0; j < M; j++) {
            dst[i][j] = line[j] - '0';
            num_dst += dst[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        scanf("%s", line);
        for (int j = 0; j < M; j++) {
            cap[i][j] = line[j] - '0';
        }
    }
    if (num_src != num_dst) {
        printf("-1\n");
        return 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (src[i][j] && dst[i][j]) {
                src[i][j] = dst[i][j] = 0;
                num_src--;
                num_dst--;
            }
        }
    }

    const int S = 0, T = 2*N*M + 1;
    MincostMaxflow flow(T+1, 11*N*M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int u1 = upperId(i, j);
            int u2 = lowerId(i, j);
            if (src[i][j]) {
                flow.addEdge(S, u1, 0, 1);
            }
            if (dst[i][j]) {
                flow.addEdge(u2, T, 0, 1);
            }
            int c = cap[i][j]/2;
            if ((src[i][j] || dst[i][j]) && (cap[i][j]&1)) c++;
            flow.addEdge(u1, u2, 1, c);
            for (int d = 0; d < 8; d++) {
                int i2 = i + DX[d];
                int j2 = j + DY[d];
                if (inRange(i2, j2)) {
                    int v = upperId(i2, j2);
                    flow.addEdge(u2, v, 0, INF);
                }
            }
        }
    }

    auto f = flow.mincostFlow(S, T);
    if (f.first < num_src) {
        printf("-1\n");
    } else {
        printf("%d\n", f.second - f.first);
    }

    return 0;
}
