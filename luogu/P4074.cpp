// https://www.luogu.com.cn/problem/P4074
// [WC2013]糖果公园

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

const int MAXN = 100010;
int father_[MAXN][17];

struct Query {
  int l, r;
  int id;
  int lca, t;
  int x, y;
  bool operator < (const Query& other) const {
    if (x != other.x) return x < other.x;
    if (y != other.y) return y < other.y;
    return t < other.t;
  }
} Q[MAXN];

class Solver {
 public:
  Solver(int n, int m, int q) : n_(n), m_(m), q_(q), g_(n, 2*(n-1)) {
    alloc();
    memset(father_, -1, sizeof(father_));
  }

  ~Solver() {
    dealloc();
  }

  void solve() {
    for (int i = 1; i <= m_; i++) {
      scanf("%d", &v_[i]);
    }
    for (int i = 1; i <= n_; i++) {
      scanf("%d", &w_[i]);
    }
    for (int i = 0; i < n_-1; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      a--; b--;
      g_.addEdge(a, b);
      g_.addEdge(b, a);
    }
    dfs(0);
    for (int i = 0; i < n_; i++) {
      scanf("%d", &cdy_[i]);
    }

    int len = pow(2*n_, 2.0/3.0);
    int tim = 0, idx = 0;
    for (int i = 0; i < q_; i++) {
      int t, x, y;
      scanf("%d%d%d", &t, &x, &y);
      if (t == 0) {
        ++tim;
        pla_[tim] = x-1;
        chg_[tim] = y;
      } else {
        x--; y--;
        int p = lca(x, y);
        if (dep_[x] > dep_[y]) swap(x, y);
        if (x == p) {
          Q[idx] = {first_[x], first_[y], idx, -1, tim, first_[x]/len, first_[y]/len};
        } else {
          Q[idx] = {last_[x], first_[y], idx, p, tim, last_[x]/len, first_[y]/len};
        }
        idx++;
      }
    }
    sort(Q, Q+idx);
    int l = 0, r = -1, momt = 0;
    for (int i = 0; i < idx; i++) {
      int L = Q[i].l, R = Q[i].r, t = Q[i].t, p = Q[i].lca;
      while (l < L) move(order_[l++]);
      while (l > L) move(order_[--l]);
      while (r < R) move(order_[++r]);
      while (r > R) move(order_[r--]);
      while (momt < t) change(++momt);
      while (momt > t) change(momt--);
      if (p != -1) move(p);
      ans_[Q[i].id] = curr_;
      if (p != -1) move(p);
    }

    for (int i = 0; i < idx; i++) {
      printf("%ld\n", ans_[i]);
    }
  }
 private:
  void alloc() {
    order_ = new int[2*n_]{};
    dep_ = new int[n_]{};
    first_ = new int[n_]{};
    last_ = new int[n_]{};
    v_ = new int[m_+1]{};
    num_ = new int[m_+1]{};
    w_ = new int[n_+1]{};
    cdy_ = new int[n_]{};
    vis_ = new bool[n_]{};
    pla_ = new int[q_+1]{};
    chg_ = new int[q_+1]{};
    ans_ = new int64_t[q_]{};
  }

  void dealloc() {
    delete[] order_;
    delete[] dep_;
    delete[] first_;
    delete[] last_;
    delete[] v_;
    delete[] num_;
    delete[] w_;
    delete[] cdy_;
    delete[] vis_;
    delete[] pla_;
    delete[] chg_;
    delete[] ans_;
  }

  void dfs(int u) {
    order_[cnt_++] = u;
    first_[u] = cnt_ - 1;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (v == father_[u][0]) continue;
      father_[v][0] = u;
      dep_[v] = dep_[u] + 1;
      for (int j = 1; j < 17; j++) {
        if (father_[v][j-1] >= 0) {
          father_[v][j] = father_[father_[v][j-1]][j-1];
        }
      }
      dfs(v);
    }
    order_[cnt_++] = u;
    last_[u] = cnt_ - 1;
  }

  int lca(int x, int y) const {
    if (dep_[x] < dep_[y]) swap(x, y);
    for (int i = 16; i >= 0; i--) {
      if (dep_[x] - (1 << i) >= dep_[y]) {
        x = father_[x][i];
      }
      if (x == y) return x;
    }
    for (int i = 16; i >= 0; i--) {
      if (father_[x][i] != father_[y][i]) {
        x = father_[x][i];
        y = father_[y][i];
      }
    }
    return father_[x][0];
  }

  void add(int x) {
    curr_ += 1LL * v_[cdy_[x]] * w_[++num_[cdy_[x]]];
  }

  void del(int x) {
    curr_ -= 1LL * v_[cdy_[x]] * w_[num_[cdy_[x]]--];
  }

  void move(int x) {
    vis_[x] ? del(x) : add(x);
    vis_[x] ^= 1;
  }

  void change(int x) {
    if (vis_[pla_[x]]) {
      move(pla_[x]);
      swap(cdy_[pla_[x]], chg_[x]);
      move(pla_[x]);
    } else {
      swap(cdy_[pla_[x]], chg_[x]);
    }
  }

  int n_, m_, q_;
  Graph g_;
  int cnt_ = 0;
  int *order_;
  int *dep_;
  int *first_, *last_;
  int64_t curr_ = 0;
  int *v_, *cdy_, *num_, *w_;
  bool* vis_;
  int *pla_, *chg_;
  int64_t* ans_;
};

int main() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  Solver solver(n, m, q);
  solver.solve();
  return 0;
}
