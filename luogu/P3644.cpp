// https://www.luogu.com.cn/problem/P3644
// [APIO2015]八邻旁之桥

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;

const int MAXN = 100010;

struct Resident {
  int a, b;
  int ax, bx;
  bool operator < (const Resident& other) const {
    return ax + bx < other.ax + other.bx;
  }
} R[MAXN];

struct RightBoundaryCompare {
  bool operator ()(int i, int j) const {
    return R[i].bx > R[j].bx;
  }
};

struct LeftBoundaryCompare {
  bool operator ()(int i, int j) const {
    return R[i].ax > R[j].ax;
  }
};

using PQ1 = __gnu_pbds::priority_queue<int, RightBoundaryCompare>;
using Iter1 = PQ1::point_iterator;
using PQ2 = __gnu_pbds::priority_queue<int, LeftBoundaryCompare>;
using Iter2 = PQ2::point_iterator;

vector<int> S;
int K, N, M;

int findMid() {
  vector<int> left, right;
  for (int i = 0; i < N; i++) {
    left.push_back(R[i].b);
    right.push_back(-R[i].a);
  }
  sort(left.begin(), left.end());
  sort(right.begin(), right.end());
  int lo = -1;
  int hi = S.size();
  while (lo < hi-1) {
    int mid = (lo + hi) / 2;
    int n1 = upper_bound(left.begin(), left.end(), mid) - left.begin();
    int n2 = lower_bound(right.begin(), right.end(), -mid) -
        right.begin();
    if (n1 < n2) {
      lo = mid;
      continue;
    }
    n1 = lower_bound(left.begin(), left.end(), mid) - left.begin();
    n2 = upper_bound(right.begin(), right.end(), -mid) -
        right.begin();
    if (n1 > n2) {
      hi = mid;
      continue;
    }
    return mid;
  }
  assert(0);
  return -1;
}

int cost(const Resident& r, int x) {
  int ret = r.bx - r.ax;
  if (x < r.ax) ret += 2*(r.ax-x);
  if (x > r.bx) ret += 2*(x-r.bx);
  return ret;
}

void solve1(int64_t base) {
  int pos = S[findMid()];
  int64_t ans = base + N;
  for (int i = 0; i < N; i++) {
    ans += cost(R[i], pos);
  }
  printf("%ld\n", ans);
}

struct IndexData {
  int type;
  int bridge;
  Iter1 it1;
  Iter2 it2;
} I[MAXN];

struct RevertData {
  vector<int> t1, t2;
};

void remove(int idx, set<int>& s, PQ1& p1, PQ2& p2) {
  switch (I[idx].type) {
    case 0:
      s.erase(idx);
      break;
    case 1:
      p1.erase(I[idx].it1);
      break;
    case 2:
      p2.erase(I[idx].it2);
      break;
  }
}

void add(int idx, int px, set<int>& s, PQ1& p1, PQ2& p2) {
  if (R[idx].bx <= px) {
    I[idx].type = 0;
    s.insert(idx);
  } else if (R[idx].ax <= px) {
    I[idx].type = 1;
    I[idx].it1 = p1.push(idx);
  } else {
    I[idx].type = 2;
    I[idx].it2 = p2.push(idx);
  }
}

void shiftLeft(int px, set<int>& s, PQ1& p1, PQ2& p2, RevertData& rev) {
  while (!p2.empty() && R[p2.top()].ax <= px) {
    int idx = p2.top();
    p2.pop();
    I[idx].type = 1;
    I[idx].it1 = p1.push(idx);
    rev.t2.push_back(idx);
  }
  while (!p1.empty() && R[p1.top()].bx <= px) {
    int idx = p1.top();
    p1.pop();
    s.insert(idx);
    I[idx].type = 0;
    rev.t1.push_back(idx);
  }
}

pair<int, int64_t> rightMoveQ(int p, int q, int last,
    set<int>& sp, set<int>& sq,
    PQ1& p1, PQ1& q1, PQ2& p2, PQ2& q2, int64_t curr,
    RevertData& rev) {
  assert(q < M-1);
  bool found = false;
  for (int i = last+1; i < N; i++) {
    if (R[i].ax + R[i].bx > S[p] + S[q+1]) {
      last = i-1;
      found = true;
      break;
    }
    curr -= cost(R[i], S[q]);
    curr += cost(R[i], S[p]);
    assert(I[i].bridge == 1);
    I[i].bridge = 0;
    remove(i, sq, q1, q2);
    add(i, S[p], sp, p1, p2);
  }
  curr += 2LL * sq.size() * (S[q+1]-S[q]);
  curr -= 2LL * q2.size() * (S[q+1]-S[q]);
  shiftLeft(S[q+1], sq, q1, q2, rev);
  if (!found) last = N-1;
  return make_pair(last, curr);
}


