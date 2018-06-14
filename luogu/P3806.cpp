// https://www.luogu.org/problemnew/show/P3806
// 【模板】点分治1

#include <bits/stdc++.h>
using namespace std;

const int MAXK = 10000010;

vector<int> K;
int M;

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
    int64_t *dist_;
    bool *rootFeasible_;

    void alloc() {
        vis_ = new bool[n_]{};
        sz_ = new int[n_]{};
        maxi_ = new int[n_]{};
        dist_ = new int64_t[n_]{};
        rootFeasible_ = new bool[MAXK]{};
        rootFeasible_[0] = true;
        ans = new bool[M]{};
    }

    void dealloc() {
        delete[] vis_;
        delete[] sz_;
        delete[] maxi_;
        delete[] dist_;
        delete[] rootFeasible_;
        delete[] ans;
    }

    void dfs(int u, int fa, int64_t ds, vector<int>& reachedDist) {
        sz_[u] = 1;
        dist_[u] = ds;
        for (int i = 0; i < M; i++) {
            if (ds <= K[i]) {
                ans[i] |= rootFeasible_[K[i]-ds];
            }
        }
        reachedDist.push_back(ds);

        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            int w = g_.E[eidx].wt;
            if (!vis_[v] && v != fa) {
                dfs(v, u, ds+w, reachedDist);
                sz_[u] += sz_[v];
            }
        }
    }

    void merge(const vector<int> &tmp, vector<int> &recover) {
        for (int d: tmp) {
            rootFeasible_[d] = true;
            recover.push_back(d);
        }
    }

    void cal(int u) {
        vector<int> recover;
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            int w = g_.E[eidx].wt;
            if (!vis_[v]) {
                vector<int> tmp;
                dfs(v, u, w, tmp);
                merge(tmp, recover);
            }
        }

        for (int d: recover) {
            if (d > 0) rootFeasible_[d] = false;
        }
    }

public:
    int rt;
    bool *ans;

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
    scanf("%d%d", &N, &M);
    TreePartition tp(N);
    for (int i = 0; i < N-1; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        tp.addEdge(a-1, b-1, c);
    }

    K.resize(M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &K[i]);
    }
    tp.getrt(0, -1, N);
    tp.solve(tp.rt);
    for (int i = 0; i < M; i++) {
        printf(tp.ans[i] ? "AYE\n" : "NAY\n");
    }
    return 0;
}
