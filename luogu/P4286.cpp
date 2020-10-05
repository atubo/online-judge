// https://www.luogu.com.cn/problem/P4286
// [SHOI2008]安全的航线

#include <bits/stdc++.h>
using namespace std;

constexpr double INF = 1e5;

struct Vec {
  double x, y;
  Vec() : x(0), y(0) {}
  Vec(double a, double b) : x(a), y(b) {}
  Vec operator + (const Vec& other) const {
    return Vec(x + other.x, y + other.y);
  }
  Vec operator - (const Vec& other) const {
    return Vec(x - other.x, y - other.y);
  }
  Vec operator * (double c) const {
    return Vec(x*c, y*c);
  }
  Vec operator / (double c) const {
    return Vec(x/c, y/c);
  }
  double len() const {
    return sqrt(x*x + y*y);
  }
};

struct Interval {
  Vec l, r;
  Interval() = default;
  Interval(const Vec& a, const Vec& b) : l(a), r(b) {}
  Vec mid() const {
    return (l + r) / 2.0;
  }
  double len() const {
    return (r - l).len();
  }
};

double dot(const Vec& a, const Vec& b) {
  return a.x*b.x + a.y*b.y;
}

double cross(const Vec& a, const Vec& b) {
  return a.x*b.y - a.y*b.x;
}

bool segmentsIntersect(const Vec& ap, const Vec& aq,
    const Vec& bp, const Vec& bq) {
  if (min(ap.x, aq.x) > max(bp.x, bq.x) ||
      min(bp.x, bq.x) > max(ap.x, aq.x) ||
      min(ap.y, aq.y) > max(bp.y, bq.y) ||
      min(bp.y, bq.y) > max(ap.y, aq.y)) {
    return false;
  }
  if (cross(bq-aq, ap-aq) * cross(bp-aq, ap-aq) > 0 ||
      cross(ap-bq, bp-bq) * cross(aq-bq, bp-bq) > 0) {
    return false;
  }
  return true;
}

double pointToSegment(const Vec& a, const Vec& p, const Vec& q) {
  Vec v = q-p;
  double t = dot(a-p, v) / dot(v, v);
  if (t < 0 || t > 1) return min((a-p).len(), (a-q).len());
  Vec b = p + (v*t);
  return (a - b).len();
}

bool pointInPoly(const Vec& a, const Vec* p, int n) {
  int cnt = 0;
  Vec b = a + Vec(1, INF);
  for (int i = 0; i < n; i++) {
    cnt += segmentsIntersect(a, b, p[i], p[(i+1)%n]);
  }
  return cnt&1;
}

const int MAXN = 32;
int C, N, M[MAXN];
Vec Line[MAXN];
Vec Poly[MAXN][MAXN];

double minDist(const Vec& a) {
  double ans = INF;
  for (int i = 0; i < C; i++) {
    if (M[i] >= 3 && pointInPoly(a, Poly[i], M[i])) {
      return 0;
    }
    if (M[i] >= 2) {
      for (int j = 0; j < M[i]; j++) {
        ans = min(ans, pointToSegment(a, Poly[i][j], Poly[i][(j+1)%M[i]]));
      }
    } else {
      ans = min(ans, (Poly[i][0]-a).len());
    }
  }
  return ans;
}

constexpr int MAXCAP = 1000001;
constexpr int MAXITER = 300000;
Interval Q[MAXCAP];

class Solver {
 public:
  void input() {
    scanf("%d%d", &C, &N);
    for (int i = 0; i < N; i++) {
      double x, y;
      scanf("%lf%lf", &x, &y);
      Line[i] = {x, y};
    }
    for (int i = 0; i < C; i++) {
      scanf("%d", &M[i]);
      for (int j = 0; j < M[i]; j++) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        Poly[i][j] = {x, y};
      }
    }
  }

  void solve() {
    double ans = 0;
    int h = 0, t = 0;
    for (int i = 0; i < N-1; i++) {
      Q[h++] = Interval(Line[i], Line[i+1]);
    }
    for (int i = 0; i < MAXITER && h > t; i++) {
      Interval now = Q[t++];
      ans = max(ans, minDist(now.mid()));
      Interval s1 = Interval(now.l, now.mid());
      Interval s2 = Interval(now.mid(), now.r);
      if (s1.len() >= 1e-3 && minDist(s1.mid()) + s1.len()/2 > ans) {
        Q[h++] = s1;
      }
      if (s2.len() >= 1e-3 && minDist(s2.mid()) + s2.len()/2 > ans) {
        Q[h++] = s2;
      }
    }
    printf("%.2lf\n", ans);
  }
};

int main() {
  Solver solver;
  solver.input();
  solver.solve();
  return 0;
}
