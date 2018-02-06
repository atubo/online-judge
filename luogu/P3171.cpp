// https://www.luogu.org/problemnew/show/P3171
// [CQOI2015]网络吞吐量

#include <bits/stdc++.h>
using namespace std;

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
private:
    static const int MAXM = 202000;
    const int N;
    int *head, *curr;
    struct Edge {
        int to, next, cap;
    };
    Edge *E;
    int e;

public:
    Dinic(int N_): N(N_) {
        alloc();
        reset();
    }

    ~Dinic() {
        dealloc();
    }

    void reset() {
        e = 0;
        memset(head, -1, N * sizeof(int));
    }

    void addEdge(int x, int y, int w, int rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
        head[y] = e++;
    }

private:
    void alloc() {
        head = new int[N];
        curr = new int[N];
        E    = new Edge[MAXM];
        d    = new int[N];
        q    = new int[N];
    }

    void dealloc() {
        delete[] head;
        delete[] curr;
        delete[] E;
        delete[] d;
        delete[] q;
    }

    int *d;
    int *q;

    bool bfs(int s, int t) {
        memset(d, -1, N * sizeof(int));
        int front = 0, back = 0;
        q[back++] = t;

        d[t] = 0;
        while (front != back) {
            int u = q[front];
            front++;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (d[v] == -1 && E[i^1].cap) {
                    d[v] = d[u] + 1;
                    q[back++] = v;
                    if (v == s) return true;
                }
            }
        }
        return false;
    }

    int dfs(int x, int low, int t) {
        if (x == t || !low) return low;
        int ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == d[x] - 1) {
                int k = dfs(v, min(low-ret, E[i].cap), t);
                if (k > 0) {
                    E[i].cap -= k;
                    E[i^1].cap += k;
                    ret += k;
                }
            }
        }
        return ret;
    }

public:
    int dinic(int s, int t) {
        int ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < N; i++) {
                curr[i] = head[i];
            }
            int k = dfs(s, inf, t);
            if (k > 0) ans += k;
        }
        return ans;
    }
};

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
            if (p.second == t) break;
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

// Note graph node is 0-indexed
class Graph {
    static const int MAXM = 200010;
public:
    struct Edge {
        int next, to, wt;
    };

    Edge *E;

    vector<int> head;
    int eidx;
    int N;

    Graph(int N_):N(N_) {
        E = new Edge[MAXM]{};
        head.resize(N);
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int wt) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = wt;
        head[u] = eidx++;
    }
};

int innode(int i) {return i*2;}
int outnode(int i) {return i*2 + 1;}

const int MAXN = 510;
int N, M;
bool vis[MAXN];

void dfs(int u, Dinic &dinic, const Graph &g, const vector<int64_t> &dist) {
    vis[u] = true;
    if (u == N-1) return;
    for (int eidx = g.head[u]; eidx != -1; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        if (dist[u] - dist[v] == g.E[eidx].wt) {
            dinic.addEdge(outnode(u), innode(v), Dinic::inf);
            if (!vis[v]) {
                dfs(v, dinic, g, dist);
            }
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);

    Graph g(N);
    FastDijkstra dij(N);
    for (int i = 0; i < M; i++) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        a--; b--;
        dij.addEdge(a, b, d);
        dij.addEdge(b, a, d);
        g.addEdge(a, b, d);
        g.addEdge(b, a, d);
    }
    dij.solve(N-1, 0);
    vector<int64_t> dist = dij.getDist();

    Dinic dinic(2*N);
    dfs(0, dinic, g, dist);

    for (int i = 0; i < N; i++) {
        int c;
        scanf("%d", &c);
        if (i == 0 || i == N-1) {
            dinic.addEdge(innode(i), outnode(i), Dinic::inf);
        } else {
            dinic.addEdge(innode(i), outnode(i), c);
        }
    }

    printf("%d", dinic.dinic(innode(0), outnode(N-1)));

    return 0;
}