pair<int, int64_t> rightMoveP(int p, int q, int last,
    set<int>& sp, set<int>& sq,
    PQ1& p1, PQ1 &q1, PQ2& p2, PQ2& q2, int64_t curr) {
  assert(p < M-1);
  curr += 2LL * sp.size() * (S[p+1]-S[p]);
  curr -= 2LL * p2.size() * (S[p+1]-S[p]);
  bool found = false;
  for (int i = last+1; i < N; i++) {
    if (R[i].ax + R[i].bx > S[p+1] + S[q]) {
      last = i-1;
      found = true;
      break;
    }
    curr -= cost(R[i], S[q]);
    curr += cost(R[i], S[p+1]);
    assert(I[i].bridge == 1);
    I[i].bridge = 0;
    remove(i, sq, q1, q2);
    add(i, S[p+1], sp, p1, p2);
  }
  RevertData rev;
  shiftLeft(S[p+1], sp, p1, p2, rev);
  if (!found) last = N-1;
  return make_pair(last, curr);
}

void revert(const RevertData& rev, int left, int right, int qx,
    set<int>& sp, set<int>& sq, PQ1& p1, PQ1& q1, PQ2& p2, PQ2& q2) {
  for (int x : rev.t1) {
    assert(I[x].type == 0);
    assert(I[x].bridge == 1);
    sq.erase(x);
    I[x].type = 1;
    I[x].it1 = q1.push(x);
  }
  for (int x : rev.t2) {
    assert(I[x].type == 1);
    assert(I[x].bridge == 1);
    q1.erase(I[x].it1);
    I[x].type = 2;
    I[x].it2 = q2.push(x);
  }

  for (int i = right; i >= left; i--) {
    assert(I[i].bridge == 0);
    I[i].bridge = 1;
    remove(i, sp, p1, p2);
    add(i, qx, sq, q1, q2);
  }
}

void solve2(int64_t base) {
  int p = 0, q = 0;
  int64_t curr = 0;
  set<int> sp, sq;
  PQ1 p1, q1;
  PQ2 p2, q2;
  for (int i = 0; i < N; i++) {
    I[i].bridge = 1;
    add(i, S[q], sq, q1, q2);
    curr += cost(R[i], S[q]);
  }
  int64_t ans = curr;
  int last = -1;
  for (p = 0; p < M-1; p++) {
    while (q < M-1) {
      RevertData rev;
      auto pr = rightMoveQ(p, q, last, sp, sq, p1, q1, p2, q2, curr, rev);
      if (pr.second > curr) {
        revert(rev, last+1, pr.first, S[q], sp, sq, p1, q1, p2, q2);
        break;
      }
      last = pr.first;
      curr = pr.second;
      ans = min(ans, curr);
      q++;
    }
    assert(p < q);
    auto pr = rightMoveP(p, q, last, sp, sq, p1, q1, p2, q2, curr);
    last = pr.first;
    curr = pr.second;
    ans = min(ans, curr);
  }
  printf("%ld\n", ans + base + N);
}

int main() {
  scanf("%d%d", &K, &N);
  char line1[5], line2[5];
  int64_t ans = 0;
  {
    int idx = 0;
    for (int i = 0; i < N; i++) {
      int s, t;
      scanf("%s%d%s%d", line1, &s, line2, &t);
      if (line1[0] == line2[0]) {
        ans += abs(t-s);
        continue;
      }
      if (s > t) swap(s, t);
      R[idx++] = {-1, -1, s, t};
      S.push_back(s);
      S.push_back(t);
    }
    N = idx;
  }

  if (N == 0) {
    printf("%ld\n", ans);
    return 0;
  }

  sort(S.begin(), S.end());
  S.erase(unique(S.begin(), S.end()), S.end());
  M = S.size();
  for (int i = 0; i < N; i++) {
    R[i].a = lower_bound(S.begin(), S.end(), R[i].ax) - S.begin();
    R[i].b = lower_bound(S.begin(), S.end(), R[i].bx) - S.begin();
  }

  sort(R, R+N);

  if (K == 1) {
    solve1(ans);
    return 0;
  } else {
    solve2(ans);
  }

  return 0;
}
