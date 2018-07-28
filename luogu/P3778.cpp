// https://www.luogu.org/problemnew/show/P3778
// [APIO2017]商旅

#include <bits/stdc++.h>
using namespace std;

const int MAXK = 1010, MAXM = 9910, MAXN = 110;
int N, M, K;

// Determine if there is any negative weight loop
// Nodes in graph are 0-indexed
// Node N is a virtual node that has 0 weight edge to all nodes
// But we don't have to explicitly add that node
class SpfaDfs {
public:
    struct Edge {
        int next, to;
        int64_t wt;
    };

    SpfaDfs(int N_, int M_): N(N_) {
        inq = new bool[N]{};
        dist = new int64_t[N];
        vis_ = new bool[N]{};
        head = new int[N];
        eTotal = 0;
        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }
        E = new Edge[M_]{};
    }

    ~SpfaDfs() {
        delete[] inq;
        delete[] dist;
        delete[] vis_;
        delete[] head;
        delete[] E;
    }

    void addEdge(int u, int v, int64_t w) {
        E[eTotal].to = v;
        E[eTotal].next = head[u];
        E[eTotal].wt = w;
        head[u] = eTotal++;
    }

    bool check() {
        init();
        for (int i = 0; i < N; i++) {
            memset(vis_, 0, N*sizeof(bool));
            if (!dfs(i, -1)) return false;
        }
        return true;
    }

private:
    int N;
    bool *inq;  // if node is in queue
    int64_t *dist;
    bool *vis_;

    int *head;
public:
    int eTotal;
    Edge *E;

    void init() {
        memset(inq, 0, N*sizeof(bool));
        memset(dist, 0, N*sizeof(int64_t));
    }

    bool dfs(int u, int fa) {
        if (inq[u]) return false;
        inq[u] = 1;
        vis_[u] = true;
        for (int eidx = head[u]; eidx != -1; eidx = E[eidx].next) {
            int v = E[eidx].to;
            int64_t w = E[eidx].wt;
            if (dist[v] == dist[u] + w && inq[v]) return false;
            if (dist[v] > dist[u] + w ||
                (dist[v] == dist[u] + w && !vis_[v])) {
                dist[v] = dist[u] + w;
                if (!dfs(v, u)) return false;
            }
        }
        inq[u] = 0;
        return true;
    }
};

class FloydWarshall {
public:
    FloydWarshall(const vector<vector<int64_t> >& graph)
        :dist_(graph)
    {
        int V = dist_.size();

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist_[i][k] + dist_[k][j] < dist_[i][j]) {
                        dist_[i][j] = dist_[i][k] + dist_[k][j];
                    }
                }
            }
        }
    }

    vector<vector<int64_t> > dist_;
};

struct Route {
    int64_t profit, tm, id;
}routes[MAXN*(MAXN-1)];
int route_cnt;

int price[MAXN][MAXK][2];
int max_profit[MAXN][MAXN];

int calcMaxProfit(int u, int v) {
    int res = 0;
    for (int i = 0; i < K; i++) {
        if (price[v][i][1] == -1 || price[u][i][0] == -1) continue;
        res = max(res, price[v][i][1] - price[u][i][0]);
    }
    return res;
}

int solve(const vector<vector<int64_t>>& g) {
    FloydWarshall floyd(g);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (floyd.dist_[i][j] < 1e13) {
                max_profit[i][j] = calcMaxProfit(i, j);
            }
        }
    }


    SpfaDfs spfa(N, N*(N-1));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            if (floyd.dist_[i][j] < 1e13) {
                spfa.addEdge(i, j, -max_profit[i][j]);
                routes[route_cnt++] = {max_profit[i][j], floyd.dist_[i][j],
                    spfa.eTotal-1};
            }
        }
    }

    if (spfa.check()) return 0;
    int lo = 0, hi = 1e9;
    while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        for (int i = 0; i < route_cnt; i++) {
            spfa.E[routes[i].id].wt = 1LL * mid * routes[i].tm - routes[i].profit;
        }
        if (spfa.check()) hi = mid;
        else lo = mid;
    }
    return lo;
}

int main() {
    scanf("%d%d%d", &N, &M, &K);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            scanf("%d%d", &price[i][j][0], &price[i][j][1]);
        }
    }
    vector<vector<int64_t>> g(N);
    for (int i = 0; i < N; i++) g[i].resize(N, 1e13);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u--; v--;
        g[u][v] = w;
    }

    int ans = solve(g);
    printf("%d", ans);
    return 0;
}
