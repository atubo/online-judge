// https://www.luogu.org/problem/P1820
// 寻找AP数

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1500000000;

int P[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

struct Data {
  int cnt[10];
  int64_t nf;
  int64_t x;
  bool operator > (const Data& other) const {
    if (nf != other.nf) return nf > other.nf;
    return x > other.x;
  }
};

namespace std {
template <> struct hash<std::pair<int64_t, int64_t>> {
    inline size_t operator()(const std::pair<int64_t, int64_t> &v) const {
        std::hash<int> int_hasher;
        return int_hasher(v.first) ^ int_hasher(v.second);
    }
};

}

bool isBetter(const Data& d, const pair<int64_t, int64_t>& b) {
  assert(d.nf >= b.second);
  return (d.nf >= b.second && d.x <= b.first);
}

vector<Data> candidate(const Data& d) {
  vector<Data> ret;
  for (int i = 0; i < 10; i++) {
    Data d2;
    for (int j = 0 ; j < 10; j++) d2.cnt[j] = d.cnt[j];
    d2.nf = d.nf;
    d2.x = d.x;

    if (i == 0 || d2.cnt[i] < d2.cnt[i-1]) {
      if (d2.x * P[i] > MAXN) break;
      d2.x *= P[i];
      d2.nf = d2.nf/(d2.cnt[i]+1) * (d2.cnt[i]+2);
      d2.cnt[i]++;
      ret.push_back(std::move(d2));
    }
  }
  return ret;
}

int main() {
  priority_queue<Data, vector<Data>, greater<Data>> q;
  vector<pair<int64_t, int64_t>> lst;
  q.push({{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 1, 1});
  unordered_set<pair<int64_t, int64_t>> seen;
  seen.insert(make_pair(1LL, 1LL));
  while (!q.empty()) {
    auto d = q.top();
    q.pop();
    while (!lst.empty() && isBetter(d, lst.back())) lst.pop_back();
    if (lst.empty() || d.nf > lst.back().second) {
      lst.push_back(make_pair(d.x, d.nf));
    }
    for (const auto& d2: candidate(d)) {
      if (seen.count({d2.nf, d2.x}) == 0) {
        q.push(d2);
        seen.insert({d2.nf, d2.x});
      }
    }
  }
  vector<int> lookup;
  for (const auto& p: lst) {
    lookup.push_back(p.first);
  }

  int x;
  while (scanf("%d", &x) == 1) {
    if (x == 0) {
      printf("0\n");
      continue;
    }
    auto it = upper_bound(lookup.begin(), lookup.end(), x);
    if (it == lookup.end()) {
      printf("%d\n", lookup.back());
    }
    printf("%d\n", *(--it));
  }

  return 0;
}
