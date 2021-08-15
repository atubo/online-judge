// https://codeforces.com/problemset/problem/51/F
// Caterpillar

#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int next, from, to;
};

class Graph {
 public:
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

// Find edge biconnected components (ebcc) in an indirected graph
class TarjanEbcc {
 public:
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
  int bcc_cnt_ = 0;
 private:
  const int n_, m_;
  Graph g_;

  int *dfn_;
  int *low_;
  bool *vis_;
  bool *is_bridge_;
  int tmpdfn_ = 0;

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

class TreeSolver {
 public:
  explicit TreeSolver(const Graph& g) : g_(g) {
    n_ = g_.N;
    alloc();
  }

  ~TreeSolver() {
    dealloc();
  }

  int solve(int root) {
    dfs(root, -1);
    return dp_[root];
  }

  int solve() {
    int ret = INT_MAX;
    for (int i = 0; i < n_; i++) {
      ret = min(ret, solve(i));
    }
    return ret;
  }

  void dfs(int u, int fa) {
    sz_[u] = 1;
    dp2_[u] = 0;
    int mp = INT_MAX;
    int tot = 0;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (v != fa) {
        dfs(v, u);
        sz_[u] += sz_[v];
        int cost = min(1 + dp2_[v], sz_[v] - 1);
        dp2_[u] += cost;
        mp = min(mp, dp_[v] - cost);
        tot += cost;
      }
    }
    if (sz_[u] == 1) dp_[u] = 0;
    else {
      dp_[u] = mp + tot;
    }
  }

 private:
  void alloc() {
    dp_ = new int[n_]{};
    sz_ = new int[n_]{};
    dp2_ = new int[n_]{};
  }

  void dealloc() {
    delete[] dp_;
    delete[] sz_;
    delete[] dp2_;
  }

  const Graph& g_;
  int n_;
  int* dp_;
  int* sz_;
  int* dp2_;
};

class ForestSolver {
 public:
  ForestSolver(const Graph& g, const vector<int>& bccSz) :
    g_(g), bccSz_(bccSz) {
    n_ = bccSz_.size();
    alloc();
  }

  ~ForestSolver() {
    dealloc();
  }

  void solve() {
    int res = -1;
    for (int i = 0; i < n_; i++) {
      if (!vis_[i]) {
        res++;
        set<int> s;
        dfs1(i, -1, s);
        for (int u : s) {
          res += bccSz_[u] - 1;
        }
        map<int, int> mapping;
        for (int u : s) {
          int sz = mapping.size();
          mapping.insert(make_pair(u, sz));
        }
        Graph g(s.size(), 2*(s.size()-1));
        dfs2(i, -1, mapping, g);
        TreeSolver treeSolver(g);
        res += treeSolver.solve();
      }
    }
    printf("%d\n", res);
  }
 private:
  void alloc() {
    vis_ = new bool[n_]{};
  }

  void dealloc() {
    delete[] vis_;
  }

  void dfs1(int u, int f, set<int>& s) {
    s.insert(u);
    vis_[u] = true;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (v != f) {
        dfs1(v, u, s);
      }
    }
  }

  void dfs2(int u, int f, const map<int, int>& mapping, Graph& g) {
    int p = mapping.at(u);
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (v != f) {
        int q = mapping.at(v);
        g.addEdge(p, q);
        g.addEdge(q, p);
        dfs2(v, u, mapping, g);
      }
    }
  }

  const Graph& g_;
  const vector<int>& bccSz_;
  int n_;
  bool *vis_;
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  TarjanEbcc tarjan(n, m);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    tarjan.addEdge(a, b);
  }
  tarjan.solve();
  vector<int> bccSz(tarjan.bcc_cnt_);
  for (int i = 0; i < n; i++) {
    bccSz.at(tarjan.bcc_[i])++;
  }
  ForestSolver forestSolver(tarjan.g_bcc_, bccSz);
  forestSolver.solve();
  return 0;
}
