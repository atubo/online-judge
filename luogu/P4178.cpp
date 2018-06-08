// https://www.luogu.org/problemnew/show/P4178
// Tree

#include <bits/stdc++.h>
using namespace std;

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

    void alloc() {
        vis_ = new bool[n_]{};
        sz_ = new int[n_]{};
        maxi_ = new int[n_]{};
    }

    void dealloc() {
        delete[] vis_;
        delete[] sz_;
        delete[] maxi_;
    }

    void getdist(int u, int fa, int d, vector<int> &dist) {
        sz_[u] = 1;
        dist.push_back(d);
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            int w = g_.E[eidx].wt;
            if (!vis_[v] && v != fa) {
                getdist(v, u, d+w, dist);
                sz_[u] += sz_[v];
            }
        }
    }

    int cal(int u, int w) {
        vector<int> dist;
        getdist(u, -1, w, dist);
        sort(dist.begin(), dist.end());
        const int len = dist.size();
        int l = 0, r = len-1, ret = 0;
        while (l < r) {
            if (dist[l] + dist[r] <= K) {
                ret += r - l;
                l++;
            } else {
                r--;
            }
        }
        return ret;
    }

public:
    int rt;
    int ans;

    TreePartition(int n): n_(n), g_(n, 2*(n-1)) {
        alloc();

        rt = -1;
        ans = 0;
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
        ans += cal(u, 0);
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            int w = g_.E[eidx].wt;
            if (!vis_[v]) {
                ans -= cal(v, w);
                rt = -1;
                getrt(v, -1, sz_[v]);
                solve(rt);
            }
        }
    }
};

int N;

int main() {
    scanf("%d", &N);
    TreePartition tp(N);
    for (int i = 0; i < N-1; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        x--; y--;
        tp.addEdge(x, y, z);
    }
    scanf("%d", &K);
    tp.getrt(0, -1, N);
    tp.solve(tp.rt);
    printf("%d\n", tp.ans);
    return 0;
}
