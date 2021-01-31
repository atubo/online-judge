// https://www.luogu.com.cn/problem/P4192
// 旅行规划

#include <bits/stdc++.h>
using namespace std;

const int B = 300;

struct Line {
  double k;
  double b;
  Line(double kk = 0, double bb = 0) : k(kk), b(bb) {}
  double calc(double x) {
    return k*x + b;
  }
  double cross(const Line& t) {
    return (t.b - b) / (k - t.k);
  }
};

struct Block {
  Line q[B];
  int l, r;

  void clear() {
    l = r = 0;
  }

  void init(int64_t *a, int x, int y) {
    clear();
    for (int i = x+1; i <= y; i++) {
      a[i] += a[i-1];
    }
    for (int i = x; i <= y; i++) {
      Line t(i-x+1, a[i]);
      while (r - l > 1 && q[r-2].cross(q[r-1]) > t.cross(q[r-2])) r--;
      q[r++] = t;
    }
  }

  double query(int64_t k) {
    if (q[0].cross(q[1]) > k) return q[0].calc(k);
    if (q[r-2].cross(q[r-1]) < k) return q[r-1].calc(k);
    int lo = l, hi = r-2;
    while (lo < hi-1) {
      int mid = (lo + hi) / 2;
      if (q[mid].cross(q[mid+1]) > k) {
        hi = mid;
      } else {
        lo = mid;
      }
    }
    return q[hi].calc(k);
  }
};

class FenwickTree {
 public:
  // 1-indexed
  FenwickTree(int size): n_(size) {
    tree_ = new int64_t[n_+1]{};
  }

  ~FenwickTree() {
    delete[] tree_;
  }

  // add v to value at x
  void add(int x, int64_t v) {
    while(x <= n_) {
      tree_[x] += v;
      x += (x & -x);
    }
  }

  void update(int x, int y, int64_t k) {
    add(x, k);
    add(y+1, -k);
  }

  // get cumulative sum up to and including x
  int64_t query(int x) const {
    int64_t res = 0;
    while(x) {
      res += tree_[x];
      x -= (x & -x);
    }
    return res;
  }

  // get result for [x, y]
  int64_t query(int x, int y) const {
    return query(y) - (x > 1 ? query(x-1) : 0);
  }

 private:
  int64_t* tree_;
  const int n_;
};

const int64_t INF = 200000000000005;
const int MAXN = 100005;
int N;
int64_t a[MAXN];
int b[MAXN];
int L[500], R[500], cnt;
int64_t add[500], sum[500];

class Solution {
 public:
  Solution() : ft_(N) {}

  void init() {
    for (cnt = 1; ; cnt++) {
      L[cnt] = R[cnt-1] + 1;
      R[cnt] = R[cnt-1] + B;
      if (R[cnt] > N) R[cnt] = N;
      for (int i = L[cnt]; i <= R[cnt]; i++) {
        b[i] = cnt;
      }
      if (R[cnt] == N) break;
    }
    for (int i = 1; i <= N; i++) {
      scanf("%ld", &a[i]);
      sum[b[i]] += a[i];
      ft_.update(i, i, a[i]);
    }
    for (int i = 1; i <= cnt; i++) {
      block_[i].init(a, L[i], R[i]);
      sum[i] += sum[i-1];
    }
  }

  void solve() {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
      int op, x, y, k;
      scanf("%d%d%d", &op, &x, &y);
      if (op) {
        printf("%ld\n", query(x, y));
      } else {
        scanf("%d", &k);
        update(x, y, k);
      }
    }
  }

  void update(int l, int r, int64_t k) {
    ft_.update(l, r, k);
    for (int i= b[l]; i <= cnt; i++) {
      sum[i] += 1LL * (min(R[i], r) - l + 1) * k;
    }
    for (int i = b[l] + 1; i < b[r]; i++) {
      add[i] += k;
    }

    for (int i = L[b[l]]; i <= R[b[l]]; i++) {
      a[i] = ft_.query(i);
    }
    add[b[l]] = 0;
    block_[b[l]].init(a, L[b[l]], R[b[l]]);

    if (b[l] == b[r]) return;

    for (int i = L[b[r]]; i <= R[b[r]]; i++) {
      a[i] = ft_.query(i);
    }
    add[b[r]] = 0;
    block_[b[r]].init(a, L[b[r]], R[b[r]]);
  }

  int64_t F(double x) {
    return int64_t(x > 0 ? x + 0.5 : x - 0.5);
  }

  int64_t query(int l, int r) {
    int64_t ans = -INF;
    for (int i = b[l] + 1; i < b[r]; i++) {
      ans = max(ans, F(block_[i].query(add[i]) + sum[i-1]));
    }
    int64_t t = 0;
    for (int i = L[b[l]]; i <= min(R[b[l]], r); i++) {
      t += ft_.query(i);
      if (i >= l) ans = max(ans, t + sum[b[l]-1]);
    }
    if (b[l] == b[r]) return ans;
    t = 0;
    for (int i = L[b[r]]; i <= r; i++) {
      t += ft_.query(i);
      ans = max(ans, t + sum[b[r]-1]);
    }
    return ans;
  }
 private:
  FenwickTree ft_;
  Block block_[500];
};

int main() {
  scanf("%d", &N);
  Solution solution;
  solution.init();
  solution.solve();
  return 0;
}
