// https://www.luogu.org/problem/P4568
// [JLOI2011]飞行路线

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

const int MAXN = 110010;
int N, M, K;
int S, T;
int D[MAXN];

void dijkstra(const Graph &g) {
    using PII = pair<int, int>;
    memset(D, 0x3F, sizeof(D));
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push(make_pair(0, S));
    D[S] = 0;
    while (!q.empty()) {
        PII p = q.top();
        q.pop();

        int u = p.second;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            if (D[v] > D[u] + w) {
                D[v] = D[u] + w;
                q.push(make_pair(D[v], v));
            }
        }
    }
    int ans = D[T];
    for (int i = 1; i <= K; i++) {
        ans = min(ans, D[i*N+T]);
    }
    printf("%d\n", ans);
}


int main() {
    scanf("%d%d%d", &N, &M, &K);
    scanf("%d%d", &S, &T);
    Graph g((K+1)*N, (4*K+2)*M);
    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        for (int j = 0; j <= K; j++) {
            g.addEdge(j*N+a, j*N+b, c);
            g.addEdge(j*N+b, j*N+a, c);
        }
        for (int j = 0; j < K; j++) {
            g.addEdge(j*N+a, (j+1)*N+b, 0);
            g.addEdge(j*N+b, (j+1)*N+a, 0);
        }
    }
    dijkstra(g);
    return 0;
}
