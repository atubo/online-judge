// https://www.luogu.com.cn/problem/P4250
// [SCOI2015]小凸想跑步

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1);

struct Point {
  double x, y;
  double len() const {
    return sqrt(x*x + y*y);
  }
  double phi() const {
    double ret = acos(min(1.0, x/len()));
    if (y < 0) ret = -ret;
    return ret;
  }

  Point operator * (double c) {
    return Point{c*x, c*y};
  }
};

Point operator - (const Point& p, const Point& q) {
  return Point{p.x - q.x, p.y - q.y};
}

Point operator + (const Point& p, const Point& q) {
  return Point{p.x + q.x, p.y + q.y};
}

struct Line {
  Line(const Point& p1, double t1) : p(p1), theta(t1) {
    if (theta > PI) theta -= 2*PI;
    if (theta < -PI) theta += 2*PI;
  }
  Point p;
  double theta;
  bool operator < (const Line& other) const {
    return theta < other.theta;
  }
};

Point crossPoint(const Line& l1, const Line& l2) {
  double x1 = l1.p.x, y1 = l1.p.y;
  double x2 = l2.p.x, y2 = l2.p.y;
  double theta1 = l1.theta, theta2 = l2.theta;
  double t1 = ((x2-x1) * sin(theta2) - (y2-y1) * cos(theta2)) /
      sin(theta2-theta1);
  return Point{x1 + t1*cos(theta1), y1 + t1*sin(theta1)};
}

double cross(const Point& a, const Point& b) {
  return a.x * b.y - a.y * b.x;
}

double dot(const Point& a, const Point& b) {
  return a.x * b.x +  a.y * b.y;
}

double divide(double theta, double r) {
  assert(r > 0);
  double lo = 0, hi = theta;
  while (lo < hi - EPS) {
    double mid = (lo + hi) / 2;
    double x = sin(mid)/sin(theta-mid);
    if (x < r) lo = mid;
    else hi = mid;
  }
  return hi;
}

Point dividePoint(const Point& p1, const Point& p2,
    const Point& q1, const Point q2) {
  double lp = (p1 - p2).len();
  double lq = (q1 - q2).len();
  Point u = q2 - q1;
  Point v = p1 - q1;
  Point n = v - u * (dot(v, u)/(lq*lq));
  double r = lp / (lp + lq);
  return q1 + n * r;
}

Point meetPoint(const Point& p1, const Point& q1,
    const Point& p2, const Point& q2) {
  double x1 = p1.x, y1 = p1.y;
  double x2 = q1.x, y2 = q1.y;
  double x3 = p2.x, y3 = p2.y;
  double x4 = q2.x, y4 = q2.y;
  double x = ((x2*y1-x1*y2)*(x4-x3) - (x4*y3-x3*y4)*(x2-x1)) /
      ((y1-y2)*(x4-x3) - (y3-y4)*(x2-x1));
  double y = ((x2*y1-x1*y2)*(y3-y4) - (x4*y3-x3*y4)*(y1-y2)) /
      ((x2-x1)*(y3-y4) - (x4-x3)*(y1-y2));
  return Point{x, y};
}

class Solver {
 public:
  Solver() {
    scanf("%d", &n_);
    alloc();
    for (int i = 0; i < n_; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      pts_[i] = {1.0*x, 1.0*y};
    }
  }

  ~Solver() {
    dealloc();
  }

  void solve() {
    vector<Line> lines;
    for (int i = 1; i < n_; i++) {
      Point p = pts_[0] - pts_[1];
      Point q = pts_[(i+1)%n_] - pts_[i];
      double lp = p.len(), lq = q.len();
      double c = cross(q, p);
      double d = dot(p, q);
      if (fabs(c) < EPS) {
        Point x = dividePoint(pts_[0], pts_[1], pts_[i], pts_[(i+1)%n_]);
        double phi = q.phi();
        lines.emplace_back(x, phi);
      } else if (c > 0) {
        double theta = acos(min(1.0, d/(lp*lq)));
        double theta1 = divide(theta, lp/lq);
        double phi = q.phi();
        Point x = meetPoint(pts_[1], pts_[0], pts_[i], pts_[(i+1)%n_]);
        lines.emplace_back(x, phi+theta1);
      } else {
        double theta = acos(min(1.0, d/(lp*lq)));
        double theta1 = divide(theta, lp/lq);
        double phi = q.phi();
        Point x = meetPoint(pts_[0], pts_[1], pts_[(i+1)%n_], pts_[i]);
        lines.emplace_back(x, phi-theta1);
      }
    }
    lines.emplace_back(pts_[0], (pts_[1]-pts_[0]).phi());
    sort(lines.begin(), lines.end());
    vector<Point> ct = convex(lines);

    double s1 = area();
    double s2 = area(ct);
    printf("%.4f\n", s2/s1);
  }

 private:
  int n_;
  Point* pts_;

  void alloc() {
    pts_ = new Point[n_]{};
  }

  void dealloc() {
    delete[] pts_;
  }

  vector<Point> convex(const vector<Line>& lines) {
    vector<Point> t(n_+1);
    vector<Line> q = lines;
    int l = -1, r = -1;
    for (int i = 0; i < n_; i++) {
      while (r - l > 1 &&
          cross(Point{cos(lines[i].theta), sin(lines[i].theta)},
                t[r]- lines[i].p) <= 0) {
        --r;
      }
      while (r - l > 1 &&
          cross(Point{cos(lines[i].theta), sin(lines[i].theta)},
                t[l+2] - lines[i].p) <= 0) {
        ++l;
      }
      q[++r] = lines[i];
      if (r - l > 1) t[r] = crossPoint(q[r], q[r-1]);
    }
    while (r - l > 1 &&
        cross(Point{cos(q[l+1].theta), sin(q[l+1].theta)},
              t[r] - q[l+1].p) <= 0) {
      --r;
    }
    t[r+1] = crossPoint(q[l+1], q[r]);
    ++r;
    assert(r < n_+1);
    vector<Point> ret;
    for (int i = l+2; i <= r; i++) {
      ret.push_back(t[i]);
    }

    return ret;
  }

  double area() const {
    double s = 0;
    for (int i = 0; i < n_; i++) {
      s += cross(pts_[i], pts_[(i+1)%n_]);
    }
    return s;
  }

  double area(const vector<Point>& c) {
    double s = 0;
    const int m = c.size();
    for (int i = 0; i < m; i++) {
      s += cross(c[i], c[(i+1)%m]);
    }
    return s;
  }
};

int main() {
  Solver solver;
  solver.solve();
  return 0;
}
