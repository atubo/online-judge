// https://www.luogu.com.cn/problem/P2179
// [NOI2012]骑行川藏

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;
const double EPS = 1e-9;

struct Road {
  double s, k, v;
} R[MAXN];

int N;
double E;

double f(double v, double k, double c) {
  return k * (v - c) * v * v;
}

double findHi(double k, double c, double lambda) {
  double v = c;
  while (f(v, k, c) <= lambda) v = 10 * v;
  return v;
}

double solve(int i, long double lambda) {
  double k = R[i].k;
  double c = R[i].v;
  double lo = max(c, 0.0), hi = 1e5;
  while (lo < hi - 0.01*EPS*hi) {
    double mid = (lo + hi) / 2;
    if (k * (mid - c) * mid * mid > lambda) hi = mid;
    else lo = mid;
  }
  return (lo + hi) / 2;
}

double workRoad(int i, double v) {
  double s = R[i].s;
  double k = R[i].k;
  double c = R[i].v;
  return k * (v - c) * (v - c) * s;
}

double work(double lambda) {
  double ret = 0;
  for (int i = 0; i < N; i++) {
    double v = solve(i, lambda);
    ret += workRoad(i, v);
  }
  return ret;
}

double ride(double lambda) {
  double ret = 0;
  for (int i = 0; i < N; i++) {
    double v = solve(i, lambda);
    ret += R[i].s / v;
  }
  return ret;
}

int main() {
  scanf("%d%lf", &N, &E);
  for (int i = 0; i < N; i++) {
    double s, k, v;
    scanf("%lf%lf%lf", &s, &k, &v);
    R[i] = {s, k, v};
  }
  double lo = 0, hi = 1e5;
  while (lo < hi - EPS) {
    double mid = (lo + hi) / 2;
    double e = work(mid);
    if (e > E) hi = mid;
    else lo = mid;
  }
  printf("%.6f\n", ride((lo + hi) / 2));
  return 0;
}
