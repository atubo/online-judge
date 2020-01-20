// https://www.luogu.com.cn/problem/P4320
// 道路相遇

#include <bits/stdc++.h>
using namespace std;

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

// Online algorithm, pre-computing O(N log N)
// Each query O(1)

class RmqLca {
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

    int *log_;
    int *dfn_;  // node to first time in euler tour array
    int *depth_;
    int** st_;
    int dfs_clock_ = 0;

public:
    RmqLca(int N, int root)
        : N_(N), root_(root), MAXB_(log2(N)+2), g_(N, 2*(N-1)) {
            alloc();
    }

    ~RmqLca() {
        dealloc();
    }

    void addEdge(int u, int v) {
        g_.addEdge(u, v);
        g_.addEdge(v, u);
    }

    void build() {
        dfs(root_, -1, 0);

        setSparseTable();
    }

    int findLca(int u, int v) const {
        int x = dfn_[u], y = dfn_[v];
        if (x > y) swap(x, y);
        int d = log_[y-x+1];
        int a = st_[d][x], b = st_[d][y-(1<<d)+1];
        int lca = depth_[a] < depth_[b] ? a : b;
        return lca;
    }

private:
    void alloc() {
        log_ = new int[2*N_]{};
        dfn_ = new int[N_]{};
        depth_ = new int[N_]{};
        st_ = new int*[MAXB_]{};
        for (int i = 0; i < MAXB_; i++) {
          st_[i] = new int[2*N_]{};
          memset(st_[i], -1, 2*N_*sizeof(int));
        }
    }

    void dealloc() {
        delete[] log_;
        delete[] dfn_;
        delete[] depth_;
        for (int i = 0; i < MAXB_; i++) {
          delete[] st_[i];
        }
        delete[] st_;
    }

    void dfs(int x, int f, int d) {
        dfn_[x] = dfs_clock_;
        depth_[x] = d;
        st_[0][dfs_clock_++] = x;
        for (int eidx = g_.head[x]; ~eidx; eidx = g_.E[eidx].next) {
            int u = g_.E[eidx].to;
            if (u != f) {
                dfs(u, x, d+1);
                st_[0][dfs_clock_++] = x;
            }
        }
    }

    void setSparseTable() {
        for (int i = 2; i < dfs_clock_; i++) {
            log_[i] = log_[i>>1] + 1;
        }
        for (int j = 1; j < MAXB_; j++) {
            for (int i = 0; i <= dfs_clock_-(1<<j); i++) {
                int x = st_[j-1][i], y = st_[j-1][i+(1<<(j-1))];
                st_[j][i] = depth_[x] < depth_[y] ? x : y;
            }
        }
    }
};

// Find biconnected components in a undirected graph
class TarjanIndirectedBcc {
public:
    // m is the number of undirected edges
    TarjanIndirectedBcc(int n, int m):
      n_(n), g_(n, 2*m), tree_(n, n-1), lca2_(n, 0),
      MAXB_(log2(n)+1) {
        alloc();
    }

    ~TarjanIndirectedBcc() {
        dealloc();
    }

    void addEdge(int u, int v) {
        g_.addEdge(u, v);
        g_.addEdge(v, u);
    }

    void solve() {
      dfs(0, 0, true);
      if (art_[0]) {
        for (int u = 1; u < n_; u++) {
          if (parent_[u] == 0) cnt_[u] = 1;
        }
      }
      buildTree();
      dfs2(0, 0);
      buildLca();
    }

    bool check(int u, int p) {
      if (u == p) return true;
      int v = lift(u, depth_[u]-depth_[p]-1);
      return cnt_[v];
    }

    int solve(int u, int v) {
      int p = lca2_.findLca(u, v);
      int ans = tot_[u] + tot_[v] - 2*tot_[p] + 2;
      bool p1 = check(u, p);
      bool p2 = check(v, p);
      ans -= (p1 && p2);
      return ans;
    }

