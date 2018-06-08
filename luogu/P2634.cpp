// https://www.luogu.org/problemnew/show/P2634
// [国家集训队]聪聪可可

#include <bits/stdc++.h>
using namespace std;

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

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
    int **depth_;

    void alloc() {
        vis_ = new bool[n_]{};
        sz_ = new int[n_]{};
        maxi_ = new int[n_]{};
        depth_ = new int*[n_]{};
        for (int i = 0; i < n_; i++) {
            depth_[i] = new int[3]{};
        }
    }

    void dealloc() {
        delete[] vis_;
        delete[] sz_;
        delete[] maxi_;

        for (int i = 0; i < n_; i++) {
            delete[] depth_[i];
        }
        delete[] depth_;
    }

    void dfs(int u, int fa) {
        sz_[u] = 1;
        depth_[u][0] = 1;
        depth_[u][1] = depth_[u][2] = 0;
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            int w = g_.E[eidx].wt;
            if (!vis_[v] && v != fa) {
                dfs(v, u);
                for (int r = 0; r < 3; r++) {
                    depth_[u][(r+w)%3] += depth_[v][r];
                }
                sz_[u] += sz_[v];
            }
        }
    }

    int down(int x, int w) {
        return (x + 3 - w%3) % 3;
    }

    int merge(int u, int v, int w, int x, int y) {
        return depth_[v][down(x, w)] *
            (depth_[u][y] - depth_[v][down(y, w)]);
    }

    void cal(int u) {
        dfs(u, -1);
        ans[0]++;
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            int w = g_.E[eidx].wt;
            if (!vis_[v]) {
                ans[0] += depth_[v][down(0, w)];
                ans[1] += depth_[v][down(1, w)];
                ans[2] += depth_[v][down(2, w)];
                ans[0] += merge(u, v, w, 0, 0);
                ans[0] += merge(u, v, w, 1, 2);
                ans[0] += merge(u, v, w, 2, 1);
                ans[1] += merge(u, v, w, 0, 1);
                ans[1] += merge(u, v, w, 1, 0);
                ans[1] += merge(u, v, w, 2, 2);
                ans[2] += merge(u, v, w, 0, 2);
                ans[2] += merge(u, v, w, 2, 0);
                ans[2] += merge(u, v, w, 1, 1);
            }
        }
        //printf("u=%d ans=(%d %d %d)\n", u+1, ans[0], ans[1], ans[2]);
    }

public:
    int rt;
    int ans[3];

    TreePartition(int n): n_(n), g_(n, 2*(n-1)) {
        alloc();

        rt = -1;
        for (int i = 0; i < 3; i++) ans[i] = 0;
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
    scanf("%d", &N);
    TreePartition tp(N);
    for (int i = 0; i < N-1; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        x--; y--;
        tp.addEdge(x, y, z%3);
    }
    scanf("%d", &K);
    tp.getrt(0, -1, N);
    tp.solve(tp.rt);
    //printf("%d %d %d\n", tp.ans[0], tp.ans[1], tp.ans[2]);
    int tot = tp.ans[0] + tp.ans[1] + tp.ans[2];
    int g = gcd(tp.ans[0], tot);
    printf("%d/%d\n", tp.ans[0]/g, tot/g);
    return 0;
}
