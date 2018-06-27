// https://www.luogu.org/problemnew/show/P1768
// 天路

#include <bits/stdc++.h>
using namespace std;


// Determine if there is any negative weight loop
// Nodes in graph are 0-indexed
// Node N is a virtual node that has 0 weight edge to all nodes
// But we don't have to explicitly add that node
class SpfaDfs {
public:
    struct Edge {
        int next, to;
        double wt;
    };

    SpfaDfs(int N_, int M): N(N_) {
        inq = new bool[N]{};
        dist = new double[N];
        head = new int[N];
        eTotal = 0;
        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
        E = new Edge[M]{};
    }

    ~SpfaDfs() {
        delete[] inq;
        delete[] dist;
        delete[] head;
        delete[] E;
    }

    void addEdge(int u, int v, double w) {
        E[eTotal].to = v;
        E[eTotal].next = head[u];
        E[eTotal].wt = w;
        head[u] = eTotal++;
    }

    bool check() {
        init();
        for (int i = 0; i < N; i++) {
            if (!dfs(i)) return false;
        }
        return true;
    }

private:
    int N;
    bool *inq;  // if node is in queue
    double *dist;

    int *head;
    int eTotal;
    Edge *E;

    void init() {
        memset(inq, 0, N*sizeof(bool));
        memset(dist, 0, N*sizeof(double));
    }

    bool dfs(int u) {
        if (inq[u]) return false;
        inq[u] = 1;
        for (int eidx = head[u]; eidx != -1; eidx = E[eidx].next) {
            int v = E[eidx].to;
            double w = E[eidx].wt;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!dfs(v)) return false;
            }
        }
        inq[u] = 0;
        return true;
    }
};

const int MAXM = 20010;

struct WeightedEdge {
    int x, y, v, p;
} WE[MAXM];

int N, M;

bool feasible(double r) {
    SpfaDfs spfa(N, M);
    for (int i = 0; i < M; i++) {
        spfa.addEdge(WE[i].x, WE[i].y, r*WE[i].p - WE[i].v);
    }
    if (!spfa.check()) return true;
    return false;
}

double solve() {
    if (!feasible(0)) {
        return -1;
    }
    double lo = 0, hi = 210;
    double mid;
    while (lo < hi - 0.0001) {
        mid = (lo + hi) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid;
    }
    return hi;
}

int main() {
    scanf("%d%d", &N, &M);
    vector<int> id;
    for (int i = 0; i < M; i++) {
        int a, b, v, p;
        scanf("%d%d%d%d", &a, &b, &v, &p);
        WE[i] = {a, b, v, p};
        id.push_back(a);
        id.push_back(b);
    }
    sort(id.begin(), id.end());
    id.erase(unique(id.begin(), id.end()), id.end());
    for (int i = 0; i < M; i++) {
        int a = lower_bound(id.begin(), id.end(), WE[i].x) - id.begin();
        int b = lower_bound(id.begin(), id.end(), WE[i].y) - id.begin();
        WE[i].x = a;
        WE[i].y = b;
    }
    N = id.size();

    double ans = solve();
    if (ans < 0) printf("-1");
    else printf("%.1f", ans);
    return 0;
}