    void print() const {
      printf("dfn: ");
      for (int i = 0; i < n_; i++) {
        printf("%d ", dfn_[i]);
      }
      printf("\n");
      printf("low: ");
      for (int i = 0; i < n_; i++) {
        printf("%d ", low_[i]);
      }
      printf("\n");
      printf("art: ");
      for (int i = 0; i < n_; i++) {
        printf("%d ", art_[i]);
      }
      printf("\n");
      printf("parent: ");
      for (int i = 0; i < n_; i++) {
        printf("%d ", parent_[i]);
      }
      printf("\n");
      printf("cnt: ");
      for (int i = 0; i < n_; i++) {
        printf("%d ", cnt_[i]);
      }
      printf("\n");
      printf("tot: ");
      for (int i = 0; i < n_; i++) {
        printf("%d ", tot_[i]);
      }
      printf("\n");
    }

    bool *art_; // whether a node is articulation point
private:
    const int n_;
    Graph g_;
    Graph tree_;
    RmqLca lca2_;

    int *dfn_;
    int *low_;
    bool *vis_;
    int *parent_;
    int *cnt_;
    int *tot_;
    int tmpdfn_ = 0;
    int MAXB_;
    int **father_;
    int *depth_;

    void alloc() {
      dfn_ = new int[n_]{};
      low_ = new int[n_]{};
      vis_ = new bool[n_]{};
      art_ = new bool[n_]{};
      parent_ = new int[n_]{};
      cnt_ = new int[n_]{};
      tot_ = new int[n_]{};
      memset(parent_, -1, n_*sizeof(int));
      father_ = new int*[n_]{};
      for (int i = 0; i < n_; i++) {
        father_[i] = new int[MAXB_]{};
        memset(father_[i], -1, MAXB_*sizeof(int));
      }
      depth_ = new int[n_]{};
    }

    void dealloc() {
      delete[] dfn_;
      delete[] low_;
      delete[] vis_;
      delete[] art_;
      delete[] parent_;
      delete[] cnt_;
      delete[] tot_;
      for (int i = 0; i < n_; i++) {
        delete[] father_[i];
      }
      delete[] father_;
      delete[] depth_;
    }

    void dfs(int u, int d, bool root = false) {
        dfn_[u] = low_[u] = tmpdfn_++;
        vis_[u] = true;
        depth_[u] = d;
        int son = 0;
        for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
            int v = g_.E[eidx].to;
            if (!vis_[v]) {
                son++;
                parent_[v] = father_[v][0] = u;
                dfs(v, d+1);
                low_[u] = min(low_[u], low_[v]);
                if (low_[v] >= dfn_[u]) {
                    if (!root) {
                        cnt_[v] = 1;
                        art_[u] = true;
                    }
                }
            } else if (v != parent_[u]) {
                low_[u] = min(low_[u], dfn_[v]);
            }
        }
        if (root) {
            if (son > 1) {
                art_[u] = true;
            }
        }
    }

    int lift(int u, int h) {
      int v = u;
      for (int b = MAXB_-1; b >= 0; b--) {
        if ((h >> b) & 1) {
          v = father_[v][b];
        }
      }
      return v;
    }

    void buildTree() {
      for (int u = 1; u < n_; u++) {
        int f = parent_[u];
        tree_.addEdge(f, u);
      }
    }

    void dfs2(int u, int c) {
      tot_[u] = cnt_[u] + c;
      for (int j = 1; j < MAXB_; j++) {
        if (father_[u][j-1] == -1) break;
        father_[u][j] = father_[father_[u][j-1]][j-1];
      }
      for (int eidx = tree_.head[u]; ~eidx; eidx = tree_.E[eidx].next) {
        int v = tree_.E[eidx].to;
        dfs2(v, tot_[u]);
      }
    }

    void buildLca() {
      for (int u = 1; u < n_; u++) {
        int f = parent_[u];
        lca2_.addEdge(f, u);
      }
      lca2_.build();
    }
};

int N, M;

int main() {
  scanf("%d%d", &N, &M);
  TarjanIndirectedBcc tarjan(N, M);

  for (int i = 0; i < M; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    tarjan.addEdge(u, v);
  }
  tarjan.solve();

  int q;
  scanf("%d", &q);
  while (q--) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    printf("%d\n", tarjan.solve(u, v));
  }

  return 0;
}
