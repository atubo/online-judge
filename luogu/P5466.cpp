// https://www.luogu.com.cn/problem/P5466
// [PKUSC2018]神仙的游戏

#include <bits/stdc++.h>
using namespace std;

class Ntt {
public:
    static int primeRoot(int p) {
        vector<int> factors;
        int x = p - 1;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                factors.push_back((p-1)/i);
                while (x % i == 0) x /= i;
            }
        }
        if (x > 1) factors.push_back((p-1)/x);

        for (int i = 2; ; i++) {
            bool ok = true;
            for (int y: factors) {
                if (pow(i, y, p) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) return i;
        }
        return -1;
    }

    static void ntt(vector<int> &a, int op, int p, int g) {
        // length should be power of 2
        const int n = a.size();
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
            int64_t wn = pow(g, op==1?(p-1)/(2*i):p-1-(p-1)/(2*i), p), t, w;
            for (j = 0; j < n; j+=i<<1) {
                w = 1;
                for (int k = 0; k < i; k++) {
                    t = w*a[i+j+k]%p; w = w*wn%p;
                    a[i+j+k] = (a[j+k]-t+p)%p;
                    a[j+k] = (a[j+k]+t)%p;
                }
            }
        }

        if (op == -1) {
            int64_t inv = pow(n, p-2, p);
            for (int i = 0; i < n; i++) a[i] = a[i] * inv % p;
        }
    }

    static vector<int> innerProduct(const vector<int> &a, const vector<int>& b,
                                    int p) {
        const int n = a.size();
        vector<int> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = int64_t(a[i]) * b[i] % p;
        }
        return c;
    }

    static vector<int> conv(vector<int> a, vector<int> b,
                            int p, int g) {
        ntt(a, 1, p, g);
        ntt(b, 1, p, g);
        vector<int> c = innerProduct(a, b, p);
        ntt(c, -1, p, g);
        return c;
    }

    static vector<int> polynomialInverse(int deg,
                                         const vector<int> &a,
                                         int prime, int g) {
        if (deg == 1) {
            vector<int> b(2);
            b[0] = pow(a[0], prime-2, prime);
            return b;
        }
        auto b = polynomialInverse((deg+1)>>1, a, prime, g);
        int p = 1;
        while (p < deg << 1) p <<= 1;
        vector<int> tmp(p);
        copy(a.begin(), a.begin()+deg, tmp.begin());
        ntt(tmp, 1, prime, g);
        b.resize(p);
        ntt(b, 1, prime, g);
        for (int i = 0; i < p; i++) {
            b[i] = (2LL - int64_t(tmp[i]) * b[i] % prime) * b[i] % prime;
            if (b[i] < 0) b[i] += prime;
        }
        ntt(b, -1, prime, g);
        fill(b.begin()+deg, b.begin()+p, 0);
        return b;
    }

    static vector<int> bernoulli(int n, int p, int g) {
        // assume n is power of 2
        vector<int> a(n), f(n+1), nf(n+1);
        f[0] = 1;
        for (int i = 1; i <= n; i++) f[i] = 1LL * f[i-1] * i % p;
        nf[n] = pow(f[n], p-2, p);
        for (int i = n-1; i >= 0; i--) {
            nf[i] = 1LL * nf[i+1] * (i+1) % p;
        }
        for (int i = 0; i < n; i++) a[i] = nf[i+1];
        auto b = polynomialInverse(n, a, p, g);
        for (int i = 0; i < n; i++) {
            b[i] = 1LL * b[i] * f[i] % p;
        }
        return b;
    }

private:
    static int pow(int64_t x, int y, int m) {
        int64_t ans = 1;
        while (y) {
            if (y & 1) ans = ans * x % m;
            x = x * x % m;
            y >>= 1;
        }
        return ans;
    }
};

const int MAXN = 500010;
char S[MAXN];
bool E[MAXN];

int main() {
  scanf("%s", S);
  int n = strlen(S);
  int len = 1;
  while (len <= 4*n) len <<= 1;
  vector<int> a(len), b(len);

  for (int i = 0; i < n; i++) {
    a[i+n] = (S[i] == '1');
    b[n-i] = (S[i] == '0');
  }

  auto c = Ntt::conv(a, b, 998244353, 3);

  for (int i = 1; i < n; i++) {
    E[i] = c[2*n-i] | c[2*n+i];
  }

  int64_t ans = 0;
  for (int l = 1; l < n; l++) {
    int d = n - l;
    bool ok = true;
    for (int j = d; j < n; j += d) {
      if (E[j]) {
        ok = false;
        break;
      }
    }
    if (ok) ans ^=  (1LL*l*l);
  }
  ans ^= (1LL*n*n);
  printf("%ld\n", ans);

  return 0;
}
