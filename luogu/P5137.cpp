// https://www.luogu.com.cn/problem/P5137
// polynomial

#include <bits/stdc++.h>
using namespace std;

int64_t mul(int64_t a, int64_t b, int64_t p) {
  int64_t c = (long double)(a) * b / p;
  int64_t ans = a * b - c * p;
  if (ans < 0) ans += p;
  if (ans >= p) ans -= p;
  return ans;
}

int64_t add(__int128_t a, __int128_t b, int64_t p) {
  a = a % p;
  b = b % p;
  return (a + b) % p;
}

int64_t sub(__int128_t a, __int128_t b, int64_t p) {
  a = a % p;
  b = b % p;
  return (a + p - b) % p;
}

int64_t solve(int64_t n, int64_t a, int64_t b, int64_t p,
    int64_t& an, int64_t& bn) {
  if (n == 0) {
    an = bn = 1;
    return 1 % p;
  }
  if (n == 1) {
    an = a;
    bn = b;
    return add(a, b, p);
  }
  int64_t am, bm;
  int64_t t = solve(n/2, a, b, p, am, bm);
  int64_t ret;
  if (n & 1) {
    ret = mul(t, add(mul(am, a, p), mul(bm, b, p), p), p);
    an = mul(am, am, p);
    an = mul(an, a, p);
    bn = mul(bm, bm, p);
    bn = mul(bn, b, p);
  } else {
    ret = mul(t, add(am, bm, p), p);
    ret = sub(ret, mul(am, bm, p), p);
    an = mul(am, am, p);
    bn = mul(bm, bm, p);
  }
  return ret;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int64_t n, a, b, p;
    scanf("%ld%ld%ld%ld", &n, &a, &b, &p);
    int64_t an, bn;
    printf("%ld\n", solve(n, a%p, b%p, p, an, bn));
  }
  return 0;
}
