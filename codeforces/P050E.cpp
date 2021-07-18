// https://codeforces.com/problemset/problem/50/E
// Square Equation Roots

#include <bits/stdc++.h>
using namespace std;

int sqrt(int m) {
  int lo = 1, hi = m;
  while (lo < hi - 1) {
    int mid = (lo + hi) / 2;
    if (1LL * mid * mid <= m) lo = mid;
    else hi = mid;
  }
  return lo;
}

__int128_t sumSq(int n) {
  return __int128_t(n) * (2*n + 1) * (n + 1) / 6;
}

__int128_t sum(int n) {
  return __int128_t(n) * (n + 1) / 2;
}

int findk(int64_t b, int64_t m) {
  int64_t lo = 0, hi = b;
  while (lo < hi - 1) {
    int64_t mid = (lo + hi) / 2;
    if (b*b - mid*mid <= m) hi = mid;
    else lo = mid;
  }
  return hi;
}

__int128_t countNonInt(int n, int m) {
  if (1LL*m >= 1LL*n*n) {
    return (sumSq(n) - sum(n)) * 2;
  }
  int ms = sqrt(m);
  __int128_t ret = (sumSq(ms) - sum(ms)) * 2;
  for (int b = ms + 1; b <= n; b++) {
    int k = findk(b, m);
    ret += 2 * (m - b + k);
  }

  return ret;
}

__int128_t countInt(int n, int m) {
  int x0 = min(2*(n-1), m/2);
  int ret = x0 / 2;
  x0 = min(2*n-1, m);
  ret += (x0 + 1) / 2;
  return ret;
}

string toString(__int128_t x) {
  if (x == 0) return "0";
  string ret;
  while (x != 0) {
    ret.push_back('0' + (x % 10));
    x /= 10;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}


int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  __int128_t x = countNonInt(n, m);
  __int128_t y = countInt(n, m);
  __int128_t ret = x + y;
  cout << toString(ret) << endl;
  return 0;
}
