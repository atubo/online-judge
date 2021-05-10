// https://codeforces.com/problemset/problem/8/D
// Two Friends

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-10;

struct Circle {
  double x, y, r;
};

struct Point {
  double x, y;
};

double distsq(double x, double y) {
  return x * x + y * y;
}

double dist(const Point& p, const Point& q) {
  return sqrt(distsq(p.x - q.x, p.y - q.y));
}

bool outside(const Circle& c1, const Circle& c2) {
   return distsq(c1.x-c2.x, c1.y-c2.y) > (c1.r+c2.r)*(c1.r+c2.r) + EPS;
}

bool inside(const Circle& c1, const Circle& c2) {
  if (c1.r > c2.r) return false;
  return distsq(c1.x-c2.x, c1.y-c2.y) <= (c2.r-c1.r)*(c2.r-c1.r) + EPS;
}

bool intersect(const Circle& c1, const Circle& c2) {
  return !outside(c1, c2);
}

pair<Point, Point> cross(const Circle& c1, const Circle& c2) {
  double dx = c1.x - c2.x;
  double dy = c1.y - c2.y;
  double d = sqrt(dx*dx + dy*dy);
  double x = (c1.x + c2.x) / 2 +
      (c2.x - c1.x) * (c1.r * c1.r - c2.r * c2.r) / (2 * d * d);
  double e = 0;
  if (-d + c1.r + c2.r >= 0) {
    e = 0.25 * sqrt((d + c1.r + c2.r) * (d + c1.r - c2.r)
      * (d - c1.r + c2.r) * (-d + c1.r + c2.r));
  }
  double x1 = x + 2 * (c1.y - c2.y) * e / (d * d);
  double x2 = x - 2 * (c1.y - c2.y) * e / (d * d);

  double y = (c1.y + c2.y) / 2 +
      (c2.y - c1.y) * (c1.r * c1.r - c2.r * c2.r) / (2 * d * d);
  double y1 = y - 2 * (c1.x - c2.x) * e / (d * d);
  double y2 = y + 2 * (c1.x - c2.x) * e / (d * d);
  return make_pair(Point{x1, y1}, Point{x2, y2});
}

bool ptInCircle(const Point& p, const Circle& c) {
  return distsq(p.x-c.x, p.y-c.y) <= c.r*c.r + EPS;
}

bool intersect(const Circle& c1, const Circle& c2, const Circle& c3) {
  if (outside(c1, c2)) return false;
  if (inside(c1, c2)) return intersect(c1, c3);
  if (inside(c2, c1)) return intersect(c2, c3);
  if (outside(c2, c3)) return false;
  if (inside(c2, c3)) return intersect(c2, c1);
  if (inside(c3, c2)) return intersect(c3, c1);
  if (outside(c1, c3)) return false;
  if (inside(c1, c3)) return intersect(c1, c2);
  if (inside(c3, c1)) return intersect(c3, c2);

  vector<Point> pts;
  Point p1, p2;
  tie(p1, p2) = cross(c1, c2);
  pts.push_back(p1);
  pts.push_back(p2);
  tie(p1, p2) = cross(c2, c3);
  pts.push_back(p1);
  pts.push_back(p2);
  tie(p1, p2) = cross(c1, c3);
  pts.push_back(p1);
  pts.push_back(p2);
  for (const auto& p : pts) {
    if (ptInCircle(p, c1) && ptInCircle(p, c2) && ptInCircle(p, c3)) {
      return true;
    }
  }
  return false;
}

Point C, H, S;
double TCS, TSH;

bool feasible1(double x, double ta, double tb) {
  if (ta < TSH) return false;
  Circle c1{C.x, C.y, x};
  Circle c2{S.x, S.y, ta-TSH};
  Circle c3{H.x, H.y, tb};
  return intersect(c1, c2, c3);
}

bool feasible2(double x, double ta, double tb) {
  Circle c1{S.x, S.y, x-TCS};
  Circle c2{H.x, H.y, ta};
  Circle c3{H.x, H.y, tb};
  return intersect(c1, c2) && intersect(c1, c3);
}

bool feasible(double x, double ta, double tb) {
  if (x >= TCS) return feasible1(x, ta, tb) || feasible2(x, ta, tb);
  return feasible1(x, ta, tb);
}

int main() {
  int t1, t2;
  scanf("%d%d", &t1, &t2);
  int x, y;
  scanf("%d%d", &x, &y);
  C.x = x;
  C.y = y;
  scanf("%d%d", &x, &y);
  H.x = x;
  H.y = y;
  scanf("%d%d", &x, &y);
  S.x = x;
  S.y = y;

  TCS = dist(C, S);
  TSH = dist(S, H);
  double ta = TCS + TSH;
  double tb = dist(C, H);
  double lo = min(t1, t2), hi = min(ta+t1, tb+t2);
  while (lo < hi - 1e-10) {
    double mid = (lo + hi) / 2;
    if (feasible(mid, ta+t1-mid, tb+t2-mid)) lo = mid;
    else hi = mid;
  }

  printf("%.6f\n", lo);
  return 0;
}
