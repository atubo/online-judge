// https://www.luogu.org/problemnew/show/P4237
// 荒芜的海洋

#include <bits/stdc++.h>
using namespace std;

class FastDijkstra {
public:
    static const int64_t INF;

    typedef pair<int64_t,int> PII;  // pair = (dist, vertex)

    FastDijkstra(int N_): N(N_), edges(N), dist(N, INF), dad(N, -1) {}

    void addEdge(int u, int v, int64_t wt) {
        edges[u].push_back(make_pair(wt, v));
    }

    const vector<int64_t>& getDist() const {
        return dist;
    }

    const vector<int>& getDad() const {
        return dad;
    }

    void solve(int s) {
        // use priority queue in which top element has the "smallest" priority
        priority_queue<PII, vector<PII>, greater<PII> > Q;
        Q.push (make_pair (0, s));
        dist[s] = 0;
        while (!Q.empty()){
            PII p = Q.top();
            // break here if we want to stop when we find a target node
            Q.pop();

            int here = p.second;
            for (vector<PII>::const_iterator it=edges[here].begin();
                 it!=edges[here].end(); it++){
                if (dist[here] + it->first < dist[it->second]){
                    dist[it->second] = dist[here] + it->first;
                    dad[it->second] = here;
                    Q.push (make_pair (dist[it->second], it->second));
                }
            }
        }
    }

    void reset() {
        dist.assign(N, INF);
        dad.assign(N, -1);
    }

private:
    const int N;
    vector<vector<PII>> edges;
    vector<int64_t> dist;
    vector<int> dad;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;

class MincostMaxflow {
    // NOTE
    // 1. nodes are 0-indexed
    // 2. call init() before you use it again
public:
    const static int INF = 1e9;

    struct Edge {
        int to, next;
        int c, v;   // residual, cost
    };

    MincostMaxflow(int N_, int M):N(N_), Q(N_) {
        V = new int[N]{};
        ES = new Edge[2*M]{};
        sp = new int[N]{};
        prev = new int[N]{};
        path = new int[N]{};
        instack_ = new bool[N]{};
        init();
    }

    ~MincostMaxflow() {
        delete[] V;
        delete[] ES;
        delete[] sp;
        delete[] prev;
        delete[] path;
        delete[] instack_;
    }

