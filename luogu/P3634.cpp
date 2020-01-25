// https://www.luogu.com.cn/problem/P3634
// [APIO2012]守卫

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 100010;

struct Range {
  int x, y;
  bool operator < (const Range& other) const {
    if (x != other.x) return x < other.x;
    return y > other.y;
  }
} R0[MAXM], R1[MAXM];

bool X[MAXM];
int L[MAXM], R[MAXM], U[MAXM];
int F[MAXM], G[MAXM];

int N, K, M;

int findIdx0(const vector<Range>& r, int p) {
  if (r[0].y == p) return 0;
  int lo = 0, hi = r.size()-1;
  while (lo < hi-1) {
    int mid = (lo + hi) / 2;
    if (r[mid].y < p) lo = mid;
    else hi = mid;
  }
  return hi;
}

int findIdx1(const vector<Range>& r, int p) {
  if (r[0].y >= p) return -1;
  int lo = 0, hi = r.size() - 1;
  while (lo < hi-1) {
    int mid = (lo + hi) / 2;
    if (r[mid].y < p) lo = mid;
    else hi = mid;
  }
  return lo;
}

int findIdx2(const vector<Range>& r, int p) {
  const int n = r.size();
  if (r[n-1].x <= p) return n;
  int lo = 0, hi = n-1;
  while (lo < hi-1) {
    int mid = (lo + hi) / 2;
    if (r[mid].x > p) hi = mid;
    else lo = mid;
  }
  return hi;
}

int main() {
  scanf("%d%d%d", &N, &K, &M);
  for (int i = 0; i <= N; i++) {
    X[i] = true;
  }
  int cnt0 = 0, cnt1 = 0;
  for (int i = 0; i < M; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if (c == 0) {
      R0[cnt0++] = {a, b};
    } else {
      R1[cnt1++] = {a, b};
    }
  }

  sort(R0, R0+cnt0);
  {
    int l = -1, r = -1;
    for (int i = 0; i < cnt0; i++) {
      int x = R0[i].x;
      int y = R0[i].y;
      if (y <= r) continue;
      if (x <= r) {
        r = y;
        continue;
      }
      if (l >= 0) {
        for (int j = l; j <= r; j++) {
          X[j] = false;
        }
      }
      l = x;
      r = y;
    }
    if (l >= 0) {
      for (int j = l; j <= r; j++) {
        X[j] = false;
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    L[i] = X[i] + L[i-1];
  }
  R[N+1] = L[N] + 1;
  for (int i = N; i >= 1; i--) {
    R[i] = R[i+1] - X[i];
  }

  for (int i = N; i >= 1; i--) {
    U[L[i]] = i;
  }

  if (L[N] == K) {
    for (int i = 1; i <= N; i++) {
      if (X[i]) {
        printf("%d\n", i);
      }
    }
    return 0;
  }

  if (cnt1 == 0) {
    printf("-1\n");
    return 0;
  }

  sort(R1, R1+cnt1);
  for (int i = 0; i < cnt1; i++) {
    R1[i].x = R[R1[i].x];
    R1[i].y = L[R1[i].y];
  }

  vector<Range> r1;
  for (int i = 0; i < cnt1; i++) {
    while (!r1.empty() && r1.back().y >= R1[i].y) r1.pop_back();
    r1.push_back(R1[i]);
  }

  vector<int> pts;
  int last = 0;
  for (int i = 0; i < (int)r1.size(); i++) {
    const auto& r = r1[i];
    if (last < r.x) {
      F[i] = 1;
      pts.push_back(r.y);
      last = r.y;
    }
  }

  last = N+1;
  for (int i = r1.size()-1; i >= 0; i--) {
    const auto& r = r1[i];
    if (last > r.y) {
      G[i] = 1;
      last = r.x;
    }
  }

  for (int i = r1.size()-2; i >= 0; i--) {
    G[i] = G[i+1] + G[i];
  }
  for (int i = 1; i < (int)r1.size(); i++) {
    F[i] = F[i] + F[i-1];
  }

  vector<int> ans;
  for (int p : pts) {
    int idx = findIdx0(r1, p);
    if (r1[idx].x == r1[idx].y) {
      ans.push_back(p);
      continue;
    }
    idx = findIdx1(r1, p-1);
    int f = (idx == -1 ? 0 : F[idx]);
    idx = findIdx2(r1, p-1);
    int g = (idx == (int)r1.size() ? 0 : G[idx]);
    if (f + g + 1 > K) {
      ans.push_back(p);
    }
  }
  if (!ans.empty()) {
    for (int x : ans) {
      printf("%d\n", U[x]);
    }
  } else {
    printf("-1\n");
  }

  return 0;
}
