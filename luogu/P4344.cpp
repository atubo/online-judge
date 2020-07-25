// https://www.luogu.com.cn/problem/P4344
// [SHOI2015]脑洞治疗仪

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
 public:
  SegmentTree(int n): n_(n) {
    alloc();
    build(1, 1, n_);
  }

  ~SegmentTree() {
    dealloc();
  }

  void dig(int l, int r) {
    erase(1, 1, n_, l, r);
  }

  int query(int l, int r) {
    Result res = query(1, 1, n_, l, r);
    return res.middle;
  }

  void heal(int l0, int r0, int l1, int r1) {
    int x = count(1, 1, n_, l0, r0);
    erase(1, 1, n_, l0, r0);
    fill(1, 1, n_, l1, r1, x);
  }

  void print() {
    for (int i = 1; i <= n_; i++) {
      printf("%d ", count(1, 1, n_, i, i));
    }
    printf("\n");
  }

 private:
  void alloc() {
    val_ = new int[4*n_+1];
    left_ = new int[4*n_+1];
    right_ = new int[4*n_+1];
    middle_ = new int[4*n_+1];
    lazy_ = new int[4*n_+1];
  }

  void dealloc() {
    delete[] val_;
    delete[] left_;
    delete[] right_;
    delete[] middle_;
    delete[] lazy_;
  }

  void build(int k, int l, int r) {
    val_[k] = r - l + 1;
    left_[k] = right_[k] = middle_[k] = 0;
    lazy_[k] = 1;
    if (l == r) return;
    int mid = (l + r) / 2;
    build(2*k, l, mid);
    build(2*k+1, mid+1, r);
  }

  void pushDown(int k, int l, int r) {
    if (lazy_[k] == -1 || l == r) return;
    lazy_[2*k] = lazy_[k];
    lazy_[2*k+1] = lazy_[k];
    int mid = (l + r) / 2;
    if (lazy_[k] == 0) {
      left_[2*k] = right_[2*k] = middle_[2*k] = (mid - l + 1);
      left_[2*k+1] = right_[2*k+1] = middle_[2*k+1] = (r - mid);
      val_[2*k] = 0;
      val_[2*k+1] = 0;
    } else {
      left_[2*k] = right_[2*k] = middle_[2*k] = 0;
      left_[2*k+1] = right_[2*k+1] = middle_[2*k+1] = 0;
      val_[2*k] = (mid - l + 1);
      val_[2*k+1] = (r - mid);
    }
    lazy_[k] = -1;
  }

  int count(int k, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) return val_[k];
    int ret = 0;
    int mid = (l + r) / 2;
    if (a <= mid) ret += count(2*k, l, mid, a, b);
    if (mid < b) ret += count(2*k+1, mid+1, r, a, b);
    return ret;
  }

  void merge(int k, int l, int r) {
    val_[k] = val_[2*k] + val_[2*k+1];
    int mid = (l + r) / 2;
    middle_[k] = max({right_[2*k]+left_[2*k+1],
        middle_[2*k], middle_[2*k+1]});
    left_[k] = left_[2*k];
    if (left_[2*k] == (mid - l + 1)) {
      left_[k] += left_[2*k+1];
    }
    right_[k] = right_[2*k+1];
    if (right_[2*k+1] == (r - mid)) {
      right_[k] += right_[2*k];
    }
  }

  void erase(int k, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      val_[k] = 0;
      left_[k] = right_[k] = middle_[k] = (r - l + 1);
      lazy_[k] = 0;
      return;
    }
    assert(l < r);
    int mid = (l + r) / 2;
    if (a <= mid) erase(2*k, l, mid, a, b);
    if (mid < b) erase(2*k+1, mid+1, r, a, b);
    merge(k, l, r);
  }

  int fill(int k, int l, int r, int a, int b, int x) {
    assert(x >= 0);
    if (x == 0) return 0;
    pushDown(k, l, r);
    int nz = r - l + 1 - val_[k];
    if (a <= l && r <= b && nz <= x) {
      val_[k] = r - l + 1;
      left_[k] = right_[k] = middle_[k] = 0;
      lazy_[k] = 1;
      return nz;
    }
    assert(l < r);
    int mid = (l + r) / 2;
    int cnt = 0;
    if (a <= mid) cnt = fill(2*k, l, mid, a, b, x);
    if (mid < b) cnt +=fill(2*k+1, mid+1, r, a, b, x-cnt);
    assert(cnt <= x);
    merge(k, l, r);
    return cnt;
  }

  struct Result {
    int left = 0, right = 0, middle = 0;
    Result(int l, int r, int m) : left(l), right(r), middle(m) {}
    void merge(const Result& other, int l, int mid, int r) {
      middle = max({middle, other.middle, right+other.left});
      if (left == mid - l + 1) left += other.left;
      int t = right;
      right = other.right;
      if (right == r - mid) right += t;
    }
  };

  Result query(int k, int l, int r, int a, int b) {
    pushDown(k, l, r);
    assert(l <= a && b <= r);
    if (a == l && r == b) {
      return Result(left_[k], right_[k], middle_[k]);
    }
    assert(l < r);
    int mid = (l + r) / 2;
    if (mid < a) return query(2*k+1, mid+1, r, a, b);
    if (b <= mid) return query(2*k, l, mid, a, b);
    Result ret = query(2*k, l, mid, a, mid);
    ret.merge(query(2*k+1, mid+1, r, mid+1, b), a, mid, b);
    return ret;
  }

  int n_;
  int* val_;
  int* left_;
  int* right_;
  int* middle_;
  int* lazy_;
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  SegmentTree st(n);
  for (int i = 0; i < m; i++) {
    int t, l0, r0, l1, r1;
    scanf("%d%d%d", &t, &l0, &r0);
    if (t == 0) {
      st.dig(l0, r0);
    } else if (t == 1) {
      scanf("%d%d", &l1, &r1);
      st.heal(l0, r0, l1, r1);
    } else {
      printf("%d\n", st.query(l0, r0));
    }
  }
  return 0;
}
