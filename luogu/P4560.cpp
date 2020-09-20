// https://www.luogu.com.cn/problem/P4560
// [IOI2014]Wall 砖墙

#include <bits/stdc++.h>
using namespace std;

const int HMAX = 100000;

struct Tag {
  Tag(int l = 0, int h = HMAX) : lo(l), hi(h) {}
  int lo, hi;
  void merge(const Tag& other) {
    if (other.lo >= hi) {
      lo = hi = other.lo;
    } else if (other.hi <= lo) {
      lo = hi = other.hi;
    } else {
      lo = max(lo, other.lo);
      hi = min(hi, other.hi);
    }
  }
};

// note it's 1-indexed
class SegmentTree {
  int N;
  Tag* lazy_;
  int* ans_;

 public:
  SegmentTree(int N_): N(N_) {
    lazy_ = new Tag[4*N+1]{};
    ans_ = new int[N]{};
    build(1, 0, N-1);
  }

  ~SegmentTree() {
    delete[] lazy_;
    delete[] ans_;
  }

  void update(int lo, int hi, int a, int b) {
    update(1, lo, hi, 0, N-1, a, b);
  }

  void query() {
    query(1, 0, N-1);
    for (int i = 0; i < N; i++) {
      printf("%d\n", ans_[i]);
    }
  }

 private:
  void build(int k, int l, int r) {
    if (l == r) {
      lazy_[k] = {0, 0};
      return;
    }
    int mid = (l + r) / 2;
    build(2*k, l, mid);
    build(2*k+1, mid+1, r);
  }

  void update(int k, int lo, int hi, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      lazy_[k].merge(Tag{lo, hi});
      return;
    }
    assert(l < r);
    int mid = (l + r) / 2;
    if (a <= mid) update(2*k, lo, hi, l, mid, a, b);
    if (mid < b) update(2*k+1, lo, hi, mid+1, r, a, b);
  }

  void pushDown(int k, int l, int r) {
    if (l == r) return;
    lazy_[2*k].merge(lazy_[k]);
    lazy_[2*k+1].merge(lazy_[k]);
    lazy_[k] = {0, HMAX};
  }

  void query(int k, int l, int r) {
    pushDown(k, l, r);
    if (l == r) {
      ans_[l] = lazy_[k].lo;
      return;
    }
    int mid = (l + r) / 2;
    query(2*k, l, mid);
    query(2*k+1, mid+1, r);
  }

};

int N, K;

int main() {
  scanf("%d%d", &N, &K);
  SegmentTree st(N);
  for (int i = 0; i < K; i++) {
    int t, l, r, h;
    scanf("%d%d%d%d", &t, &l, &r, &h);
    int lo, hi;
    if (t == 1) {
      lo = h;
      hi = HMAX;
    } else {
      lo = 0;
      hi = h;
    }
    st.update(lo, hi, l, r);
  }
  st.query();

  return 0;
}
