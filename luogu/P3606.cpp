// https://www.luogu.com.cn/problem/P3606
// [USACO17JAN]Building a Tall Barn P

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int64_t A[MAXN], B[MAXN];
int N;
int64_t K;

struct Node {
  double v;
  int id;
  bool operator < (const Node& other) const {
    return v < other.v;
  }
  bool operator > (const Node& other) const {
    return other < *this;
  }
};

double decr(int i) {
  assert(B[i] > 1);
  return 1.0 * A[i] / (B[i]-1) - 1.0 * A[i] / B[i];
}

double incr(int i) {
  if (B[i] == 0) return 1e15;
  return 1.0 * A[i] / B[i] - 1.0 * A[i] / (B[i]+1);
}

int64_t calc() {
  double ret = 0;
  for (int i = 0; i < N; i++) {
    assert(B[i] > 0);
    ret += 1.0 * A[i] / B[i];
  }
  return ret + 0.5;
}

void allocate(int64_t m) {
  priority_queue<Node> pq;
  for (int i = 0; i < N; i++) {
    pq.push(Node{incr(i), i});
  }

  while (m > 0) {
    assert(!pq.empty());
    auto node = pq.top();
    pq.pop();
    int i = node.id;
    B[i]++;
    m--;
    pq.push(Node{incr(i), i});
  }
}

void adjust() {
  priority_queue<Node> upper;
  priority_queue<Node, vector<Node>, greater<Node>> lower;
  for (int i = 0; i < N; i++) {
    upper.push(Node{incr(i), i});
    if (B[i] > 1) lower.push(Node{decr(i), i});
  }

  while (!upper.empty() && !lower.empty()) {
    auto u = upper.top();
    auto l = lower.top();
    upper.pop();
    lower.pop();
    if (l.v >= u.v) break;
    int i = u.id;
    int j = l.id;
    B[i]++;
    B[j]--;
    upper.push(Node{incr(i), i});
    if (B[j] > 1) lower.push(Node{decr(j), j});
  }
}

int main() {
  scanf("%d%ld", &N, &K);
  double tot = 0;
  for (int i = 0; i < N; i++) {
    scanf("%ld", &A[i]);
    tot += sqrt(1.0 * A[i]);
  }
  int64_t assigned = 0;
  for (int i = 0; i < N; i++) {
    B[i] = int64_t(sqrt(1.0 * A[i]) / tot * K);
    assigned += B[i];
  }
  allocate(K - assigned);
  adjust();
  int64_t ans = calc();
  printf("%ld\n", ans);
  return 0;
}
