// https://www.luogu.com.cn/problem/P1222
// 三角形

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2010;
int N;
const double EPS = 1e-9;
struct Segment {
  double a, b;
  bool operator < (const Segment& other) const {
    if (a != other.a) return a < other.a;
    return b < other.b;
  }
} S[MAXN];

struct Tri {
  int x, y, r;
} T[MAXN];

double f(double x) {
  int cnt = 0;
  for (int i = 0; i < N; i++) {
    if (T[i].x < x && T[i].x + T[i].r > x) {
      double t = T[i].r - (x - T[i].x);
      S[cnt++] = {double(T[i].y), T[i].y + t};
    }
  }
  if (!cnt) return 0;
  sort(S, S+cnt);
  double len = 0, last = S[0].a;
  for (int i = 0; i < cnt; i++) {
    if (S[i].b > last) {
      len += S[i].b - max(S[i].a, last);
      last = S[i].b;
    }
  }
  return len;
}

double calc(double l, double r, double lv, double rv) {
  double mid = (l + r) / 2;
  return (lv + 4.0 * f(mid) + rv) * (r - l) / 6.0;
}

bool equal(double a, double b) {
  return fabs(a - b) <= EPS;
}

double simpson(double l, double r, double now, double lv, double rv) {
  double mid = (l + r) / 2, mv = f(mid);
  double left = calc(l, mid, lv, mv), right = calc(mid, r, mv, rv);
  if (equal(left + right, now)) return now;
  return simpson(l, mid, left, lv, mv) + simpson(mid, r, right, mv, rv);
}

int main() {
  scanf("%d", &N);
  vector<int> xpos;
  for (int i = 0; i < N; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    T[i] = {a, b, c};
    xpos.push_back(a);
    xpos.push_back(a + c);
  }
  sort(xpos.begin(), xpos.end());
  xpos.erase(unique(xpos.begin(), xpos.end()), xpos.end());
  double ans = 0;
  for (int i = 0; i < (int)xpos.size()-1; i++) {
    double l = xpos[i] + 2 * EPS, r = xpos[i+1] - 2 * EPS;
    double left = f(l), right = f(r);
    ans += simpson(l, r, calc(l, r, left, right), left, right);
  }
  printf("%.1lf\n", ans);
  return 0;
}
