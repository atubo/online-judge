// https://www.luogu.org/problemnew/show/P4298
// [CTSC2008]祭祀

#include <bits/stdc++.h>
using namespace std;

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

// Note: be sure it's DAG
class TopologicalSort {
public:
    vector<int> topo;  // topologically sorted result

private:
    void topologicalSortUtil(const Graph &g, int v, bool visited[],
                             stack<int> &order) {
        visited[v] = true;

        for (int i = g.head[v]; i != -1; i = g.E[i].next) {
            int m = g.E[i].to;
            if (!visited[m]) {
                topologicalSortUtil(g, m, visited, order);
            }
        }

        order.push(v);
    }

public:
    TopologicalSort() {}

    void sort(const Graph &g) {
        const int N = g.N;
        topo.resize(N);

        stack<int> order;
        bool visited[N];
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                topologicalSortUtil(g, i, visited, order);
            }
        }

        int i = 0;
        while (!order.empty()) {
            topo[i++] = order.top();
            order.pop();
        }
    }
};

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
public:
    int nx_, ny_;
    bool** g_;

    int *cx_, *cy_;
    int *mk_;

    void alloc() {
        g_ = new bool*[nx_];
        for (int i = 0; i < nx_; i++) {
            g_[i] = new bool[ny_];
        }
        cx_ = new int[nx_];
        cy_ = new int[ny_];
        mk_ = new int[ny_];
    }

    void dealloc() {
        for (int i = 0; i < nx_; i++) {
            delete[] g_[i];
        }
        delete[] g_;

        delete[] cx_;
        delete[] cy_;
        delete[] mk_;
    }

    int path(int u) {
        for (int v = 0; v < ny_; v++) {
            if (g_[u][v] && !mk_[v]) {
                mk_[v] = 1;
                if (cy_[v] == -1 || path(cy_[v])) {
                    cx_[u] = v;
                    cy_[v] = u;
                    return 1;
                }
            }
        }
        return 0;
    }

public:
    Hungarian(int nx, int ny): nx_(nx), ny_(ny) {
        alloc();
        reset();
    }

    ~Hungarian() {
        dealloc();
    }

    void reset() {
        for (int i = 0; i < nx_; i++) {
            memset(g_[i], 0, ny_ * sizeof(bool));
        }
    }

    void addEdge(int x, int y) {
        g_[x][y] = true;
    }

    void removeEdge(int x, int y) {
        g_[x][y] = false;
    }

    int maxMatch() {
        int res = 0;
        memset(cx_, -1, nx_ * sizeof(int));
        memset(cy_, -1, ny_ * sizeof(int));
        for (int i = 0; i < nx_; i++) {
            if (cx_[i] == -1) {
                memset(mk_, 0, ny_ * sizeof(int));
                res += path(i);
            }
        }
        return res;
    }
};

class BipartiteMinVertexCover {
private:
    const int nx_, ny_;
    const int *cx_, *cy_;
    bool ** g_;

    bool *mk_, *mkx_, *mky_;

    void path(int u) {
        mkx_[u] = true;
        for (int v = 0; v < ny_; v++) {
            if (g_[u][v] && !mk_[v]) {
                mk_[v] = true;
                if (cy_[v] != -1) {
                    mky_[v] = true;
                    path(cy_[v]);
                }
            }
        }
    }

public:
    BipartiteMinVertexCover(int nx, int ny,
                            int *cx, int *cy,
                            bool **g)
        :nx_(nx), ny_(ny), cx_(cx), cy_(cy), g_(g) {
            mk_ = new bool[ny_]{};
            mkx_ = new bool[nx_]{};
            mky_ = new bool[ny_]{};
        }

    ~BipartiteMinVertexCover() {
        delete[] mky_;
        delete[] mkx_;
        delete[] mk_;
    }

    vector<int> calcMinVertexCover() {
        // [0, nx-1] means left side
        // [nx, nx+ny-1] means right side
        vector<int> ret;
        for (int i = 0; i < nx_; i++) {
            if (cx_[i] == -1) {
                memset(mk_, 0, ny_ * sizeof(bool));
                path(i);
            }
        }
        for (int i = 0; i < nx_; i++) {
            if (!mkx_[i]) {
                ret.push_back(i);
            }
        }
        for (int i = 0; i < ny_; i++) {
            if (mky_[i]) {
                ret.push_back(i+nx_);
            }
        }
        return ret;
    }
};

int N, M;

bool adj[110][110];
int ans;


int main() {
    scanf("%d%d", &N, &M);
    Graph g(N, M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g.addEdge(u, v);
    }
    TopologicalSort topo;
    topo.sort(g);

    for (int i = N-1; i >= 0; i--) {
        int u = topo.topo[i];
        for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
            int v = g.E[eidx].to;
            adj[u][v] = true;
            for (int w = 0; w < N; w++) {
                if (adj[v][w]) adj[u][w] = true;
            }
        }
    }

    Hungarian hungarian(N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (adj[i][j]) {
                hungarian.addEdge(i, j);
            }
        }
    }
    ans = N - hungarian.maxMatch();
    printf("%d\n", ans);
    BipartiteMinVertexCover bmc(N, N,
                                hungarian.cx_, hungarian.cy_,
                                hungarian.g_);
    vector<int> vc = bmc.calcMinVertexCover();
    string s(N, '1');
    for (int x: vc) {
        if (x >= N) s[x-N] = '0';
        else s[x] = '0';
    }
    printf("%s\n", s.c_str());

    for (int i = 0; i < N; i++) {
        int neighbor = 0;
        for (int j = 0; j < N; j++) {
            if (adj[i][j]) {
                hungarian.removeEdge(i, j);
                neighbor++;
            }
            if (adj[j][i]) {
                hungarian.removeEdge(j, i);
                neighbor++;
            }
            if (adj[i][j] || adj[j][i]) {
                for (int k = 0; k < N; k++) {
                    if (adj[j][k]) {
                        hungarian.removeEdge(j, k);
                    }
                    if (adj[k][j]) {
                        hungarian.removeEdge(k, j);
                    }
                }
            }
        }
        if (hungarian.maxMatch() == N-ans-neighbor) {
            printf("1");
        } else {
            printf("0");
        }
        for (int j = 0; j < N; j++) {
            if (adj[i][j]) {
                hungarian.addEdge(i, j);
            }
            if (adj[j][i]) {
                hungarian.addEdge(j, i);
            }
            if (adj[i][j] || adj[j][i]) {
                for (int k = 0; k < N; k++) {
                    if (adj[j][k]) {
                        hungarian.addEdge(j, k);
                    }
                    if (adj[k][j]) {
                        hungarian.addEdge(k, j);
                    }
                }
            }
        }
    }

    return 0;
}
