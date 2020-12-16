// https://www.luogu.com.cn/problem/P4747
// [CERC2017]Intrinsic Interval

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
  int N;
  int *mx_, *rp_, *tag_;

 public:
  SegmentTree(int N_): N(N_) {
    mx_ = new int[4*N+1]{};
    rp_ = new int[4*N+1]{};
    tag_ = new int[4*N+1]{};
  }

  ~SegmentTree() {
    delete[] mx_;
    delete[] rp_;
    delete[] tag_;
  }

  void build() {
    build(1, 1, N);
  }

  void increment(int a, int b) {
    increment(1, 1, N, a, b);
  }

  int query(int p, int w) {
    return query(1, 1, N, p, w);
  }

 private:
  void pushUp(int k) {
    if (mx_[2*k+1] >= mx_[2*k]) {
      mx_[k] = mx_[2*k+1];
      rp_[k] = rp_[2*k+1];
    } else {
      mx_[k] = mx_[2*k];
      rp_[k] = rp_[2*k];
    }
  }

  void pushDown(int k) {
    if (!tag_[k]) return;
    mx_[2*k] += tag_[k];
    tag_[2*k] += tag_[k];
    mx_[2*k+1] += tag_[k];
    tag_[2*k+1] += tag_[k];
    tag_[k] = 0;
  }

  void build(int k, int l, int r) {
    if (l == r) {
      mx_[k] = rp_[k] = l;
      return;
    }
    int mid = (l + r) / 2;
    build(2*k, l, mid);
    build(2*k+1, mid+1, r);
    pushUp(k);
  }

  void increment(int k, int l, int r, int a, int b) {
    if (a <= l && r <= b) {
      mx_[k]++;
      tag_[k]++;
      return;
    }
    pushDown(k);
    int mid = (l + r) / 2;
    if (a <= mid) increment(2*k, l, mid, a, b);
    if (mid < b) increment(2*k+1, mid+1, r, a, b);
    pushUp(k);
  }

  int query(int k, int l, int r, int p, int w) {
    if (mx_[k] < w) return 0;
    if (r <= p) return rp_[k];
    pushDown(k);
    int mid = (l + r) / 2;
    if (mid < p && mx_[2*k+1] >= w) {
      int t = query(2*k+1, mid+1, r, p, w);
      if (t) return t;
    }
    return query(2*k, l, mid, p, w);
  }
};

const int MAXN = 100010;
int N, M;
int A[MAXN], P[MAXN], AL[MAXN], AR[MAXN];
stack<pair<int, int>> D[MAXN];
priority_queue<pair<int, int>> S;

bool solve(SegmentTree& st, int r) {
  if (S.empty()) return 0;
  int ql = S.top().first;
  int qid = S.top().second;
  AL[qid] = st.query(ql, r);
  if (!AL[qid]) return 0;
  AR[qid] = r;
  S.pop();
  return 1;
}

int main() {
  scanf("%d", &N);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
    P[A[i]] = i;
  }
  scanf("%d", &M);
  for (int i = 0; i < M; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    D[y].push(make_pair(x, i));
  }

  SegmentTree st(N);
  st.build();
  for (int i = 1; i <= N; i++) {
    if (A[i] > 1 && P[A[i]-1] < i) st.increment(1, P[A[i]-1]);
    if (A[i] < N && P[A[i]+1] < i) st.increment(1, P[A[i]+1]);
    while (!D[i].empty()) {
      S.push(D[i].top());
      D[i].pop();
    }
    while (solve(st, i)) {}
  }

  for (int i = 0; i < M; i++) {
    printf("%d %d\n", AL[i], AR[i]);
  }

  return 0;
}
