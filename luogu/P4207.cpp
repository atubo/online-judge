// https://www.luogu.com.cn/problem/P4207
// [NOI2005]月下柠檬树

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-7;
const int MAXN = 510;
int N;
struct Circle {
  double x, r;
} C[MAXN];

struct Line {
  double k, b, left, right;
} L[MAXN];

double leg(double a, double b) {
  return sqrt(a*a - b*b);
}

void getTan(int x, int y) {
  if (fabs(C[x].r - C[y].r) < EPS) {
    L[x].left = C[x].x;
    L[x].right = C[y].x;
    L[x].k = 0;
    L[x].b = C[x].r;
    return;
  }
  double dx = C[y].x - C[x].x;
  double dr = fabs(C[x].r - C[y].r);
  double ly, ry;
  if (C[x].r > C[y].r) {
    L[x].left = C[x].x + C[x].r * dr / dx;
    L[x].right = C[y].x + (L[x].left - C[x].x) * C[y].r / C[x].r;
    ly = leg(C[x].r, L[x].left - C[x].x);
    ry = leg(C[y].r, L[x].right - C[y].x);
    L[x].k = (ly - ry) / (L[x].left - L[x].right);
    L[x].b = ly - L[x].left * L[x].k;
  } else {
    L[x].right = C[y].x - C[y].r * dr / dx;
    L[x].left = C[x].x - (C[y].x - L[x].right) * C[x].r / C[y].r;
    ly = leg(C[x].r, L[x].left - C[x].x);
    ry = leg(C[y].r, L[x].right - C[y].x);
    L[x].k = (ly - ry) / (L[x].left - L[x].right);
    L[x].b = ly - L[x].left * L[x].k;
  }
}

double F(double x) {
  double ans = 0;
  for (int i = 1; i <= N; i++) {
    if (x < C[i].x + C[i].r && x > C[i].x - C[i].r) {
      ans = max(ans, leg(C[i].r, x - C[i].x));
    }
  }
  for (int i = 1; i <= N; i++) {
    if (x >= L[i].left && x <= L[i].right) {
      ans = max(ans, L[i].b + L[i].k * x);
    }
  }
  return ans;
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
  } else {
    return asr(a, c, left) + asr(c, b, right);
  }
}

int main() {
  double alpha;
  scanf("%d%lf", &N, &alpha);
  alpha = 1.0 / tan(alpha);
  double last = 0;
  for (int i = 1; i <= N+1; i++) {
    scanf("%lf", &C[i].x);
    C[i].x *= alpha;
    C[i].x += last;
    last = C[i].x;
  }
  for (int i = 1; i <= N; i++) {
    scanf("%lf", &C[i].r);
  }
  N++;
  C[N].r = 0;
  for (int i = 1; i <= N-1; i++) {
    getTan(i, i+1);
  }
  double ll = C[1].x - C[1].r, rr = C[N].x;
  for (int i = 1; i <= N; i++) {
    rr = max(rr, C[i].x + C[i].r);
    ll = min(ll, C[i].x - C[i].r);
  }
  printf("%.2lf\n", 2.0 * asr(ll, rr, simpson(ll, rr)));

  return 0;
}
