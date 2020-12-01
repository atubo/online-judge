// https://www.luogu.com.cn/problem/P2839
// [国家集训队]middle

#include <bits/stdc++.h>
using namespace std;


class PersistentSegmentTree {
  struct Data {
    int lmax, rmax, tot;
  };

  struct Node {
    int ls, rs;
    Data d;
  };

 public:
  PersistentSegmentTree(int n) : n_(n) {
    alloc();
  }

  ~PersistentSegmentTree() {
    dealloc();
  }

  void build() {
    build(root_[1], 1, n_);
  }

  void update(int i, int x) {
    root_[i] = root_[i-1];
    update(root_[i], 1, n_, x);
  }

  bool check(int id, int l1, int r1, int l2, int r2) const {
    int ret = 0;
    if (r1 + 1 <= l2 - 1) ret += query(root_[id], 1, n_, r1+1, l2-1).tot;
    ret += query(root_[id], 1, n_, l1, r1).rmax;
    ret += query(root_[id], 1, n_, l2, r2).lmax;
    return ret >= 0;
  }

 private:
  const int n_;
  Node* t_;
  int* root_;
  int cnt_ = 0;

  void alloc() {
    t_ = new Node[n_<<6]{};
    root_ = new int[n_+1]{};
  }

  void dealloc() {
    delete[] t_;
    delete[] root_;
  }

  static Data merge(const Data& a, const Data& b) {
    Data ret;
    ret.tot = a.tot + b.tot;
    ret.lmax = max(a.lmax, a.tot + b.lmax);
    ret.rmax = max(b.rmax, b.tot + a.rmax);
    return ret;
  }

  void build(int &u, int l, int r) {
    int tmp = u;
    u = ++cnt_;
    t_[u] = t_[tmp];
    if (l == r) {
      t_[u].d.tot = t_[u].d.lmax = t_[u].d.rmax = 1;
      return;
    }
    int mid = (l + r) / 2;
    build(t_[u].ls, l, mid);
    build(t_[u].rs, mid+1, r);
    t_[u].d = merge(t_[t_[u].ls].d, t_[t_[u].rs].d);
  }

  void update(int &u, int l, int r, int x) {
    int tmp = u;
    u = ++cnt_;
    t_[u] = t_[tmp];
    if (l == r) {
      t_[u].d.tot = t_[u].d.lmax = t_[u].d.rmax = -1;
      return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) update(t_[u].ls, l, mid, x);
    else update(t_[u].rs, mid+1, r, x);
    t_[u].d = merge(t_[t_[u].ls].d, t_[t_[u].rs].d);
  }

  Data query(int u, int l, int r, int a, int b) const {
    if (a <= l && r <= b) return t_[u].d;
    int mid = (l + r) / 2;
    if (b <= mid) return query(t_[u].ls, l, mid, a, b);
    if (mid < a) return query(t_[u].rs, mid+1, r, a, b);
    return merge(query(t_[u].ls, l, mid, a, b),
                 query(t_[u].rs, mid+1, r, a, b));
  }
};

const int MAXN = 20010;
struct Data {
  int x, id;
  bool operator < (const Data& other) const {
    return x < other.x;
  }
} A[MAXN];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &A[i].x);
    A[i].id = i;
  }
  sort(A+1, A+n+1);
  PersistentSegmentTree pst(n);
  pst.build();
  for (int i = 2; i <= n; i++) {
    pst.update(i, A[i-1].id);
  }
  int Q;
  scanf("%d", &Q);
  int q[4];
  int lastans = 0;
  while (Q--) {
    for (int i = 0; i < 4; i++) {
      scanf("%d", &q[i]);
      q[i] = (q[i] + lastans) % n;
    }
    sort(q, q+4);
    for (int i = 0; i < 4; i++) {
      q[i]++;
    }
    int lo = 1, hi = n+1;
    while (lo < hi - 1) {
      int mid = (lo + hi) / 2;
      if (pst.check(mid, q[0], q[1], q[2], q[3])) lo = mid;
      else hi = mid;
    }
    printf("%d\n", lastans = A[lo].x);
  }

  return 0;
}
