// https://www.luogu.com.cn/problem/P4607
// [SDOI2018]反回文串

#include <bits/stdc++.h>
using namespace std;

int64_t mul(__int128_t a, __int128_t b, int64_t mod) {
  return (a * b) % mod;
}

namespace miller_rabin {
const int64_t bs[7] = {2, 3, 5, 7, 11, 61, 24151};
int64_t qpow(int64_t a, int64_t p, int64_t mod) {
  int64_t ret = 1;
  while (p) {
    if (p & 1) ret = mul(ret, a, mod);
    a = mul(a, a, mod);
    p >>= 1;
  }
  return ret;
}

bool tst(int64_t x, int t) {
  for (int64_t p = x - 1; ; p >>= 1) {
    int64_t g = qpow(bs[t], p, x);
    if (g == x-1) return 0;
    if (g != 1) return 1;
    if (p & 1) return 0;
  }
}

bool check(int64_t x) {
  for (int i = 0; i < 7 && bs[i] < x; i++) {
    if (tst(x, i)) return false;
  }
  return true;
}
}

set<int64_t> s;

namespace pollard_rho {
int64_t st;
int64_t mabs(int64_t x, int64_t y) {
  return (x > y) ?  x - y : y - x;
}

int64_t gcd(int64_t a, int64_t b) {
  while (b) {
    int64_t c = a % b;
    a = b;
    b = c;
  }
  return a;
}

int64_t rd(int64_t x, int64_t md) {
  return (mul(x, x, md) + st) % md;
}

int64_t bigr() {
  int64_t ret = 0;
  for (int i = 0; i <= 62; i++) {
    ret += (1LL << i) * (rand()%2);
  }
  return ret;
}

void solve(int64_t x) {
  if (x == 1) return;
  if (miller_rabin::check(x)) {
    s.insert(x);
    return;
  }
  while(1) {
    int64_t x1 = bigr() % x;
    st = rand() % x + 1;
    int64_t g = gcd(x, x1);
    if (g != 1 && g != x) {
      solve(g);
      solve(x/g);
      return;
    }
    int64_t x2 = x1;
    x1 = rd(x1, x);
    int64_t k = 0, tr = 1;
    for (; x1-x2; x1=rd(x1,x),k++) {
      g = gcd(x, mabs(x1, x2));
      if (g != 1 && g != x) {
        solve(g);
        solve(x/g);
        return;
      }
      if (k == tr) {
        x2 = x1;
        tr <<= 1;
      }
    }
  }
}
}

int64_t N, K, P;

int64_t qpow(int64_t a, int64_t n) {
  int64_t ret = 1;
  while (n) {
    if (n & 1) ret = mul(ret, a, P);
    a = mul(a, a, P);
    n >>= 1;
  }
  return ret;
}

vector<int64_t> ys;
unordered_map<int64_t, int64_t> T;
void dfs(int64_t d, int64_t f, set<int64_t>::iterator it) {
  if (it == s.end()) {
    ys.push_back(d);
    T[d] = f;
    return;
  }
  set<int64_t>::iterator it1 = ++it;
  --it;
  dfs(d, f, it1);
  for (int64_t m = *it;; m *= (*it)) {
    dfs(d*m, f*(P - *it%P + 1)%P, it1);
    if ((N/m) % (*it) != 0) break;
  }
}

void solve() {
  scanf("%ld%ld%ld", &N, &K, &P);
  K %= P;
  int64_t ret = 0;
  pollard_rho::solve(N);
  dfs(1, 1, s.begin());
  for (int64_t d : ys) {
    if (d%2 == 1 && (N/d)%2 == 0) continue;
    (ret += ((d%2) ? d:d/2)%P*qpow(K, (d+1)/2)%P*T[N/d]%P) %= P;
  }
  printf("%ld\n", ret);
}

void clear() {
  ys.clear();
  s.clear();
}

int main() {
  srand(66623366);
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
    clear();
  }
  return 0;
}
