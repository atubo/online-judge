// https://www.luogu.org/problemnew/show/P3296
// [SDOI2013]刺客信条

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

        E = new Edge[M]{};
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        head[u] = eidx++;
    }
};

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

private:
    int N;
    struct Edge {
        Edge *next, *op;
        int t;
        int64_t c, v;    // node, residual, cost
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

const int MAXN = 710;
int N;
int S[MAXN], T[MAXN];
bool iso[MAXN][MAXN];
int DMAX;
map<int64_t, int> mp;

void dfs(const Graph &g, int u, int fa, int d, int &dmax) {
    dmax = max(d, dmax);
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (v != fa) dfs(g, v, u, d+1, dmax);
    }
}

int isomorphic(const Graph &g, int u, int fu, int v, int fv) {
    int64_t key = (u+1)*702*702*702 + (fu+1)*702*702 +
        (v+1)*702 + (fv+1);
    if (mp.find(key) != mp.end()) return mp[key];
    int &ret = mp[key];
    vector<int> cu, cv;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int c = g.E[eidx].to;
        if (c != fu) cu.push_back(c);
    }
    for (int eidx = g.head[v]; ~eidx; eidx = g.E[eidx].next) {
        int c = g.E[eidx].to;
        if (c != fv) cv.push_back(c);
    }
    if (cu.size() != cv.size()) return ret = -1;
    if (cu.empty()) return ret = (S[u] != T[v]);

    int sz = cu.size();
    MincostMaxflow flow(2*sz+2, sz*sz+2*sz);
    
    const int src = 2*sz, dst = 2*sz+1;
    for (int i = 0; i < sz; i++) {
        flow.addEdge(src, i, 0, 1);
        flow.addEdge(sz+i, dst, 0, 1);
        for (int j = 0; j < sz; j++) {
            int cost = isomorphic(g, cu[i], u, cv[j], v);
            if (cost >= 0) {
                flow.addEdge(i, sz+j, cost, 1);
            }
        }
    }

    auto mf = flow.mincostFlow(src, dst);
    if (mf.first == sz) return ret = (mf.second + (S[u] != T[v]));
    return ret = -1;
}

int main() {
    scanf("%d", &N);
    Graph g(N, 2*(N-1));
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
        g.addEdge(v, u);
    }

    dfs(g, 0, -1, 0, DMAX);
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &T[i]);
    }

    int ans = N;
    for (int i = 0; i < N; i++) {
        int dmax = 0;
        dfs(g, i, -1, 0, dmax);
        if (dmax != DMAX) continue;
        int t = isomorphic(g, 0, -1, i, -1);
        if (t >= 0) ans = min(ans, t);
    }
    printf("%d\n", ans);
    return 0;
}
