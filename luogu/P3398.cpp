// https://www.luogu.org/problemnew/show/P3398
// 仓鼠找sugar

#include <bits/stdc++.h>
using namespace std;

// Online algorithm, pre-computing O(N log N)
// Each query O(log N)

class BinaryLiftLCA {
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

    int N_, root_;
    int MAXB_;
    Graph g_;
public:
    vector<int> depth;
    vector<vector<int> > father;

public:
    BinaryLiftLCA(int N, int root)
        : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, 2*(N-1)) {
    }

    void addEdge(int u, int v) {
        g_.addEdge(u, v);
        g_.addEdge(v, u);
    }

    void build() {
        depth.resize(N_);
        father.resize(N_);
        for (int i = 0; i < N_; i++) {
            father[i].resize(MAXB_, -1);
        }

        dfs(root_, -1, 0);

        binaryLift();
    }

    int findLCA(int u, int v) const {
        if (depth[u] < depth[v]) swap(u, v);
        for (int b = MAXB_-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (depth[father[u][b]] >= depth[v]) {
                u = father[u][b];
            }
        }

        if (u == v) return u;

        for (int b = MAXB_-1; b >= 0; b--) {
            if (father[u][b] == -1) continue;
            if (father[u][b] != father[v][b]) {
                u = father[u][b];
                v = father[v][b];
            }
        }
        return father[u][0];
    }

private:
    void dfs(int x, int f, int d) {
        depth[x] = d;
        father[x][0] = f;
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int u = g_.E[eidx].to;
            if (u != f) dfs(u, x, d+1);
        }
    }

    void binaryLift() {
        for (int j = 1; j < MAXB_; j++) {
            for (int i = 0; i < N_; i++) {
                if (father[i][j-1] != -1) {
                    father[i][j] = father[father[i][j-1]][j-1];
                }
            }
        }
    }
};

const int MAXN = 100010;
int N, Q;

bool meet(const BinaryLiftLCA &lca, int a, int b, int c, int d) {
    int p = lca.findLCA(a, b);
    int q = lca.findLCA(c, d);
    int s = lca.findLCA(a, d);
    if (lca.depth[s] < lca.depth[p]) return false;
    if (lca.depth[s] < lca.depth[q]) return false;
    int t = lca.findLCA(a, c);
    if (lca.depth[s] < lca.depth[t]) return false;
    return true;
}


bool solve(const BinaryLiftLCA &lca, int a, int b, int c, int d) {
    int p = lca.findLCA(a, b);
    int q = lca.findLCA(c, d);
    int s = lca.findLCA(a, c);
    if (lca.depth[s] >= max(lca.depth[p], lca.depth[q])) return true;
    return meet(lca, a, b, c, d) || meet(lca, c, d, a, b);
}

int main() {
    scanf("%d%d", &N, &Q);
    BinaryLiftLCA lca(N, 0);
    for (int i = 0; i < N-1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        lca.addEdge(u, v);
    }
    lca.build();

    for (int i = 0; i < Q; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        a--; b--; c--; d--;
        bool ans = solve(lca, a, b, c, d);
        printf(ans ? "Y\n":"N\n");
    }

    return 0;
}
