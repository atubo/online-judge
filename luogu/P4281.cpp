// https://www.luogu.org/problemnew/show/P4281
// [AHOI2008]紧急集合 / 聚会

#include <bits/stdc++.h>
using namespace std;

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
    int* depth;
    int** father;

public:
    BinaryLiftLCA(int N, int root)
        : N_(N), root_(root), MAXB_(log2(N)+1), g_(N, 2*(N-1)) {
            alloc();
    }

    ~BinaryLiftLCA() {
        dealloc();
    }

    void addEdge(int u, int v) {
        g_.addEdge(u, v);
        g_.addEdge(v, u);
    }

    void build() {
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
    void alloc() {
        depth = new int[N_]{};
        father = new int*[N_]{};
        for (int i = 0; i < N_; i++) {
            father[i] = new int[MAXB_]{};
            memset(father[i], -1, MAXB_*sizeof(int));
        }
    }

    void dealloc() {
        delete[] depth;
        for (int i = 0; i < N_; i++) {
            delete[] father[i];
        }
        delete[] father;
    }

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

int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

int min3(int a, int b, int c) {
    return min(a, min(b, c));
}

int N, M;

int main() {
    scanf("%d%d", &N, &M);
    BinaryLiftLCA lca(N, 0);
    for (int i = 0; i < N-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--; b--;
        lca.addEdge(a, b);
    }
    lca.build();

    for (int i = 0; i < M; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--; b--; c--;
        int p1 = lca.findLCA(a, b);
        int p2 = lca.findLCA(b, c);
        int p3 = lca.findLCA(a, c);
        int d1 = lca.depth[p1];
        int d2 = lca.depth[p2];
        int d3 = lca.depth[p3];
        int dmin = min3(d1, d2, d3);
        int dmax = max3(d1, d2, d3);
        int rend;
        if (d1 == dmax) rend = p1;
        else if (d2 == dmax) rend = p2;
        else rend = p3;
        int ans = lca.depth[a] + lca.depth[b] + lca.depth[c]
            - (dmax + 2*dmin);
        printf("%d %d\n", rend+1, ans);
    }

    return 0;
}
