// https://www.luogu.org/problemnew/show/P4149
// [IOI2011]Race

#include <bits/stdc++.h>
using namespace std;
using Pii = pair<int, int>;

const int INF = 1e8;

int K;

class TreePartition {
private:
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

    const int n_;
    Graph g_;

    bool *vis_;
    int *sz_;
    int *maxi_;
    int *depth_;
    int64_t *dist_;
    int *curr_;

    void alloc() {
        vis_ = new bool[n_]{};
        sz_ = new int[n_]{};
        maxi_ = new int[n_]{};
        depth_ = new int[n_]{};
        dist_ = new int64_t[n_]{};
        curr_ = new int[K+1]{};
        for (int i = 1; i <= K; i++) curr_[i] = INF;
    }

    void dealloc() {
        delete[] vis_;
        delete[] sz_;
        delete[] maxi_;
        delete[] depth_;
        delete[] dist_;
        delete[] curr_;
    }

    void dfs(int u, int fa, int d, int64_t ds, vector<Pii>& path) {
        sz_[u] = 1;
        depth_[u] = d;
        dist_[u] = ds;
        if (ds <= K) {
            ans = min(ans, curr_[K-ds] + d);
            path.push_back(make_pair(ds, d));
        }
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            int w = g_.E[eidx].wt;
            if (!vis_[v] && v != fa) {
                dfs(v, u, d+1, ds+w, path);
                sz_[u] += sz_[v];
            }
        }
    }

    void merge(const vector<Pii> &tmp, vector<int> &recover) {
        for (const auto &p: tmp) {
            curr_[p.first] = min(curr_[p.first], p.second);
            recover.push_back(p.first);
        }
    }

    void cal(int u) {
        vector<int> recover;
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            int w = g_.E[eidx].wt;
            if (!vis_[v]) {
                vector<Pii> tmp;
                dfs(v, u, 1, w, tmp);
                merge(tmp, recover);
            }
        }

        for (int d: recover) {
            if (d > 0) curr_[d] = INF;
        }
    }

public:
    int rt;
    int ans = INF;

    TreePartition(int n): n_(n), g_(n, 2*(n-1)) {
        alloc();

        rt = -1;
    }

    ~TreePartition() {
        dealloc();
    }

    void addEdge(int u, int v, int w) {
        g_.addEdge(u, v, w);
        g_.addEdge(v, u, w);
    }

    void getrt(int x, int fa, int totalSize) {
        sz_[x] = 1;
        maxi_[x] = 0;
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            if (v != fa && !vis_[v]) {
                getrt(v, x, totalSize);
                sz_[x] += sz_[v];
                maxi_[x] = max(maxi_[x], sz_[v]);
            }
        }
        maxi_[x] = max(maxi_[x], totalSize - sz_[x]);
        if (rt == -1 || maxi_[x] < maxi_[rt]) rt = x;
    }

    void solve(int u) {
        vis_[u] = true;
        cal(u);
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            if (!vis_[v]) {
                rt = -1;
                getrt(v, -1, sz_[v]);
                solve(rt);
            }
        }
    }
};

int N;

int main() {
    scanf("%d%d", &N, &K);
    TreePartition tp(N);
    for (int i = 0; i < N-1; i++) {
        int  u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        tp.addEdge(u, v, w);
    }
    tp.getrt(0, -1, N);
    tp.solve(tp.rt);
    printf("%d\n", tp.ans < INF ? tp.ans : -1);
    return 0;
}
