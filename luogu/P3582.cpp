// https://www.luogu.com.cn/problem/P3582
// [POI2015]KIN

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
  int N;
  int64_t *left_, *right_, *mid_, *tot_;

 public:
  SegmentTree(int N_): N(N_) {
    left_ = new int64_t[int(3.7*N)]{};
    right_ = new int64_t[int(3.7*N)]{};
    mid_ = new int64_t[int(3.7*N)]{};
    tot_ = new int64_t[int(3.7*N)]{};
  }

  ~SegmentTree() {
    delete[] left_;
    delete[] right_;
    delete[] mid_;
    delete[] tot_;
  }

  void update(int t, int x) {
    // set val t to position x
    update(1, t, 1, N, x);
  }

  int64_t query() const {
    return mid_[1];
  }

 private:
  void update(int k, int t, int l, int r, int x) {
    if (l == r) {
      left_[k] = right_[k] = mid_[k] = tot_[k] = t;
      return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) update(2*k, t, l, mid, x);
    else update(2*k+1, t, mid+1, r, x);
    pushUp(k, l, r);
  }

  void pushUp(int k, int l, int r) {
    if (l == r) return;
    tot_[k] = tot_[2*k] + tot_[2*k+1];
    left_[k] = max(left_[2*k], tot_[2*k] + left_[2*k+1]);
    right_[k] = max(right_[2*k+1], tot_[2*k+1] + right_[2*k]);
    mid_[k] = max(max(mid_[2*k], mid_[2*k+1]), right_[2*k] + left_[2*k+1]);
  }
};

const int MAXN = 1000010;
int F[MAXN], W[MAXN];
int L[MAXN], P[MAXN];

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &F[i]);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d", &W[i]);
  }

  SegmentTree st(n);
  int64_t ans = W[F[1]];
  for (int i = 1; i <= n; i++) {
    int t = W[F[i]];
    int p = L[F[i]];
    int q = P[p];
    st.update(t, i);
    if (p > 0) st.update(-t, p);
    if (q > 0) st.update(0, q);
    ans = max(ans, st.query());
    P[i] = p;
    L[F[i]] = i;
  }
  printf("%ld\n", ans);

  return 0;
}
