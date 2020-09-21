// https://www.luogu.com.cn/problem/P4183
// [USACO18JAN]Cow at Large P

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

class TreeDivide {
 public:
  TreeDivide(int n) : n_(n), gr_(n, 2*(n-1)) {
    alloc();
  }

  ~TreeDivide() {
    dealloc();
  }

  void addEdge(int u, int v) {
    gr_.addEdge(u, v);
    gr_.addEdge(v, u);
    deg_[u]++;
    deg_[v]++;
  }

  void getRoot(int u, int fa) {
    siz_[u] = 1;
    son_[u] = 0;
    for (int eidx = gr_.head[u]; ~eidx; eidx = gr_.E[eidx].next) {
      int v = gr_.E[eidx].to;
      if (v == fa || vis_[v]) continue;
      getRoot(v, u);
      siz_[u] += siz_[v];
      son_[u] = max(son_[u], siz_[v]);
    }
    son_[u] = max(son_[u], sum_-siz_[u]);
    if (root_ == -1 || son_[u] < son_[root_]) root_ = u;
  }

  void dfs1(int u, int fa, int depth) {
    dep_[u] = depth;
    g_[u] = INT_MAX;
    if (deg_[u] == 1) g_[u] = 0;
    for (int eidx = gr_.head[u]; ~eidx; eidx = gr_.E[eidx].next) {
      int v = gr_.E[eidx].to;
      if (v == fa) continue;
      dfs1(v, u, depth+1);
      g_[u] = min(g_[u], g_[v]+1);
    }
  }

  void dfs2(int u, int father) {
    for (int eidx = gr_.head[u]; ~eidx; eidx = gr_.E[eidx].next) {
      int v = gr_.E[eidx].to;
      if (v == father) continue;
      g_[v] = min(g_[v], g_[u]+1);
      dfs2(v, u);
    }
  }

  void getDist(int u, int father, int cur) {
    d_[u] = cur;
    for (int eidx = gr_.head[u]; ~eidx; eidx = gr_.E[eidx].next) {
      int v = gr_.E[eidx].to;
      if (v == father || vis_[v]) continue;
      getDist(v, u, cur+1);
    }
  }

  struct Node {
    int dg, deg;
    bool operator < (const Node& other) const {
      return dg < other.dg;
    }
  };

  struct Bond {
    int id, dis;
    bool operator < (const Bond& other) const {
      return dis < other.dis;
    }
  };

  void addin(int u, int father) {
    p_[tot_] = Bond{u, d_[u]};
    q_[tot_++] = Node{g_[u]-d_[u], 2-deg_[u]};
    for (int eidx = gr_.head[u]; ~eidx; eidx = gr_.E[eidx].next) {
      int v = gr_.E[eidx].to;
      if (v == father || vis_[v]) continue;
      addin(v, u);
    }
  }

  void calc(int u, int father, int type) {
    tot_ = 0;
    addin(u, father);
    sort(p_, p_+tot_);
    sort(q_, q_+tot_);
    int t = 0, cursor = 0;
    for (int i = 0; i < tot_; i++) {
      while (cursor < tot_ && p_[i].dis >= q_[cursor].dg) {
        t += q_[cursor].deg;
        cursor++;
      }
      ans_[p_[i].id] += type * t;
    }
  }

  void solve(int u) {
    vis_[u] = true;
    getDist(u, -1, 0);
    calc(u, -1, 1);
    for (int eidx = gr_.head[u]; ~eidx; eidx = gr_.E[eidx].next) {
      int v = gr_.E[eidx].to;
      if (vis_[v]) continue;
      calc(v, u, -1);
      sum_ = siz_[v];
      root_ = -1;
      getRoot(v, u);
      solve(root_);
    }
  }

  void solve() {
    root_ = -1;
    sum_ = n_;
    getRoot(0, -1);
    solve(root_);
    for (int i = 0; i < n_; i++) {
      if (deg_[i] == 1) ans_[i] = 1;
    }
    for (int i = 0; i < n_; i++) {
      printf("%d\n", ans_[i]);
    }
  }

 private:
  int n_;
  Graph gr_;

  int* siz_;
  int* son_;
  bool* vis_;
  int root_ = -1;
  int *dep_;
  int *g_;
  int *deg_;
  int *d_;
  int tot_ = 0;
  Bond* p_;
  Node* q_;
  int* ans_;
  int sum_ = 0;

  void alloc() {
    siz_ = new int[n_]{};
    son_ = new int[n_]{};
    vis_ = new bool[n_]{};
    dep_ = new int[n_]{};
    g_ = new int[n_]{};
    deg_ = new int[n_]{};
    d_ = new int[n_]{};
    p_ = new Bond[n_]{};
    q_ = new Node[n_]{};
    ans_ = new int[n_]{};
  }

  void dealloc() {
    delete[] siz_;
    delete[] son_;
    delete[] vis_;
    delete[] dep_;
    delete[] g_;
    delete[] deg_;
    delete[] d_;
    delete[] p_;
    delete[] q_;
    delete[] ans_;
  }
};

int main() {
  int n;
  scanf("%d", &n);
  TreeDivide td(n);
  for (int i = 0; i < n-1; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    td.addEdge(x, y);
  }
  td.dfs1(0, -1, 0);
  td.dfs2(0, -1);
  td.solve();

  return 0;
}
