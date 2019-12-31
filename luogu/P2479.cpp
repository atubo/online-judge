// https://www.luogu.com.cn/problem/P2479
// [SDOI2010]捉迷藏

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int *val;

public:
    SegmentTree(int N_): N(N_) {
        val = new int[4*N+1]{};
        reset();
    }

    ~SegmentTree() {
        delete[] val;
    }
    // insert t to position a
    void update(int t, int a) {
        update(1, t, 1, N, a);
    }

    // query range sum in [a, b]
    int query(int a, int b) {
        return query(1, 1, N, a, b);
    }

    void reset() {
      for (int i = 0; i <= 4*N; i++) {
        val[i] = INT_MIN;
      }
    }

private:
    // insert t to position a, current node range is [l, r]
    void update(int k, int t, int l, int r, int a) {
        val[k] = (val[k] > t ? val[k] : t);
        if (l == r) return;
        int mid = (l + r) / 2;
        if (a <= mid) update(2*k, t, l, mid, a);
        else          update(2*k+1, t, mid+1, r, a);
    }

    // query range sum in [a, b], current node is [l, r]
    int query(int k, int l, int r, int a, int b) {
        if (!k) return INT_MIN;
        if (b < l || a > r) return INT_MIN;
        if (a <= l && r <= b) return val[k];
        int ret = INT_MIN;
        int mid = (l + r) / 2;
        if (a <= mid) {
            int t = query(2*k, l, mid, a, b);
            if (t > ret) ret = t;
        }
        if (mid < b) {
            int t = query(2*k+1, mid+1, r, a, b);
            if (t > ret) ret = t;
        }
        return ret;
    }
};

const int MAXN = 100010;

struct Point {
  int x, y;
  int idy;
  bool operator < (const Point& other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
} P[MAXN];

int R1[MAXN], R2[MAXN]; // max and min distance

int N;

int main() {
  vector<int> sorty;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d%d", &P[i].x, &P[i].y);
    sorty.push_back(P[i].y);
  }
  sort(sorty.begin(), sorty.end());
  sorty.erase(unique(sorty.begin(), sorty.end()), sorty.end());
  const int M = sorty.size();
  SegmentTree st1(M), st2(M), st3(M), st4(M);
  sort(P, P+N);
  for (int i = 0; i < N; i++) {
    P[i].idy = lower_bound(sorty.begin(), sorty.end(), P[i].y)
        - sorty.begin() + 1;
  }
  for (int i = 0; i < N; i++) {
    R1[i] = INT_MIN;
    R2[i] = INT_MAX;
    int idy = P[i].idy;
    int x1 = st1.query(1, idy);
    if (x1 > INT_MIN) R2[i] = min(R2[i], P[i].x + P[i].y - x1);
    x1 = st2.query(1, idy);
    if (x1 > INT_MIN) R1[i] = max(R1[i], P[i].x + P[i].y + x1);
    x1 = st3.query(idy, M);
    if (x1 > INT_MIN) R1[i] = max(R1[i], P[i].x - P[i].y + x1);
    x1 = st4.query(idy, M);
    if (x1 > INT_MIN) R2[i] = min(R2[i], P[i].x - P[i].y - x1);
    st1.update(P[i].x+P[i].y, idy);
    st2.update(-P[i].x-P[i].y, idy);
    st3.update(P[i].y-P[i].x, idy);
    st4.update(P[i].x-P[i].y, idy);
  }

  st1.reset(); st2.reset(); st3.reset(); st4.reset();
  for (int i = N-1; i >= 0; i--) {
    int idy = P[i].idy;
    int x1 = st1.query(idy, M);
    if (x1 > INT_MIN) R1[i] = max(R1[i], x1 - P[i].x - P[i].y);
    x1 = st2.query(idy, M);
    if (x1 > INT_MIN) R2[i] = min(R2[i], -x1 - P[i].x - P[i].y);
    x1 = st3.query(1, idy);
    if (x1 > INT_MIN) R1[i] = max(R1[i], x1 - P[i].x + P[i].y);
    x1 = st4.query(1, idy);
    if (x1 > INT_MIN) R2[i] = min(R2[i], -x1 - P[i].x + P[i].y);
    st1.update(P[i].x+P[i].y, idy);
    st2.update(-P[i].x-P[i].y, idy);
    st3.update(P[i].x-P[i].y, idy);
    st4.update(P[i].y-P[i].x, idy);
  }

  int ans = INT_MAX;
  for (int i = 0; i < N; i++) {
    ans = min(ans, R1[i]-R2[i]);
  }
  printf("%d\n", ans);

  return 0;
}
