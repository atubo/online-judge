// https://www.luogu.com.cn/problem/P4525
// 【模板】自适应辛普森法1

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
double A, B, C, D, L, R;

double F(double x) {
  return (C*x + D) / (A*x + B);
}

double simpson(double a, double b) {
  double c = a + (b - a) / 2.0;
  return (b - a) * (F(a) + 4 * F(c) + F(b)) / 6;
}

double asr(double a, double b, double ans) {
  double c = a + (b - a) / 2.0;
  double left = simpson(a, c), right = simpson(c, b);
  if (fabs(left + right - ans) < EPS) {
    return left + right;
  }
  return asr(a, c, left) + asr(c, b, right);
}

int main() {
  scanf("%lf%lf%lf%lf%lf%lf", &A, &B, &C, &D, &L, &R);
  double ans = asr(L, R, simpson(L, R));
  printf("%.6f\n", ans);
  return 0;
}
