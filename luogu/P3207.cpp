// https://www.luogu.com.cn/problem/P3207
// [HNOI2010]物品调度

#include <bits/stdc++.h>
using namespace std;

// (g, x, y) that a*x + b*y = g
static void ext_gcd(int64_t a, int64_t b,
    int64_t &g, int64_t &x, int64_t &y) {
  if (b == 0) {
    g = a; x = 1; y = 0;
    return;
  }
  int64_t dp, xp, yp;
  ext_gcd(b, a % b, dp, xp, yp);
  g = dp;
  x = yp;
  y = xp - a / b * yp;
}

// find x that a*x = b mod n
static int64_t mod_solve(int64_t a, int64_t b, int64_t n) {
  int64_t d, xp, yp;
  ext_gcd(a, n, d, xp, yp);
  if (b % d == 0) {
    int64_t x0 = ((1LL * xp * b/d) % n + n) % n;
    return x0;
  } else {
    abort();
  }
}


class SegmentTree {
  int N;
  int *left_;

 public:
  SegmentTree(int N_): N(N_) {
    left_ = new int[4*N+1]{};
    build(1, 0, N-1);
  }

  ~SegmentTree() {
    delete[] left_;
  }

  void take(int x) {
    assert(0 <= x && x < N);
    take(1, 0, N-1, x);
  }

  int query(int a, int b) const {
    assert(0 <= a && a < N && 0 <= b && b < N && a <= b);
    return query(1, 0, N-1, a, b);
  }

 private:
  void take(int k, int l, int r, int x) {
    if (l == r) {
      left_[k] = -1;
      return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) take(2*k, l, mid, x);
    else take(2*k+1, mid+1, r, x);
    left_[k] = (left_[2*k] >= 0 ? left_[2*k] : left_[2*k+1]);
  }

  void build(int k, int l, int r) {
    if (l == r) {
      left_[k] = l;
      return;
    }
    int mid = (l + r) / 2;
    build(2*k, l, mid);
    build(2*k+1, mid+1, r);
    left_[k] = (left_[2*k] >= 0 ? left_[2*k] : left_[2*k+1]);
  }

  int query(int k, int l, int r, int a, int b) const {
    if (a <= l && r <= b) return left_[k];
    int mid = (l + r) / 2;
    int ret = -1;
    if (a <= mid) ret = query(2*k, l, mid, a, b);
    if (ret >= 0) return ret;
    if (mid < b) ret = query(2*k+1, mid+1, r, a, b);
    return ret;
  }
};

const int MAXN = 100010;

class Solver {
 public:
  Solver() {
    alloc();
  }

  ~Solver() {
    dealloc();
  }

  void solve() {
    scanf("%d%d%d%d%d%d", &n_, &s_, &q_, &p_, &m_, &d_);
    g_ = gcd(d_, n_);
    w_ = n_ / g_;
    inv_ = mod_solve(d_/g_, 1, w_);
    generateC();
    setupForest();
    solvePos();
    solveAns();
    clearForest();
  }

 private:
  int n_, s_, q_, p_, m_, d_;
  int g_, w_, inv_;
  int* c_;
  int* pos_;
  bool* vis_;
  SegmentTree **forest_;
  SegmentTree *root_;

  void alloc() {
    c_ = new int[MAXN]{};
    pos_ = new int[MAXN]{};
    vis_ = new bool[MAXN]{};
  }

  void dealloc() {
    delete[] c_;
    delete[] pos_;
    delete[] vis_;
  }

  void clearForest() {
    for (int i = 0; i < g_; i++) {
      delete forest_[i];
    }
    delete[] forest_;

    delete root_;
  }

  void generateC() {
    c_[0] = 0;
    for (int i = 1; i < n_; i++) {
      c_[i] = (1LL * c_[i-1] * q_ + p_) % m_;
    }
  }

  int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
  }

  void solvePos() {
    pos_[0] = s_;
    for (int i = 1; i < n_; i++) {
      int c = root_->query(c_[i] % g_, g_-1);
      if (c == -1) c = root_->query(0, c_[i] % g_ -1);
      assert(c != -1);
      int c2;
      if (c_[i] % g_ > c) c2 = (1LL * (c_[i] / g_ + 1) * g_ + c) % n_;
      else c2 = (1LL * c_[i] / g_ * g_ + c) % n_;
      int x0 = 1LL * inv_ * (c2 - c) / g_ % w_;
      int x = forest_[c]->query(x0, w_-1);
      if (x == -1) x = forest_[c]->query(0, x0-1);
      assert(x != -1);
      pos_[i] = (c + 1LL * x * d_) % n_;
      forest_[c]->take(x);
      if (forest_[c]->query(0, w_-1) == -1) {
        root_->take(c);
      }
    }
  }

  int traverse(int u) {
    int start = u;
    vis_[u] = true;
    int l = 1;
    int v = pos_[u];
    while (v != start) {
      u = v;
      vis_[u] = true;
      l++;
      v = pos_[u];
    }
    return l;
  }

  void solveAns() {
    memset(vis_, 0, n_*sizeof(bool));
    int ans = 0;
    for (int i = 0; i < n_; i++) {
      if (!vis_[i]) {
        int l = traverse(i);
        if (l > 1) {
          if (i == 0) ans += l - 1;
          else ans += l + 1;
        }
      }
    }
    printf("%d\n", ans);
  }

  void setupForest() {
    forest_ = new SegmentTree*[g_];
    for (int i = 0; i < g_; i++) {
      forest_[i] = new SegmentTree(w_);
    }
    root_ = new SegmentTree(g_);
    int c = s_ % g_;
    int x = 1LL * inv_ * (s_-c)/g_ % w_;
    forest_[c]->take(x);
    if (forest_[c]->query(0, w_-1) == -1) {
      root_->take(c);
    }
  }
};

int main() {
  int t;
  scanf("%d", &t);
  Solver solver;
  while (t--) {
    solver.solve();
  }
  return 0;
}
