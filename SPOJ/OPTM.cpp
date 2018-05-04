// http://www.spoj.com/problems/OPTM/
// OPTM - Optimal Marks

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
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

        E = new Edge[2*M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;

        E[eidx].to = u;
        E[eidx].next = head[v];
        head[v] = eidx++;
    }
};

class MincostMaxflow {
    // NOTE
    // 1. set up the following values
    // 2. nodes are 0-indexed
    // 3. MAXM must be twice the number of edges you added
    // 4. call init() before you use it again
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
        Edge e1 = {V[a], 0, b, capacity, cost, true}, e2 = {V[b], 0, a, 0, -cost, false};
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

//private:
    int N;
    struct Edge {
        Edge *next, *op;
        int t, c, v;    // node, residual, cost
        bool orig;
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

const int MAXN = 510;
int T;
int N, M;
int K;
int mark[MAXN];

int id(int u) {
    return u+1;
}

void dfs(const MincostMaxflow &mcf, vector<bool> &visited, int u, int d) {
    visited[u] = true;
    mark[u-1] |= (1 << d);
    for (MincostMaxflow::Edge *e = mcf.V[u]; e; e = e->next) {
        if (e->c > 0 && e->orig) {
            int v = e->t;
            if (!visited[v]) {
                dfs(mcf, visited, v, d);
            }
        }
    }
}


void solve(const Graph &g) {
    vector<pair<int, int>> fixed;
    vector<bool> isFixed(N, false);
    for (int i = 0; i < N; i++) {
        if (mark[i] >= 0) {
            fixed.push_back({i, mark[i]});
            isFixed[i] = true;
        } else {
            mark[i] = 0;
        }
    }
    for (int d = 0; d < 31; d++) {
        bool doit = false;
        const int s = 0, t = N+1;
        MincostMaxflow mcf(t+1, 2*(N+M));
        for (int u = 0; u < N; u++) {
            if (!isFixed[u]) {
                mcf.addEdge(s, id(u), 0, 1);
                mcf.addEdge(id(u), t, 1, 1);
            } else {
                if ((mark[u]>>d) & 1) {
                    doit = true;
                    mcf.addEdge(s, id(u), 0, MincostMaxflow::INF);
                } else {
                    mcf.addEdge(id(u), t, 0, MincostMaxflow::INF);
                }
            }

            for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
                int v = g.E[eidx].to;
                mcf.addEdge(id(u), id(v), 0, 1);
            }
        }
        if (!doit) continue;
        mcf.mincostFlow(s, t);
        vector<bool> visited(N, false);
        dfs(mcf, visited, s, d);
    }

    for (int i = 0; i < N; i++) {
        printf("%d\n", mark[i]);
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        memset(mark, -1, sizeof(mark));
        scanf("%d%d", &N, &M);
        Graph g(N, M);
        for (int i = 0; i < M; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            u--; v--;
            g.addEdge(u, v);
        }
        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            int u, p;
            scanf("%d%d", &u, &p);
            u--;
            mark[u] = p;
        }

        solve(g);
    }

    return 0;
}
