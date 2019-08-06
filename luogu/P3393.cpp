// https://www.luogu.org/problem/P3393
// 逃离僵尸岛

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to, wt;
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
    void addEdge(int u, int v, int w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

const int MAXN = 100010;
int N, M, K, S;
int P, Q;
int dst[MAXN];
int64_t D[2*MAXN];
bool inq[2*MAXN];
bool occupied[MAXN];

void bfs(const Graph &g, const vector<int> &cities) {
    memset(dst, -1, sizeof(dst));
    queue<int> q;
    for (int c: cities) {
        dst[c] = 0;
        q.push(c);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dst[u] == S) continue;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            if (dst[v] == -1) {
                dst[v] = dst[u] + 1;
                q.push(v);
            }
        }
    }
}

int calc_wt(int u) {
    if (u == 0 || u == N-1) return 0;
    return dst[u] == -1 ? P : Q;
}

void build(const Graph &g0, Graph &g) {
    for (int u = 0; u < N; u++) {
        if (!occupied[u]) {
            int wt = calc_wt(u);
            g.addEdge(2*u, 2*u+1, wt);
        }
        for (int eidx = g0.head[u]; ~eidx; eidx = g0.E[eidx].next) {
            int v = g0.E[eidx].to;
            g.addEdge(2*u+1, 2*v, 0);
        }
    }
}

int64_t spfa(const Graph &g) {
    memset(D, -1, sizeof(D));
    queue<int> q;
    D[0] = 0;
    inq[0] = true;
    q.push(0);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;

        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;

            if (D[v] == -1 || D[v] > D[u] + w) {
                D[v] = D[u] + w;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
    return D[2*N-1];
}

int main() {
    scanf("%d%d%d%d", &N, &M, &K, &S);
    scanf("%d%d", &P, &Q);
    vector<int> cities;
    for (int i = 0; i < K; i++) {
        int c;
        scanf("%d", &c);
        c--;
        cities.push_back(c);
        occupied[c] = true;
    }
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        g.addEdge(a, b, 0);
        g.addEdge(b, a, 0);
    }
    bfs(g, cities);

    Graph g2(2*N, 2*N+2*M);
    build(g, g2);
    printf("%ld\n", spfa(g2));
    return 0;
}
