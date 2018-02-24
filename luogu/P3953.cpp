// https://www.luogu.org/problem/show?pid=3953
// 逛公园

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

    int64_t solve(int s, int t) {
        // use priority queue in which top element has the "smallest" priority
        priority_queue<PII, vector<PII>, greater<PII> > Q;
        Q.push (make_pair (0, s));
        dist[s] = 0;
        while (!Q.empty()){
            PII p = Q.top();
            //if (p.second == t) break;
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
        return dist[t];
    }

private:
    const int N;
    vector<vector<PII>> edges;
    vector<int64_t> dist;
    vector<int> dad;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;

class TarjanSCC {
    struct Edge {
        int from, to, nex;
        bool sign;  // bridge?
    };

public:
    class Graph {
    private:
        int N, M;
        vector<int> head;
        vector<Edge> edge;
        int edgenum;
    public:
        Graph(int N_): N(N_) {
            head.resize(N, -1);
            edgenum = 0;
        }

        void add(int u, int v) {
            Edge e = {u, v, head[u], false};
            edge.push_back(e);
            head[u] = edgenum++;
        }
        friend class TarjanSCC;
    };

public:
    Graph& g;
    const int N;
    int taj, top, Time;    // SCC index
    vector<int> belong; // node -> its component
    vector<bool> instack;
    vector<vector<int> > bcc;   // component -> all nodes in it
    vector<int> DFN;
    vector<int> low;
    vector<int> Stack;

    vector<vector<int> > ng;    // new graph
    vector<int> du;             // in-degree of the new graph

    TarjanSCC(Graph& g_):g(g_), N(g.N) {
        top = Time = 0;
        taj = 0;
        belong.resize(N, -1);
        instack.resize(N, false);
        DFN.resize(N, -1);
        low.resize(N, -1);
        Stack.resize(N, -1);
    }

    void dfs() {
        for (int i = 0; i < N; i++) {
            if (DFN[i] == -1) tarjan(i, i);
        }
    }

    void assign() {
        // set up new graph
        ng.resize(taj);
        du.resize(taj, 0);
        for (int i = 0; i < g.edgenum; i++) {
            int u = belong[g.edge[i].from], v = belong[g.edge[i].to];
            if (u != v) {
                ng[u].push_back(v);
                du[v]++;
            }
        }
    }

private:
    void tarjan(int u, int fa) {
        DFN[u] = low[u] = ++Time;
        Stack[top++] = u;
        instack[u] = true;

        for (int i = g.head[u]; ~i; i = g.edge[i].nex) {
            int v = g.edge[i].to;
            if (DFN[v] == -1) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (DFN[u] < low[v]) {
                    g.edge[i].sign = 1;   // it's bridge
                }
            } else if (instack[v]) low[u] = min(low[u], DFN[v]);
        }

        if (low[u] == DFN[u]) {
            int now;
            bcc.push_back(vector<int>());
            do {
                now = Stack[--top];
                instack[now] = false;
                belong[now] = taj;
                bcc[taj].push_back(now);
            } while (now != u);
            taj++;
        }
    }
};

const int MAXM = 200010;
const int MAXN = 100010;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to, wt;
    };

    vector<int> head;
    int eidx;
    int N;
    Edge *E;

    Graph(int N_):N(N_) {
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
        E = new Edge[MAXM];
    }

    ~Graph() {
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

int N, M, K, P;
int S, T;

struct Edge {
    int a, b, c;
} edge[MAXM];

int cnt[MAXN][51];
bool vis[MAXN][51];
int topoorder[MAXN], in[MAXN];

struct Item {
    int d, k, id;
    bool operator > (const Item &other) const {
        if (k > other.k) return true;
        if (k < other.k) return false;
        if (d > other.d) return true;
        if (d < other.d) return false;
        return topoorder[id] > topoorder[other.id];
    }
};


int add(int a, int b) {
    return (a + b) % P;
}

void init() {
    memset(cnt, 0, sizeof(cnt));
    memset(vis, 0, sizeof(vis));
    memset(topoorder, -1, sizeof(topoorder));
    memset(in, 0, sizeof(in));
}

void toposort(const Graph &g) {
    for (int u = 0; u < g.N; u++) {
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            if (w == 0) in[v]++;
        }
    }
    int curr = 0;
    queue<int> q;
    for (int u = 0; u < g.N; u++) {
        if (in[u] == 0) q.push(u);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoorder[u] = curr++;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            if (w == 0) {
                in[v]--;
                if (in[v] == 0) q.push(v);
            }
        }
    }
}

void solve(const Graph &g, const FastDijkstra &dij) {
    priority_queue<Item, vector<Item>, greater<Item>> pq;
    if (cnt[S][0] != -1) cnt[S][0] = 1;
    pq.push({0, 0, S});
    while (!pq.empty()) {
        Item item = pq.top();
        pq.pop();
        int d = item.d, k = item.k, u = item.id;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            int dv = d + w;
            int kv = dv - dij.getDist()[v];
            if (kv > K) continue;
            if (cnt[u][k] >= 0 && cnt[v][kv] >= 0) {
                cnt[v][kv] = add(cnt[v][kv], cnt[u][k]);
            } else {
                cnt[v][kv] = -1;
            }
#if 0
            printf("u=%d d=%d k=%d dv=%lld w=%d cntu=%d v=%d kv=%d cntv=%d\n",
                   u, d, k, dij.getDist()[v], w, cnt[u][k], v, kv, cnt[v][kv]);
#endif
            if (!vis[v][kv]) {
                pq.push({dv, kv, v});
                vis[v][kv] = true;
            }
        }
    }
    int ret = 0;
    for (int k = 0; k <= K; k++) {
        if (cnt[T][k] == -1) {
            ret = -1;
            break;
        }
        ret = add(ret, cnt[T][k]);
    }
    printf("%d\n", ret);
}

int main() {
    int nt;
    scanf("%d", &nt);
    while (nt--) {
        scanf("%d%d%d%d", &N, &M, &K, &P);
        init();
        for (int i = 0; i < M; i++) {
            scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].c);
            edge[i].a--;
            edge[i].b--;
        }

        TarjanSCC::Graph g0(N);
        for (int i = 0; i < M; i++) {
            if (edge[i].c == 0) {
                g0.add(edge[i].a, edge[i].b);
            }
        }
        TarjanSCC tarjan(g0);
        tarjan.dfs();

        for (int i = 0; i < tarjan.taj; i++) {
            if (tarjan.bcc[i].size() > 1) {
                cnt[i][0] = -1;
            }
        }
        Graph g(tarjan.taj);
        FastDijkstra dij(tarjan.taj);
        for (int i = 0; i < M; i++) {
            int a = edge[i].a, b = edge[i].b, c= edge[i].c;
            int u = tarjan.belong[a];
            int v = tarjan.belong[b];
            //printf("new: %d old: %d\n", u, a+1);
            //printf("new: %d old: %d\n", v, b+1);
            if (u != v) {
                g.addEdge(u, v, c);
                dij.addEdge(u, v, c);
            }
        }
        S = tarjan.belong[0], T = tarjan.belong[N-1];
        dij.solve(S, T);

        toposort(g);
        solve(g, dij);
    }
    return 0;
}
