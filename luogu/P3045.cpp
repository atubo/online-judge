// https://www.luogu.com.cn/problem/P3045
// [USACO12FEB]Cow Coupons G

#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/priority_queue.hpp>

const int MAXN = 50010;
int N, K;
int64_t M;

struct Cow {
  int c, p;
  bool operator < (const Cow& other) const {
    if (c != other.c) return c < other.c;
    return p < other.p;
  }
} C[MAXN];

struct CmpByDiff {
  bool operator() (int i, int j) const {
    return (C[i].p - C[i].c) < (C[j].p - C[j].c);
  }
};

struct CmpByDiff2 {
  bool operator() (int i, int j) const {
    return (C[i].p - C[i].c) > (C[j].p - C[j].c);
  }
};

struct CmpByPrice {
  bool operator() (int i, int j) const {
    return C[i].p < C[j].p;
  }
};

struct CmpByCoupon {
  bool operator() (int i, int j) const {
    return C[i].c < C[j].c;
  }
};

int64_t P[MAXN];

class PQueue {
  using PQ1 = __gnu_pbds::priority_queue<int, CmpByCoupon>;
  using PQ2 = __gnu_pbds::priority_queue<int, CmpByPrice>;
  using PQ3 = __gnu_pbds::priority_queue<int, CmpByDiff>;
  using PQ4 = __gnu_pbds::priority_queue<int, CmpByDiff2>;
  using Iter1 = PQ1::point_iterator;
  using Iter2 = PQ2::point_iterator;
  using Iter3 = PQ3::point_iterator;
  using Iter4 = PQ4::point_iterator;
 public:
  PQueue(int n) {
    it1_.resize(n);
    it2_.resize(n);
    it3_.resize(n);
    it4_.resize(n);
  }

  void push(int c) {
    it1_[c] = q1_.push(c);
    it2_[c] = q2_.push(c);
    it3_[c] = q3_.push(c);
    it4_[c] = q4_.push(c);
  }

  void pop(int x) {
    q1_.erase(it1_[x]);
    q2_.erase(it2_[x]);
    q3_.erase(it3_[x]);
    q4_.erase(it4_[x]);
  }

  int topByCoupon() {
    return q1_.top();
  }

  int topByPrice() {
    return q2_.top();
  }

  int topByDiff() {
    return q3_.top();
  }

  int bottomByDiff() {
    return q4_.top();
  }

  int size() const {
    return q1_.size();
  }
 private:
  PQ1 q1_;
  PQ2 q2_;
  PQ3 q3_;
  PQ4 q4_;
  vector<Iter1> it1_;
  vector<Iter2> it2_;
  vector<Iter3> it3_;
  vector<Iter4> it4_;
};

int diff1(const Cow& c, PQueue& qc, PQueue& qp) {
  const Cow& tc = C[qc.topByCoupon()];
  const Cow& tp = C[qp.topByDiff()];
  return (tp.p - tp.c) - (c.p - tc.c);
}

int diff2(const Cow& c, PQueue& qp) {
  const Cow& tp = C[qp.topByPrice()];
  return tp.p - c.p;
}

bool feasible(int n) {
  if (n <= K) return P[n] <= M;
  PQueue qc(N+1), qp(N+1);
  int64_t cost = 0;
  for (int i = 1; i <= K; i++) {
    qc.push(i);
    cost += C[i].c;
  }
  for (int i = K+1; i <= N; i++) {
    if (qp.size() < n-K) {
      int j = qc.bottomByDiff();
      if (C[i].p - C[i].c > C[j].p - C[j].c) {
        cost += C[j].p - C[j].c + C[i].c;
        qc.pop(j);
        qc.push(i);
        qp.push(j);
      } else {
        cost += C[i].p;
        qp.push(i);
      }
    } else {
      int d1 = diff1(C[i], qc, qp);
      int d2 = diff2(C[i], qp);
      if (max(d1, d2) > 0) {
        if (d1 > d2) {
          cost -= d1;
          int k = qp.topByDiff();
          qp.pop(k);
          qp.push(i);
          int j = qc.topByCoupon();
          qc.pop(j);
          qc.push(k);
        } else {
          cost -= d2;
          int k = qp.topByPrice();
          qp.pop(k);
          qp.push(i);
        }
      }
    }
  }

  return cost <= M;
}

int main() {
  scanf("%d%d%ld", &N, &K, &M);
  for (int i = 1; i <= N; i++) {
    scanf("%d%d", &C[i].p, &C[i].c);
  }
  sort(C+1, C+N+1);
  for (int i = 1; i <= K; i++) {
    P[i] = P[i-1] + C[i].c;
  }
  int lo = 0, hi = N+1;
  while (lo < hi-1) {
    int mid = (lo + hi) / 2;
    if (feasible(mid)) lo = mid;
    else hi = mid;
  }
  printf("%d\n", lo);
  return 0;
}
