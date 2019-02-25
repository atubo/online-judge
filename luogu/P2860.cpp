// https://www.luogu.org/problemnew/show/P2860
// [USACO06JAN]冗余路径Redundant Paths

#include <bits/stdc++.h>
using namespace std;

// Find edge biconnected components (ebcc) in an indirected graph

class TarjanEbcc {
public:
    class Graph {
    public:
        struct Edge {
            int next, from, to;
        };

        int *head;
        int eidx;
        int N, M;

        Edge *E;

        Graph(int N_, int M_): N(N_), M(M_) {
            alloc();
            eidx = 0;
            for (int i = 0; i < N; i++) {
                head[i] = -1;
            }
        }

        ~Graph() {
            dealloc();
        }

        void addEdge(int u, int v) {
            E[eidx].from = u;
            E[eidx].to = v;
            E[eidx].next = head[u];
            head[u] = eidx++;
        }

        void alloc() {
            head = new int[N]{};
            E = new Edge[M]{};
        }

        void dealloc() {
            delete[] head;
            delete[] E;
        }
    };

    TarjanEbcc(int n, int m):
        g_bcc_(n, 2*m), n_(n), m_(m), g_(n, 2*m) {
        alloc();
    }

    ~TarjanEbcc() {
        dealloc();
    }

    void addEdge(int u, int v) {
        g_.addEdge(u, v);
        g_.addEdge(v, u);
    }

    void solve() {
        for (int u = 0; u < n_; u++) {
            if (!vis_[u]) tarjan(u, -1);
        }
        memset(vis_, 0, sizeof(bool)*n_);
        for (int u = 0; u < n_; u++) {
            if (!vis_[u]) {
                dfs1(u);
                bcc_cnt_++;
            }
        }
        memset(vis_, 0, sizeof(bool)*n_);
        for (int u = 0; u < n_; u++) {
            if (!vis_[u]) dfs2(u);
        }
    }

    int *bcc_;   // node is -> bcc id
    Graph g_bcc_;
private:
    const int n_, m_;
    Graph g_;

    int *dfn_;
    int *low_;
    bool *vis_;
    bool *is_bridge_;
    int tmpdfn_ = 0;
    int bcc_cnt_ = 0;

    void alloc() {
        dfn_ = new int[n_]{};
        low_ = new int[n_]{};
        bcc_ = new int[n_]{};
        vis_ = new bool[n_]{};
        is_bridge_ = new bool[2*m_]{};
    }

    void dealloc() {
        delete[] dfn_;
        delete[] low_;
        delete[] bcc_;
        delete[] vis_;
        delete[] is_bridge_;
    }

    void tarjan(int u, int fa) {
        dfn_[u] = low_[u] = tmpdfn_++;
        vis_[u] = true;
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            if (!vis_[v]) {
                tarjan(v, u);
                low_[u] = min(low_[u], low_[v]);
                if (low_[v] > dfn_[u]) {
                    is_bridge_[eidx] = is_bridge_[eidx^1] = true;
                }
            } else if (v != fa) {
                low_[u] = min(low_[u], dfn_[v]);
            }
        }
    }

    void dfs1(int u) {
        vis_[u] = true;
        bcc_[u] = bcc_cnt_;
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            if (!is_bridge_[eidx] && !vis_[v]) {
                dfs1(v);
            }
        }
    }

    void dfs2(int u) {
        vis_[u] = true;
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            if (!vis_[v]) dfs2(v);
            if (bcc_[u] != bcc_[v]) {
                g_bcc_.addEdge(bcc_[u], bcc_[v]);
            }
        }
    }
};

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    TarjanEbcc bcc(N, M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        bcc.addEdge(u, v);
    }

    bcc.solve();
    int ans = 0;
    for (int u = 0; u < N; u++) {
        int cnt = 0;
        for (int eidx = bcc.g_bcc_.head[u]; ~eidx;
             eidx = bcc.g_bcc_.E[eidx].next) {
            cnt++;
        }
        ans += (cnt == 1);
    }
    printf("%d\n", ans == 0 ? 0 : (ans+1)/2);
    return 0;
}
