// https://www.luogu.org/problemnew/show/P3469
// [POI2008]BLO-Blockade

#include <bits/stdc++.h>
using namespace std;

class TarjanArticulationPoint {
public:
    // Note graph node is 0-indexed
    class Graph {
    public:
        struct Edge {
            int next, to;
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
        void addEdge(int u, int v) {
            E[eidx].to = v;
            E[eidx].next = head[u];
            head[u] = eidx++;
        }
    };

    // m is the number of undirected edges
    TarjanArticulationPoint(int n, int m): n_(n), g_(n, 2*m) {
        alloc();
    }

    ~TarjanArticulationPoint() {
        dealloc();
    }

    void addEdge(int u, int v) {
        g_.addEdge(u, v);
        g_.addEdge(v, u);
    }

    void solve() {
        dfs(0);
    }

    bool *art_; // whether a node is articulation point
    int64_t *ans_;
private:
    const int n_;
    Graph g_;

    int *dfn_;
    int *low_;
    bool *vis_;
    int *sz_;
    int tmpdfn_ = 0;
    int root_ = 0;
    vector<int> rc_;

    void alloc() {
        dfn_ = new int[n_]{};
        low_ = new int[n_]{};
        vis_ = new bool[n_]{};
        art_ = new bool[n_]{};
        sz_  = new int[n_]{};
        ans_ = new int64_t[n_]{};
    }

    void dealloc() {
        delete[] dfn_;
        delete[] low_;
        delete[] vis_;
        delete[] art_;
        delete[] sz_;
        delete[] ans_;
    }

    void dfs(int u) {
        sz_[u] = 1;
        ans_[u] = 2*(n_-1);
        dfn_[u] = low_[u] = tmpdfn_++;
        vis_[u] = true;
        int son = 0;
        int des = 0;
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            if (!vis_[v]) {
                if (u == root_) rc_.push_back(v);
                son++;
                dfs(v);
                low_[u] = min(low_[u], low_[v]);
                if (low_[v] >= dfn_[u]) {
                    if (u != root_) {
                        art_[u] = true;
                        ans_[u] += 1LL * sz_[v] * (n_-sz_[v]-1);
                    }
                    des += sz_[v];
                }
                sz_[u] += sz_[v];
            } else {
                low_[u] = min(low_[u], dfn_[v]);
            }
        }
        if (u != root_ && art_[u]) {
            ans_[u] += 1LL * (n_-1-des)*des;
        }
        if (u == root_ && son > 1) {
            art_[u] = true;
            for (int v: rc_) {
                ans_[u] += 1LL * sz_[v] * (n_-1-sz_[v]);
            }
        }
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    TarjanArticulationPoint tap(N, M);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        tap.addEdge(a, b);
    }
    tap.solve();
    for (int i = 0; i < N; i++) {
        printf("%ld\n", tap.ans_[i]);
    }
    return 0;
}
