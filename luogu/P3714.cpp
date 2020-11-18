// https://www.luogu.com.cn/problem/P3714
// [BJOI2017]树的难题

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
 public:
  struct Edge {
    int next, to, c;
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
  void addEdge(int u, int v, int c) {
    E[eidx].to = v;
    E[eidx].c = c;
    E[eidx].next = head[u];
    head[u] = eidx++;
  }
};

class SegmentTree {
  const int INF = 2e9 + 1;
  const int n_;
  int *mx_;
  int *ch_[2];
  int cnt_ = 0;

  void alloc() {
    mx_ = new int[4*n_+1]{};
    for (int i = 0; i < 2; i++) {
      ch_[i] = new int[4*n_+1]{};
    }
  }

  void dealloc() {
    delete[] mx_;
    for (int i = 0; i < 2; i++) {
      delete[] ch_[i];
    }
  }

  int newNode() {
    ++cnt_;
    mx_[cnt_] = -INF;
    ch_[0][cnt_] = ch_[1][cnt_] = 0;
    return cnt_;
  }

  void ins(int& x, int l, int r, int t, int v) {
    x = x ? x : newNode();
    mx_[x] = max(mx_[x], v);
    if (l == r) return;
    int mid = (l + r) / 2;
    if (mid >= t) ins(ch_[0][x], l, mid, t, v);
    else ins(ch_[1][x], mid+1, r, t, v);
  }

  int query(int x, int l, int r, int a, int b) {
    if (!x) return -INF;
    if (l >= a && r <= b) return mx_[x];
    int mx = -INF;
    int mid = (l + r) / 2;
    if (mid >= a) mx = query(ch_[0][x], l, mid, a, b);
    if (mid < b) mx = max(mx, query(ch_[1][x], mid+1, r, a, b));
    return mx;
  }

 public:
  SegmentTree(int n): n_(n) {
    alloc();
  }

  ~SegmentTree() {
    dealloc();
  }

  void clear() {
    cnt_ = 0;
  }

  void ins(int& x, int t, int v) {
    ins(x, 0, n_, t, v);
  }

  int query(int x, int a, int b) {
    return query(x, 0, n_, a, b);
  }

  int merge(int p, int q) {
    if (!p || !q) return p + q;
    mx_[p] = max(mx_[p], mx_[q]);
    ch_[0][p] = merge(ch_[0][p], ch_[0][q]);
    ch_[1][p] = merge(ch_[1][p], ch_[1][q]);
    return p;
  }
};

class GravityTree {
 private:
  int n_, m_;
  int* sz_;
  bool* vis_;
  int* col_;
  Graph g_;
  SegmentTree st_;
  int msz_, id_; // max sz and the id in current getrt
  int ans_ = INT_MIN;
  int L, R;
  vector<pair<int, int>> rte_;

  void alloc() {
    sz_ = new int[n_]{};
    vis_ = new bool[n_]{};
    col_ = new int[m_]{};
  }

  void dealloc() {
    delete[] sz_;
    delete[] vis_;
    delete[] col_;
  }

  void getsz(int u) {
    vis_[u] = true;
    sz_[u] = 1;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (!vis_[v]) {
        getsz(v);
        sz_[u] += sz_[v];
      }
    }
    vis_[u] = false;
  }

  int getrt(int u, int tot) {
    int sz = 1, mx = 0;
    vis_[u] = true;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (!vis_[v]) {
        int t = getrt(v, tot);
        mx = max(mx, t);
        sz += t;
      }
    }
    mx = max(mx, tot - sz);
    if (mx < msz_) {
      msz_ = mx;
      id_ = u;
    }
    vis_[u] = false;
    return sz;
  }

  void qroute(int u, int l, int c, int val) {
    if (l > R) return;
    rte_.push_back(make_pair(l, val));
    vis_[u] = true;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      int c2 = g_.E[eidx].c;
      if (!vis_[v]) {
        qroute(v, l+1, c2, c2 == c ? val : val + col_[c2]);
      }
    }
    vis_[u] = false;
  }

 public:
  GravityTree(int n, int m): n_(n), m_(m), g_(n, 2*n-2), st_(n) {
    alloc();
  }

  ~GravityTree() {
    dealloc();
  }

  void solve(int u) {
    msz_ = INT_MAX;
    getsz(u);
    getrt(u, sz_[u]);
    u = id_;
    st_.clear();
    int r1 = 0, r2 = 0;
    st_.ins(r1, 0, 0);
    vis_[u] = true;
    vector<pair<int, int>> ch;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      int c = g_.E[eidx].c;
      if (!vis_[v]) {
        ch.push_back(make_pair(c, v));
      }
    }
    sort(ch.begin(), ch.end());
    for (int i = 0; i < (int)ch.size(); i++) {
      if (i && ch[i].first != ch[i-1].first) {
        r1 = st_.merge(r1, r2);
        r2 = 0;
      }
      rte_.clear();
      qroute(ch[i].second, 1, ch[i].first, col_[ch[i].first]);
      for (int j = 0; j < (int)rte_.size(); j++) {
        int left = max(0, L - rte_[j].first);
        int tmp = max(
          st_.query(r1, left, R-rte_[j].first),
          st_.query(r2, left, R-rte_[j].first) - col_[ch[i].first]);
        ans_ = max(ans_, tmp + rte_[j].second);
      }
      for (int j = 0; j < (int)rte_.size(); j++) {
        st_.ins(r2, rte_[j].first, rte_[j].second);
      }
    }
    for (int i = 0; i < (int)ch.size(); i++) {
      solve(ch[i].second);
    }
  }

  void solve() {
    scanf("%d%d", &L, &R);
    for (int i = 0; i < m_; i++) {
      scanf("%d", &col_[i]);
    }
    for (int i = 0; i < n_-1; i++) {
      int p, q, c;
      scanf("%d%d%d", &p, &q, &c);
      p--; q--; c--;
      g_.addEdge(p, q, c);
      g_.addEdge(q, p, c);
    }
    solve(0);
    printf("%d\n", ans_);
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  GravityTree gt(n, m);
  gt.solve();
  return 0;
}
