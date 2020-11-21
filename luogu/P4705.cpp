// https://www.luogu.com.cn/problem/P4705
// 玩游戏

#include <bits/stdc++.h>
using namespace std;

class Ntt2 {
 public:
  // get the first power of 2 that is larger than n
  static int getlen(int n) {
    return 1 << (32 - __builtin_clz(n));
  }

  Ntt2(int p, int g, int n) : p_(p), g_(g) {
    cap_ = getlen(2*n);
    alloc();
    init();
  }

  ~Ntt2() {
    dealloc();
  }

  void ntt(int* a, int op, int n) const {
    // length must be power of 2
    assert(__builtin_popcount(n) == 1);
    int j = 0;
    for (int i = 0; i < n; i++) {
      if (j > i) {
        swap(a[i], a[j]);
      }
      int m = (n >> 1);
      while (m >= 2 && j >= m) {
        j -= m;
        m >>= 1;
      }
      j += m;
    }

    for (int i = 1; i < n; i<<=1) {
      for (j = 0; j < n; j+=i<<1) {
        for (int k = 0; k < i; k++) {
          int64_t t = (op == 1 ? 1LL*w_[2*i+k] : 1LL*w_[4*i-k]) * a[i+j+k] % p_;
          a[i+j+k] = (a[j+k]-t+p_)%p_;
          a[j+k] = (a[j+k]+t)%p_;
        }
      }
    }

    if (op == -1) {
      int64_t inv = p_ - (p_ - 1) / n;
      for (int i = 0; i < n; i++) a[i] = a[i] * inv % p_;
    }
  }

  // b must be initialized to 0 before calling
  void inverse(const int *a, int *b, int n) const {
    if (n == 1) {
      b[0] = pow(a[0], p_-2);
      return;
    }
    inverse(a, b, (n+1)/2);
    int lim = 1;
    while (lim < 2*n) lim <<= 1;
    memcpy(temp_, a, n * sizeof(int));
    memset(temp_+n, 0, (lim-n) * sizeof(int));
    ntt(temp_, 1, lim);
    ntt(b, 1, lim);
    for (int i = 0; i < lim; i++) {
      temp_[i] = 1LL * b[i] * (2 - 1LL * b[i] * temp_[i] % p_ + p_) % p_;
    }
    ntt(temp_, -1, lim);
    memcpy(b, temp_, n * sizeof(int));
    memset(b+n, 0, (lim-n) * sizeof(int));
  }

  int pow(int64_t x, int y) const {
    int64_t ans = 1;
    while (y) {
      if (y & 1) ans = ans * x % p_;
      x = x * x % p_;
      y >>= 1;
    }
    return ans;
  }

 private:
  int p_, g_;
  int cap_;
  int* temp_;
  int* w_;

  void alloc() {
    temp_ = new int[cap_]{};
    w_ = new int[cap_]{};
  }

  void dealloc() {
    delete[] temp_;
    delete[] w_;
  }

  void init() {
    // initialize the powers of g
    // if p = c * 2^k + 1
    // w[i] = 1 if i is power of 2
    // w[i] = g ^ (j * c * 2 ^ (k - n)) if i = j + 2^n
    int n = __builtin_ctz(cap_ >> 1);
    w_[1<<n] = 1;
    int wn = pow(g_, (p_-1) >> n);
    for (int i = (1<<n)+1; i < cap_; i++) {
      w_[i] = (1LL * w_[i-1] * wn) % p_;
    }
    for (int i = (1<<n)-1; i; --i) {
      w_[i] = w_[i<<1];
    }
  }

};

const int P = 998244353;
const int MAXN = 262147;
int len[MAXN];
int inv[MAXN], fac[MAXN], ifac[MAXN];

void init(int n) {
  inv[1] = 1;
  fac[0] = fac[1] = 1;
  ifac[0] = ifac[1] = 1;
  for (int i = 2; i <= n; i++) {
    inv[i] = 1LL * (P - P/i) * inv[P%i] % P;
    fac[i] = 1LL * fac[i-1] * i % P;
    ifac[i] = 1LL * ifac[i-1] * inv[i] % P;
  }
}

void log(const Ntt2& ntt, int *f, int n) {
  static int g[MAXN];
  int lim = Ntt2::getlen(2*n);
  memset(g, 0, lim*sizeof(int));
  ntt.inverse(f, g, n);
  memset(g+n, 0, (lim-n) * sizeof(int));
  for (int i = 0; i < n; i++) {
    f[i] = 1LL * f[i+1] * (i+1) % P;
  }
  ntt.ntt(f, 1, lim);
  ntt.ntt(g, 1, lim);
  for (int i = 0; i < lim; i++) {
    f[i] = 1LL * f[i] * g[i] % P;
  }
  ntt.ntt(f, -1, lim);
  for (int i = n-1; i; i--) {
    f[i] = P - f[i-1];
  }
  f[0] = 0;
  memset(f+n, 0, (lim-n) * sizeof(int));
}

void solve(const Ntt2& ntt, int l, int r, int k, const int* a, int *ret) {
  len[k] = r - l + 1;
  if (l == r) {
    ret[0] = 1;
    ret[1] = P - a[l];
    return;
  }
  int lim = Ntt2::getlen(len[k]+1);
  int f[lim], g[lim];
  int mid = (l + r) / 2;
  solve(ntt, l, mid, 2*k, a, f);
  solve(ntt, mid+1, r, 2*k+1, a, g);
  memset(f+len[2*k]+1, 0, (lim-len[2*k]-1)*sizeof(int));
  memset(g+len[2*k+1]+1, 0, (lim-len[2*k+1]-1)*sizeof(int));
  ntt.ntt(f, 1, lim);
  ntt.ntt(g, 1, lim);
  for (int i = 0; i < lim; i++) f[i] = 1LL * f[i] * g[i] % P;
  ntt.ntt(f, -1, lim);
  memcpy(ret, f, (len[k]+1) * sizeof(int));
}

int A[MAXN], B[MAXN], F[MAXN], G[MAXN];

int main() {
  Ntt2 ntt(998244353, 3, 1<<18);
  init(200000);
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", &A[i]);
  }
  for (int i = 0; i < m; i++) {
    scanf("%d", &B[i]);
  }
  int k;
  scanf("%d", &k);
  int t = k;
  k = max(max(k, n), m);
  solve(ntt, 0, n-1, 1, A, F);
  solve(ntt, 0, m-1, 1, B, G);
  log(ntt, F, k+1);
  log(ntt, G, k+1);
  F[0] = n; G[0] = m;
  for (int i = 2; i <= k; i++) {
    F[i] = 1LL * F[i] * ifac[i] % P;
    G[i] = 1LL * G[i] * ifac[i] % P;
  }
  int lim = Ntt2::getlen(2*k);
  ntt.ntt(F, 1, lim);
  ntt.ntt(G, 1, lim);
  for (int i = 0; i < lim; i++) {
    F[i] = 1LL * F[i] * G[i] % P;
  }
  ntt.ntt(F, -1, lim);
  int tmp = ntt.pow(1LL*n*m%P, P-2);
  for (int i = 0; i <= k; i++) {
    F[i] = 1LL * F[i] * fac[i] % P * tmp % P;
  }
  for (int i = 1; i <= t; i++) {
    printf("%d\n", F[i]);
  }

  return 0;
}
