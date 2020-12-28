// https://www.luogu.com.cn/problem/P3822
// [NOI2017]整数

#include <bits/stdc++.h>
using namespace std;

const uint32_t ALL = 4294967295;

class SegmentTree {
  int N;
  uint32_t *val_;
  char* tag_;

 public:
  SegmentTree(int N_): N(N_) {
    val_ = new uint32_t[4*N+1]{};
    tag_ = new char[4*N+1]{};
  }

  ~SegmentTree() {
    delete[] val_;
    delete[] tag_;
  }

  tuple<uint32_t, uint32_t, int> extract(uint32_t a, int b) {
    int x = b / 32;
    int d = 32 - (b % 32);
    if (d == 32) d = 0;
    uint32_t a1 = (a >> d) & ALL;
    uint32_t a2 = a & ((1U << d) - 1);
    if (d == 0) {
      swap(a1, a2);
    } else {
      a2 = a2 << (32 - d);
    }
    return make_tuple(x, a1, a2);
  }

  void add(uint32_t a, int b) {
    int x;
    uint32_t a1, a2;
    tie(x, a1, a2) = extract(a, b);
    uint32_t carry = add(1, 0, N-1, a2, x);
    carry = add(1, 0, N-1, a1+carry, x+1);
    if (carry) {
      int x2 = searchNonFull(1, 0, N-1, x+2);
      assert(x2 != INT_MAX);
      carry = add(1, 0, N-1, 1, x2);
      assert(carry == 0);
      if (x + 2 < x2) setZero(1, 0, N-1, x+2, x2-1);
    }
  }

  void sub(uint32_t a, int b) {
    int x;
    uint32_t a1, a2;
    tie(x, a1, a2) = extract(a, b);
    uint32_t borrow = sub(1, 0, N-1, a2, x);
    borrow = sub(1, 0, N-1, a1+borrow, x+1);
    if (borrow) {
      int x2 = searchNonZero(1, 0, N-1, x+2);
      assert(x2 != INT_MAX);
      borrow = sub(1, 0, N-1, 1, x2);
      assert(borrow == 0);
      if (x + 2 < x2) setFull(1, 0, N-1, x+2, x2-1);
    }
  }

  int query(int b) {
    int x = b / 32;
    int y = b % 32;
    return query(1, 0, N-1, x, y);
  }

 private:

  bool add(int k, int l, int r, uint32_t t, int x) {
    pushDown(k, l, r);
    if (l == r) {
      uint32_t old = val_[k];
      val_[k] += t;
      if (val_[k] == 0) tag_[k] = 0;
      else if (val_[k] == ALL) tag_[k] = 1;
      else tag_[k] = -1;
      return val_[k] < old;
    }
    int mid = (l + r) / 2;
    bool ret = (x <= mid ? add(2*k, l, mid, t, x) : add(2*k+1, mid+1, r, t, x));
    pushUp(k);
    return ret;
  }

  bool sub(int k, int l, int r, uint32_t t, int x) {
    pushDown(k, l, r);
    if (l == r) {
      uint32_t old = val_[k];
      val_[k] -= t;
      if (val_[k] == 0) tag_[k] = 0;
      else if (val_[k] == ALL) tag_[k] = 1;
      else tag_[k] = -1;
      return val_[k] > old;
    }
    int mid = (l + r) / 2;
    bool ret = (x <= mid ? sub(2*k, l, mid, t, x) : sub(2*k+1, mid+1, r, t, x));
    pushUp(k);
    return ret;
  }

  void pushDown(int k, int l, int r) {
    if (l == r || tag_[k] == -1) return;
    tag_[2*k] = tag_[2*k+1] = tag_[k];
    if (tag_[k] == 1) {
      val_[2*k] = val_[2*k+1] = ALL;
    } else {
      val_[2*k] = val_[2*k+1] = 0;
    }
  }

  void pushUp(int k) {
    if (tag_[2*k] == tag_[2*k+1]) tag_[k] = tag_[2*k];
    else tag_[k] = -1;
  }

  int searchNonFull(int k, int l, int r, int x) {
    pushDown(k, l, r);
    if (tag_[k] == 1) return INT_MAX;
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (x <= l) {
      if (tag_[2*k] != 1) return searchNonFull(2*k, l, mid, x);
      return searchNonFull(2*k+1, mid+1, r, x);
    } else if (x <= mid) {
      int ret = searchNonFull(2*k, l, mid, x);
      if (ret != INT_MAX) return ret;
      return searchNonFull(2*k+1, mid+1, r, x);
    } else {
      return searchNonFull(2*k+1, mid+1, r, x);
    }
  }

  int searchNonZero(int k, int l, int r, int x) {
    pushDown(k, l, r);
    if (tag_[k] == 0) return INT_MAX;
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (x <= l) {
      if (tag_[2*k] != 0) return searchNonZero(2*k, l, mid, x);
      return searchNonZero(2*k+1, mid+1, r, x);
    } else if (x <= mid) {
      int ret = searchNonZero(2*k, l, mid, x);
      if (ret != INT_MAX) return ret;
      return searchNonZero(2*k+1, mid+1, r, x);
    } else {
      return searchNonZero(2*k+1, mid+1, r, x);
    }
  }

  int query(int k, int l, int r, int x, int y) {
    pushDown(k, l, r);
    if (l == r) {
      return (val_[k] >> y) & 1;
    }
    int mid = (l + r) / 2;
    if (x <= mid) return query(2*k, l, mid, x, y);
    return query(2*k+1, mid+1, r, x, y);
  }

  void setZero(int k, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      tag_[k] = 0;
      val_[k] = 0;
      return;
    }
    int mid = (l + r) / 2;
    if (a <= mid) setZero(2*k, l, mid, a, b);
    if (mid < b) setZero(2*k+1, mid+1, r, a, b);
    pushUp(k);
  }

  void setFull(int k, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      tag_[k] = 1;
      val_[k] = ALL;
      return;
    }
    int mid = (l + r) / 2;
    if (a <= mid) setFull(2*k, l, mid, a, b);
    if (mid < b) setFull(2*k+1, mid+1, r, a, b);
    pushUp(k);
  }
};

int main() {
  int n, t1, t2, t3;
  scanf("%d%d%d%d", &n, &t1, &t2, &t3);
  SegmentTree st(n+10);
  for (int i = 0; i < n; i++) {
    int op, a, b, k;
    scanf("%d", &op);
    if (op == 1) {
      scanf("%d%d", &a, &b);
      if (a == 0) continue;
      if (a > 0) st.add(a, b);
      else st.sub(-a, b);
    } else {
      scanf("%d", &k);
      printf("%d\n", st.query(k));
    }
  }
  return 0;
}
