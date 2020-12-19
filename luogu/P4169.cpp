// https://www.luogu.com.cn/problem/P4169
// [Violet]天使玩偶/SJY摆棋子

#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
  int N;
  int *mx_;

 public:
  SegmentTree(int N_): N(N_) {
    mx_ = new int[4*N+1]{};
    reset();
  }

  ~SegmentTree() {
    delete[] mx_;
  }

  void modify(int t, int x) {
    assert(0 <= x && x < N);
    modify(1, t, 0, N-1, x);
  }

  int query(int a, int b) {
    assert(0 <= a && a <= b && b < N);
    return query(1, 0, N-1, a, b);
  }

  void reset() {
    memset(mx_, 0x80, (4*N+1)*sizeof(int));
  }
 private:
  int query(int k, int l, int r, int a, int b) {
    if (a <= l && r <= b) return mx_[k];
    int mid = (l + r) / 2;
    int ret = INT_MIN;
    if (a <= mid) ret = max(ret, query(2*k, l, mid, a, b));
    if (mid < b) ret = max(ret, query(2*k+1, mid+1, r, a, b));
    return ret;
  }

  void modify(int k, int t, int l, int r, int x) {
    if (l == r) {
      mx_[k] = t;
      return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) modify(2*k, t, l, mid, x);
    else modify(2*k+1, t, mid+1, r, x);
    mx_[k] = max(mx_[2*k], mx_[2*k+1]);
  }
};

const int MAXN = 300010;
int ans[MAXN];
int N, M;
int Y[2*MAXN];

struct Point {
  int x, y;
  int type; // 0 - target, 1 - query
  int id;
  bool operator < (const Point& other) const {
    if (x != other.x) return x < other.x;
    if (y != other.y) return y < other.y;
    if (type != other.type) return type < other.type;
    return id < other.id;
  }
} P[2*MAXN], Q[2*MAXN];

int search(int n, int y) {
  int lo = 0, hi = n;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    if (Y[mid] <=  y) lo = mid;
    else hi = mid;
  }
  return lo;
}

void solve(int n) {
  sort(Q, Q+n);
  for (int i = 0; i < n; i++) {
    Y[i] = Q[i].y;
  }
  sort(Y, Y+n);
  int ny = unique(Y, Y+n) - Y;
  SegmentTree st1(ny), st2(ny);
  for (int i = 0; i < n; i++) {
    int ry = search(ny, Q[i].y);
    if (Q[i].type == 0) {
      st1.modify(Q[i].x + Q[i].y, ry);
      st2.modify(Q[i].x - Q[i].y, ry);
    } else {
      int x = Q[i].x, y = Q[i].y, id = Q[i].id;
      ans[id] = min(ans[id], x + y - st1.query(0, ry));
      ans[id] = min(ans[id], x - y - st2.query(ry, ny-1));
    }
  }
  st1.reset();
  st2.reset();
  for (int i = n-1; i >= 0; i--) {
    int ry = search(ny, Q[i].y);
    if (Q[i].type == 0) {
      st1.modify(- (Q[i].x + Q[i].y), ry);
      st2.modify(- (Q[i].x - Q[i].y), ry);
    } else {
      int x = Q[i].x, y = Q[i].y, id = Q[i].id;
      ans[id] = min(ans[id], -st1.query(ry, ny-1) - (x + y));
      ans[id] = min(ans[id], -st2.query(0, ry) - (x - y));
    }
  }
}

void cdq(int l, int r) {
  if (l == r) return;
  int mid = (l + r) / 2;
  int len = 0;
  for (int i = l; i <= mid; i++) {
    if (P[i].type == 0) Q[len++] = P[i];
  }
  int tmp = len;
  for (int i = mid+1; i <= r; i++) {
    if (P[i].type == 1) Q[len++] = P[i];;
  }
  if (len > tmp) {
    solve(len);
    cdq(l, mid);
    cdq(mid+1, r);
  } else {
    cdq(l, mid);
  }
}

int main() {
  memset(ans, 0x7F, sizeof(ans));
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    P[i] = {x, y, 0, -1};
  }
  int nq = 0;
  for (int i = N; i < N+M; i++) {
    int t, x, y;
    scanf("%d%d%d", &t, &x, &y);
    P[i] = {x, y, t-1, t == 2 ? nq++ : -1};
  }
  cdq(0, N+M-1);
  for (int i = 0; i < nq; i++) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
