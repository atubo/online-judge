// https://www.luogu.com.cn/problem/P3779
// [SDOI2017]龙与地下城

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;
const int MAXN = (1<<24)+10;
double TMP[MAXN], F[MAXN], R[MAXN];
double P[20*200000+10];

int64_t counter;

class Fft {
 public:
  constexpr const static double PI = 3.14159265359;

  static void four1(double* data, int sz, const int isign) {
    int nn = sz / 2;
    int n = nn << 1;
    int j = 1;
    counter += n;
    for (int i = 1; i < n; i+=2) {
      if (j > i) {
        swap(data[j-1], data[i-1]);
        swap(data[j], data[i]);
      }
      int m = nn;
      while (m >= 2 && j > m) {
        j -= m;
        m >>= 1;
      }
      j += m;
    }

    int mmax = 2;
    while (n > mmax) {
      int istep = mmax << 1;
      double theta = isign * (2 * PI / mmax);
      double wtemp = sin(0.5 * theta);
      double wpr = - 2.0 * wtemp * wtemp;
      double wpi = sin(theta);
      double wr = 1.0;
      double wi = 0.0;
      for (int m = 1; m < mmax; m += 2) {
        for (int i = m; i <= n; i += istep) {
          j = i + mmax;
          double tempr = wr * data[j-1] - wi * data[j];
          double tempi = wr * data[j] + wi * data[j-1];
          data[j-1] = data[i-1] - tempr;
          data[j] = data[i] - tempi;
          data[i-1] += tempr;
          data[i] += tempi;
        }
        wr = (wtemp=wr)*wpr - wi*wpi + wr;
        wi = wi*wpr + wtemp*wpi + wi;
      }
      mmax = istep;
    }
  }

  static void innerProduct(double* f, const double* g, int sz) {
    const int n = sz / 2;
    for (int i = 0; i < n; i++) {
      double a = f[2*i], b = f[2*i+1];
      double c = g[2*i], d = g[2*i+1];
      f[2*i] = a*c - b*d;
      f[2*i+1] = a*d + b*c;
    }
  }

  static void square(double *f, int sz) {
    const int n = sz / 2;
    for (int i = 0; i < n; i++) {
      double a = f[2*i], b = f[2*i+1];
      f[2*i] = a*a - b*b;
      f[2*i+1] = 2*a*b;
    }
  }

  static pair<int, int> reduce(double *f, int sz, int maxn) {
    int n = sz / 2;
    for (int i = 0; i < sz; i++) {
      if (i&1) f[i] = 0;
      else f[i] /= n;
    }
    int l = 0;
    for (int i = 0; i <= maxn; i++) {
      if (f[2*i] >= EPS) {
        l = i;
        break;
      }
    }
    int r = n-1;
    for (int i = maxn; i >= 0; i--) {
      if (f[2*i] >= EPS) {
        r = i;
        break;
      }
    }
    for (int i = 0; i < l; i++) {
      f[2*i] = 0;
    }
    for (int i = n-1; i > r; i--) {
      f[2*i] = 0;
    }
    for (int i = l; i <= r; i++) {
      f[2*(i-l)] = f[2*i];
    }
    return make_pair(l, r-l);
  }

  static pair<int, int> polySquare(double *f, int n) {
    int n2 = 1;
    while (n2 < 2*n+1) n2 <<= 1;
    for (int i = n+1; i < n2; i++) {
      f[2*i] = f[2*i+1] = 0;
    }
    const int sz = 2*n2;
    assert(sz < MAXN);
    four1(f, sz, 1);
    square(f, sz);
    four1(f, sz, -1);
    return reduce(f, sz, 2*n);
  }

  static pair<int, int> polyMultiply(
      double *f, int n1, const double *g, int n2) {
    int n = 1;
    while (n < n1+n2+1) n <<= 1;
    const int sz = 2*n;
    assert(sz < MAXN);
    memset(TMP, 0, sz*sizeof(double));
    for (int i = 0; i <= n2; i++) {
      TMP[2*i] = g[2*i];
    }
    for (int i = n1+1; i < n; i++) {
      f[2*i] = f[2*i+1] = 0;
    }
    four1(f, sz, 1);
    four1(TMP, sz, 1);
    innerProduct(f, TMP, sz);
    four1(f, sz, -1);
    return reduce(f, sz, n1+n2);
  }
};

int T;
int X, Y;

pair<int, int> qpow(double *f, int nf, int n) {
  R[0] = 1;
  int nr = 0;
  int br = 0;
  int bf = 0;
  while (n) {
    int b, w;
    if (n & 1) {
      tie(b, w) = Fft::polyMultiply(R, nr, f, nf);
      br = br + bf + b;
      nr = w;
    }
    tie(b, w) = Fft::polySquare(f, nf);
    bf = 2*bf + b;
    nf = w;
    n >>= 1;
  }
  return make_pair(br, nr);
}

double eval(double *p, int l, int r, int x) {
  if (x > r) return 1;
  if (x < l) return 0;
  return p[x-l];
}

void solve() {
  scanf("%d%d", &X, &Y);
  for (int i = 0; i < X; i++) {
    F[2*i] = 1.0/X;
  }
  auto p = qpow(F, X-1, Y);
  P[0] = R[0];
  for (int i = 1; i <= p.second; i++) {
    P[i] = P[i-1] + R[2*i];
  }
  int l = p.first, r = l + p.second;
  for (int i = 0; i < 10; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%.6f\n", eval(P, l, r, b) - eval(P, l, r, a-1));
  }
  memset(P, 0, (p.second+1)*sizeof(int));
}

int main() {
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