    void addEdge(int a, int b, int cost, int capacity) {
#if 0
        Edge e1 = {V[a], 0, b, capacity, cost}, e2 = {V[b], 0, a, 0, -cost};
        ES[++EC] = e1; V[a] = &ES[EC];
        ES[++EC] = e2; V[b] = &ES[EC];
        V[a]->op = V[b]; V[b]->op = V[a];
#endif
        ES[++EC] = {b, V[a], capacity, cost};
        ES[++EC] = {a, V[b], 0, -cost};
        V[a] = EC - 1;
        V[b] = EC;
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
    pair<int, int> mincostFlow(int s, int t) {
        FlowCost fc{};
        while (SPFA(s, t)) {
            fc += augment(t);
        }
        return make_pair(fc.flow, fc.cost);
    }

private:
    int N;
#if 0
    struct Edge {
        Edge *next, *op;
        int t;
        int64_t c, v;    // node, residual, cost
    };
#endif

    Edge *ES;
    int *V;
    int EC = -1;

    void init() {
        EC = -1;
        //memset(V, 0, N * sizeof(Edge*));
        for (int i = 0; i < N; i++) V[i] = -1;
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


    int *sp;
    int *prev;
    int *path;
    bool *instack_;

    bool SPFA(int s, int t) {
#if 0
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
#endif
        memset(instack_, 0, N*sizeof(bool));
        for (int u = 0; u < N; u++) sp[u] = INF;
        queue<int> q;
        q.push(s);
        sp[s] = 0; prev[s] = -1;
        instack_[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            instack_[u] = false;
            for (int eidx = V[u]; ~eidx; eidx = ES[eidx].next) {
                const Edge &e = ES[eidx];
                int v = e.to;
                if (e.c > 0 && sp[u] + e.v < sp[v]) {
                    sp[v] = sp[u] + e.v;
                    prev[v] = u;
                    path[v] = eidx;
                    if (!instack_[v]) {
                        instack_[v] = true;
                        q.push(v);
                    }
                }
            }

#if 0
            for (Edge *k = V[u]; k; k = k->next) {
                int v = k->t;
                if (k->c > 0 && sp[u] + k->v < sp[v]) {
                    sp[v] = sp[u] + k->v;
                    prev[v] = u;
                    path[v] = k;
                    if (!instack_[v]) {
                        instack_[v] = true;
                        if (!q.empty() && sp[v] < sp[q.front()]) {
                            q.push_front(v);
                        } else {
                            q.push_back(v);
                        }
                    }
                }
            }
#endif
        }
        return sp[t] != INF;
    }

    FlowCost augment(int t) {
        int i;
        int low = INF, cost = 0;
        for (i = t; prev[i] != -1; i = prev[i]) {
            const Edge &e = ES[path[i]];
            if (e.c < low) low = e.c;
        }
        for (i = t; prev[i] != -1; i = prev[i]) {
            Edge &e = ES[path[i]];
            Edge &e_op = ES[path[i]^1];
            e.c -= low; e_op.c += low;
            cost += e.v * low;
        }
        return FlowCost{low, cost};
    }
};

const int MAXN = 1010, MAXM = 15010;
const int MAXA = 310;
int N, M, A, B;
int beast[MAXN];
int64_t dist[2*MAXA][2*MAXA];

struct Item {
    int price, pos;
};

Item mercenary[MAXA], bounty[MAXA];

int upperId(int i) {return 2*i;}
int lowerId(int i) {return 2*i+1;}

int nodeIdx(int u, const vector<int> &nodes) {
    return lower_bound(nodes.begin(), nodes.end(), u) - nodes.begin();
}

int main() {
    scanf("%d%d%d%d", &N, &M, &A, &B);
    for (int i = 0; i < N; i++) {
        scanf("%d", &beast[i]);
    }

    FastDijkstra dijkstra(2*N);
    for (int i = 0; i < N; i++) {
        dijkstra.addEdge(upperId(i), lowerId(i), beast[i]);
    }
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        dijkstra.addEdge(lowerId(u), upperId(v), w);
        dijkstra.addEdge(lowerId(v), upperId(u), w);
    }

    vector<int> nodes;
    for (int i = 0; i < A; i++) {
        scanf("%d%d", &mercenary[i].price, &mercenary[i].pos);
        mercenary[i].pos--;
        nodes.push_back(mercenary[i].pos);
    }
    for (int i = 0; i < B; i++) {
        scanf("%d%d", &bounty[i].price, &bounty[i].pos);
        bounty[i].pos--;
        nodes.push_back(bounty[i].pos);
    }
    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    for (int i = 0; i < (int)nodes.size(); i++) {
        dijkstra.reset();
        dijkstra.solve(upperId(nodes[i]));
        for (int j = 0; j < (int)nodes.size(); j++) {
            dist[i][j] = dijkstra.getDist()[lowerId(nodes[j])];
        }
    }

    const int src = 0, dst = A+B+1;
    MincostMaxflow flow(dst+1, A+B+A*B);

    for (int i = 0; i < A; i++) {
        int cost = mercenary[i].price;
        flow.addEdge(src, i+1, 0, 1);
        int m_node = nodeIdx(mercenary[i].pos, nodes);
        for (int j = 0; j < B; j++) {
            int b_node = nodeIdx(bounty[j].pos, nodes);
            if (dist[m_node][b_node] < FastDijkstra::INF) {
                flow.addEdge(i+1, j+A+1, dist[m_node][b_node]+cost, 1);
            }
        }
    }

    int tot = 0;
    for (int i = 0; i < B; i++) {
        flow.addEdge(i+A+1, dst, 0, 1);
        tot += bounty[i].price;
    }

    auto f = flow.mincostFlow(src, dst);
    if (f.first == B) {
        printf("Yes\n%d\n", tot-f.second);
    } else {
        printf("No\n%d\n", f.first);
    }

    return 0;
}
