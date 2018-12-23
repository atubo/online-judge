// https://www.luogu.org/problemnew/show/P2502
// [HAOI2006]旅行

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

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

int N, M;
int S, T;
bool vis[512];
int pans = 50000, qans = 1;

bool dfs(const Graph &g, int u, int lo, int hi) {
    if (u == T) return true;
    vis[u] = true;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (w < lo || w > hi) continue;
        if (!vis[v]) {
            if (dfs(g, v, lo, hi)) return true;
        }
    }
    return false;
}

void tally(int p, int q) {
    int g = gcd(p, q);
    p /= g;
    q /= g;
    if (p * qans < q * pans) {
        pans = p;
        qans = q;
    }
}

void solve(const Graph &g, const vector<int> &v) {
    if (!dfs(g, S, v[0], v.back())) {
        printf("IMPOSSIBLE");
        return;
    }
    int p = 0, q = v.size()-1;
    while (true) {
        int lo = p-1, hi = v.size()-1;
        while (lo < hi-1) {
            int mid = (lo + hi) / 2;
            memset(vis, 0, sizeof(vis));
            if (dfs(g, S, v[p], v[mid])) hi = mid;
            else lo = mid;
        }
        q = hi;
        lo = p, hi = q+1;
        while (lo < hi-1) {
            int mid = (lo + hi) / 2;
            memset(vis, 0, sizeof(vis));
            if (dfs(g, S, v[mid], v[q])) lo = mid;
            else hi = mid;
        }
        p = lo;
        tally(v[q], v[p]);

        p++;
        memset(vis, 0, sizeof(vis));
        if (p >= (int)v.size() || !dfs(g, S, v[p], v.back())) break;
    }
    if (qans == 1) {
        printf("%d", pans);
    } else {
        printf("%d/%d", pans, qans);
    }
}

int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, 2*M);
    vector<int> vvec;
    for (int i = 0; i < M; i++) {
        int x, y, v;
        scanf("%d%d%d", &x, &y, &v);
        x--; y--;
        g.addEdge(x, y, v);
        g.addEdge(y, x, v);
        vvec.push_back(v);
    }
    scanf("%d%d", &S, &T);
    S--; T--;

    sort(vvec.begin(), vvec.end());
    vvec.erase(unique(vvec.begin(), vvec.end()), vvec.end());
    solve(g, vvec);

    return 0;
}
