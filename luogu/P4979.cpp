// https://www.luogu.com.cn/problem/P4979
// 矿洞：坍塌

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
  int N;
  int *val, *lazy;

 public:
  SegmentTree(int N_): N(N_) {
    val = new int[4*N+1]{};
    lazy = new int[4*N+1]{};
    memset(lazy, -1, (4*N+1)*sizeof(int));
  }

  ~SegmentTree() {
    delete[] val;
    delete[] lazy;
  }
  // set t to range [a, b]
  void update(int t, int a, int b) {
    update(1, t, 1, N, a, b);
  }

  // query range sum in [a, b]
  int query(int a, int b) {
    return query(1, 1, N, a, b);
  }

  void build(const char* a, char c) {
    build(1, 1, N, a, c);
  }

 private:
  // set t to range [a, b], current node range is [l, r]
  void update(int k, int t, int l, int r, int a, int b) {
    if (a > b) return;
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      val[k] = (r - l + 1) * t;
      lazy[k] = t;
      return;
    }
    if (l == r) return;
    int mid = (l + r) / 2;
    if (a <= mid) update(2*k,   t, l, mid, a, b);
    if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
    val[k] = val[2*k] + val[2*k+1];
  }

  void pushDown(int k, int l, int r) {
    if (lazy[k] == -1 || l == r) return;
    lazy[2*k] = lazy[2*k+1] = lazy[k];
    int mid = (l + r) / 2;
    val[2*k] = (mid - l + 1) * lazy[k];
    val[2*k+1] = (r - mid) * lazy[k];
    lazy[k] = -1;
  }

  // query range sum in [a, b], current node is [l, r]
  int query(int k, int l, int r, int a, int b) {
    if (!k) return 0;
    if (b < l || a > r) return 0;
    pushDown(k, l, r);
    if (a <= l && r <= b) return val[k];
    int sum = 0;
    int mid = (l + r) / 2;
    if (a <= mid) sum += query(2*k, l, mid, a, b);
    if (mid < b)  sum += query(2*k+1, mid+1, r, a, b);
    return sum;
  }

  void build(int k, int l, int r, const char* a, char c) {
    if (l == r) {
      if (a[l] == c) val[k] = 1;
      return;
    }
    int mid = (l + r) / 2;
    build(2*k, l, mid, a, c);
    build(2*k+1, mid+1, r, a, c);
    val[k] = val[2*k] + val[2*k+1];
  }
};

const int MAXN = 500010;
char A[MAXN];
int N;
int Q;

int check(SegmentTree& st1, SegmentTree& st2, int x) {
  if (st1.query(x, x) == 1) return 0;
  if (st2.query(x, x) == 1) return 1;
  return 2;
}

void verify(SegmentTree& st1, SegmentTree& st2, SegmentTree& st3, int x, int y) {
  bool c1 = (x == 1 || y == N ||
      check(st1, st2, x-1) != check(st1, st2, y+1));
  const int len = y - x + 1;
  int first = check(st1, st2, x);
  bool c2;
  if (first == 0) {
    c2 = (st1.query(x, y) == len);
  } else if (first == 1) {
    c2 = (st2.query(x, y) == len);
  } else {
    c2 = (st3.query(x, y) == len);
  }
  if (c1 && c2) printf("Yes\n");
  else printf("No\n");
}

int main() {
  scanf("%d", &N);
  scanf("%s", A+1);
  SegmentTree sa(N), sb(N), sc(N);
  sa.build(A, 'A');
  sb.build(A, 'B');
  sc.build(A, 'C');
  char op[5], ore[5];
  int x, y;
  scanf("%d", &Q);
  for (int i = 0; i < Q; i++) {
    scanf("%s%d%d", op, &x, &y);
    if (op[0] == 'A') {
      scanf("%s", ore);
      if (ore[0] == 'A') {
        sa.update(1, x, y);
        sb.update(0, x, y);
        sc.update(0, x, y);
      } else if (ore[0] == 'B') {
        sa.update(0, x, y);
        sb.update(1, x, y);
        sc.update(0, x, y);
      } else {
        sa.update(0, x, y);
        sb.update(0, x, y);
        sc.update(1, x, y);
      }
    } else {
      verify(sa, sb, sc, x, y);
    }
  }

  return 0;
}
