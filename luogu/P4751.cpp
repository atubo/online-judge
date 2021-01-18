// https://www.luogu.com.cn/problem/P4751
// 【模板】"动态DP"&动态树分治（加强版）

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
struct Matrix {
  int m[2][2];
  Matrix() {
    m[0][0] = m[0][1] = m[1][0] = m[1][1] = -0x3f3f3f3f;
  }

  friend Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix c;
    for (int i = 0; i < 2; i++) {
      for (int k = 0; k < 2; k++) {
        for (int j = 0; j < 2; j++) {
          c.m[i][j] = max(c.m[i][j], a.m[i][k] + b.m[k][j]);
        }
      }
    }
    return c;
  }

  int gmx() const {
    return max(max(m[0][0], m[0][1]), max(m[1][0], m[1][1]));
  }

  void print() const {
    printf("%d %d %d %d\n", m[0][0], m[0][1], m[1][0], m[1][1]);
  }
};

class Solver {
 public:
  Solver(int n, int q) : n_(n), q_(q), g_(n, 2*(n-1)) {
    alloc();
    for (int i = 0; i < n; i++) {
      scanf("%d", &wt_[i]);
    }
    for (int i = 0; i < n-1; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      g_.addEdge(u, v);
      g_.addEdge(v, u);
    }
    dfs(0);
    init();
    root_ = build(0);
  }

  ~Solver() {
    dealloc();
  }

  void solve() {
    for (int i = 0, last = 0; i < q_; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      x ^= last;
      x--;
      modify(x, y);
      last = mul_[root_].gmx();
      printf("%d\n", last);
    }
  }

  void update(int u) {
    if (s_[u][0] >= 0 && s_[u][1] >= 0) {
      mul_[u] = mul_[s_[u][0]] * w_[u] * mul_[s_[u][1]];
    } else if (s_[u][0] >= 0) {
      mul_[u] = mul_[s_[u][0]] * w_[u];
    } else if (s_[u][1] >= 0) {
      mul_[u] = w_[u] * mul_[s_[u][1]];
    } else {
      mul_[u] = w_[u];
    }
  }

  void gtw(int u, int v) {
    w_[u].m[0][0] += mul_[v].gmx();
    w_[u].m[0][1] = w_[u].m[0][0];
    w_[u].m[1][0] += max(mul_[v].m[0][0], mul_[v].m[0][1]);
    fa_[v] = u;
  }

  void modify(int p, int w) {
    w_[p].m[1][0] += w - wt_[p];
    wt_[p] = w;
    for (int t = p; t != -1; t = fa_[t]) {
      if (isr(t) && fa_[t] != -1) {
        int f = fa_[t];
        w_[f].m[0][0] -= mul_[t].gmx();
        w_[f].m[1][0] -= max(mul_[t].m[0][0], mul_[t].m[0][1]);
        update(t);
        w_[f].m[0][0] += mul_[t].gmx();
        w_[f].m[0][1] = w_[f].m[0][0];
        w_[f].m[1][0] += max(mul_[t].m[0][0], mul_[t].m[0][1]);
      } else {
        update(t);
      }
    }
  }

 private:
  int n_;
  int q_;
  Graph g_;
  int* wt_;
  int* sz_;
  int* lsz_;
  int* h_;
  array<int, 2> *s_;
  int *fa_;
  int *st_;
  Matrix *mul_, *w_;
  bool *book_;
  int root_ = -1;

  void alloc() {
    wt_ = new int[n_]{};
    sz_ = new int[n_]{};
    lsz_ = new int[n_]{};
    h_ = new int[n_]{};
    memset(h_, -1, n_*sizeof(int));
    s_ = new array<int, 2>[n_]{};
    for (int i = 0; i < n_; i++) {
      s_[i][0] = s_[i][1] = -1;
    }
    fa_ = new int[n_]{};
    memset(fa_, -1, n_*sizeof(int));
    st_ = new int[n_]{};
    mul_ = new Matrix[n_]{};
    w_ = new Matrix[n_]{};
    book_ = new bool[n_]{};
  }

  void dealloc() {
    delete[] wt_;
    delete[] sz_;
    delete[] lsz_;
    delete[] h_;
    delete[] s_;
    delete[] fa_;
    delete[] st_;
    delete[] mul_;
    delete[] w_;
    delete[] book_;
  }

  int dfs(int u) {
    sz_[u] = 1;
    int mx = 0;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (sz_[v] == 0) {
        sz_[u] += dfs(v);
        if (mx < sz_[v]) {
          mx = sz_[v];
          h_[u] = v;
        }
      }
    }
    return sz_[u];
  }

  void init() {
    for (int u = 0; u < n_; u++) {
      w_[u].m[0][0] = w_[u].m[0][1] = 0;
      w_[u].m[1][0] = wt_[u];
    }
  }

  bool isr(int p) {
    return fa_[p] != -1 && s_[fa_[p]][0] != p && s_[fa_[p]][1] != p;
  }

  int sbuild(int l, int r) {
    if (l >= r) return -1;
    int tot = 0;
    for (int i = l; i < r; i++) tot += lsz_[st_[i]];
    for (int i = l, ns = lsz_[st_[i]]; i < r; i++, ns += lsz_[st_[i]]) {
      if (2*ns >= tot) {
        int ls = sbuild(l, i);
        int rs = sbuild(i+1, r);
        s_[st_[i]][0] = ls;
        s_[st_[i]][1] = rs;
        if (ls >= 0) fa_[ls] = st_[i];
        if (rs >= 0) fa_[rs] = st_[i];
        update(st_[i]);
        return st_[i];
      }
    }
    assert(false);
    return -1;
  }

  int build(int p) {
    for (int t = p; t != -1; t = h_[t]) book_[t] = true;
    for (int t = p; t != -1; t = h_[t]) {
      for (int eidx = g_.head[t]; ~eidx; eidx = g_.E[eidx].next) {
        int v = g_.E[eidx].to;
        if (!book_[v]) gtw(t, build(v));
      }
    }
    int tp = 0;
    for (int t = p; t != -1; t = h_[t]) st_[tp++] = t;
    for (int t = p; t != -1; t = h_[t]) {
      lsz_[t] = sz_[t] - (h_[t] == -1 ? 0 : sz_[h_[t]]);
    }
    return sbuild(0, tp);
  }
};

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  Solver solver(n, q);
  solver.solve();
  return 0;
}
