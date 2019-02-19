// https://www.luogu.org/problemnew/show/P1875
// 佳佳的魔法药水

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

const int MAXN = 1024;
int N, M;
int A[MAXN];
int dist[MAXN], inq[MAXN];
int cnt[MAXN];

struct Recipe {
    int a, b, c;
} R[MAXN*MAXN/2];

struct Data {
    int d, id;
    bool operator < (const Data &other) const {
        if (d != other.d) return d < other.d;
        return id < other.id;
    }
} data[MAXN];

struct Ing {
    int a, b;
};

void spfa(const Graph &g) {
    queue<int> q;
    for (int i = 0; i < N; i++) {
        dist[i] = A[i];
        q.push(i);
        inq[i] = true;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            int w = g.E[eidx].wt;
            if (dist[v] > dist[u] + dist[w]) {
                dist[v] = dist[u] + dist[w];
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }
}

void path(const Graph &g, const vector<vector<Ing>> &ing) {
    for (int i = 0; i < N; i++) {
        data[i] = {dist[i], i};
    }
    sort(data, data+N);
    for (int i = 0; i < N; i++) {
        int d = data[i].d;
        int id = data[i].id;
        cnt[id] = (d == A[id]);
        for (auto ig: ing[id]) {
            int a = ig.a;
            int b = ig.b;
            if (dist[a] + dist[b] == d) {
                cnt[id] += cnt[a] * cnt[b];
            }
        }
    }
}

int main() {
    memset(dist, 0x7F, sizeof(dist));
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    int a, b, c;
    while (scanf("%d%d%d", &a, &b, &c) == 3) {
        R[M++] = {a, b, c};
    }
    vector<vector<Ing>> ing(N);
    Graph g(N, 2*M);
    for (int i = 0; i < M; i++) {
        a = R[i].a;
        b = R[i].b;
        c = R[i].c;
        g.addEdge(a, c, b);
        g.addEdge(b, c, a);
        ing[c].push_back({a, b});
    }
    spfa(g);
    path(g, ing);
    printf("%d %d", dist[0], cnt[0]);
    return 0;
}
