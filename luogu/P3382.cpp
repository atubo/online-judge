// https://www.luogu.com.cn/problem/P3382
// 【模板】三分法

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;
const double EPS = 1e-7;
int N;
double L, R;
double C[MAXN];

double f(double x) {
  double ans = C[N];
  for (int i = N; i >= 1; i--) {
    ans = ans * x + C[i-1];
  }
  return ans;
}

double solve() {
  double l = L, r = R;
  while (l < r-EPS) {
    double x1 = l + (r-l)/3;
    double x2 = l + 2*(r-l)/3;
    double y1 = f(x1);
    double y2 = f(x2);
    if (y1 <= y2) l = x1;
    else r = x2;
  }
  return (l+r)/2;
}

int main() {
  scanf("%d", &N);
  scanf("%lf%lf", &L, &R);
  for (int i = N; i >= 0; i--) {
    scanf("%lf", &C[i]);
  }
  printf("%.5f\n", solve());
  return 0;
}
