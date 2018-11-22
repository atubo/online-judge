// https://www.luogu.org/problemnew/show/P2770
// 航空路线问题

#include <bits/stdc++.h>
using namespace std;

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

    void init() {
        EC = -1;
        memset(V, 0, N * sizeof(Edge*));
    }

    struct Edge {
        Edge *next, *op;
        int t;
        int64_t c, v;    // node, residual, cost
    };

    int N;
    Edge *ES;
    Edge **V;
private:
    int EC = -1;

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

const int MAXN = 102;
int N, V;
int src, dst;
int top[MAXN], bot[MAXN];

void build(const Graph &g, MincostMaxflow &flow, int last) {
    for (int u = 0; u <= last; u++) {
        if (u == 0 || u == last) {
            flow.addEdge(top[u], bot[u], 0, 2);
        } else {
            flow.addEdge(top[u], bot[u], -1, 1);
        }
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (v > last) continue;
            flow.addEdge(bot[u], top[v], 0, 1);
        }
    }
    flow.addEdge(src, top[0], 0, 2);
    flow.addEdge(bot[last], dst, 0, 2);
}

int solve(const Graph &g, MincostMaxflow &flow, int last) {
    flow.init();
    build(g, flow, last);
    auto ret = flow.mincostFlow(src, dst);
    if (ret.first < 2) return 0;
    return -ret.second + 2;
}

vector<int> trace(const MincostMaxflow &flow, int last) {
    using Edge = MincostMaxflow::Edge;

    vector<int> ret = {0};
    Edge *curr = flow.V[1];
    for (int i = 0; i < 2; i++) {
        for (Edge *k = curr; k; k = k->next) {
            if (k->c == 0) {
                int u = k->t;
                while (u != top[last]) {
                    ret.push_back(u);
                    u++;
                    for (Edge *e = flow.V[u]; e; e = e->next) {
                        if (e->c == 0) {
                            u = e->t;
                            break;
                        }
                    }
                }
                ret.push_back(top[last]);
                curr = k->next;
                break;
            }
        }
    }
    for (int i = 0; i < (int)ret.size(); i++) ret[i] /= 2;
    ret.pop_back();
    int pivot = 0;
    for (; pivot < (int)ret.size(); pivot++) {
        if (ret[pivot] == last) break;
    }
    reverse(ret.begin()+pivot+1, ret.end());
    ret.push_back(0);

    return ret;
}


int main() {
    scanf("%d%d", &N, &V);
    src = 2*N, dst = 2*N+1;
    for (int i = 0; i < N; i++) {
        top[i] = 2*i;
        bot[i] = top[i] + 1;
    }
    map<string, int> cityIds;
    vector<string> cityNames;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        cityNames.push_back(s);
        cityIds[s] = i;
    }

    bool conn = false;
    Graph g(N, 2*V);
    for (int i = 0; i < V; i++) {
        string c1, c2;
        cin >> c1 >> c2;
        int u = cityIds.at(c1);
        int v = cityIds.at(c2);
        if (u == v) continue;
        if (u > v) swap(u, v);
        g.addEdge(u, v);
        if (u == 0 && v == N-1) conn = true;
    }

    MincostMaxflow flow(2*N+2, N+V+2);
    int ans = solve(g, flow, N-1);
    if (ans == 0 && !conn) {
        printf("No Solution!\n");
        return 0;
    }
    if (ans == 0 && conn) {
        printf("2\n");
        printf("%s\n%s\n%s\n", cityNames[0].c_str(),
               cityNames[N-1].c_str(),
               cityNames[0].c_str());
        return 0;
    }
    vector<int> path = trace(flow, N-1);
    printf("%d\n", ans);

    for (int x: path) {
        printf("%s\n", cityNames[x].c_str());
    }

    return 0;
}
