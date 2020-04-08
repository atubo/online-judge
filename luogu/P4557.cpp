// https://www.luogu.com.cn/problem/P4557
// [JSOI2018]战争

#include <bits/stdc++.h>
using namespace std;

class Convex {
 public:
  struct Point {
    int x, y;

    bool operator < (const Point& other) const {
      return x < other.x || (x == other.x && y < other.y);
    }

    bool operator == (const Point& other) const {
      return x == other.x && y == other.y;
    }

    Point& operator += (const Point& other) {
      x += other.x;
      y += other.y;
      return *this;
    }
      
    friend Point operator + (const Point& p1, const Point& p2) {
      return Point{p1.x+p2.x, p1.y+p2.y};
    }

    friend Point operator - (const Point& p1, const Point& p2) {
      return Point{p1.x-p2.x, p1.y-p2.y};
    }

    friend int64_t operator * (const Point& p1, const Point& p2) {
      return 1LL*p1.x*p2.y - 1LL*p1.y*p2.x;
    }

    friend int64_t dot_product(const Point& p1, const Point& p2) {
      return 1LL*p1.x*p2.x + 1LL*p1.y*p2.y;
    }
  };

  Convex(int cap): cap_(cap), n_(0) {
    alloc();
  }

  ~Convex() {
    dealloc();
  }

  void push(const Point& x) {
    while (n_ >= 2 && (pts_[n_-1]-pts_[n_-2])*(x-pts_[n_-1]) <= 0) n_--;
    pts_[n_++] = x;
  }

  Point* pts_;
  int cap_;
  int n_;

 private:
  void alloc() {
    pts_ = new Point[cap_];
  }

  void dealloc() {
    delete[] pts_;
  }
};

using Point = Convex::Point;

const int MAXN = 100010;

struct Sorter {
  Sorter(const Point& p) : p0(p) {}
  bool operator() (const Point& p1, const Point& p2) const {
    int x1 = p1.x - p0.x;
    int y1 = p1.y - p0.y;
    int x2 = p2.x - p0.x;
    int y2 = p2.y - p0.y;
    return (1LL*x1*y2 - 1LL*x2*y1) > 0;
  }

  Point p0;
};

struct EdgeSorter {
  bool operator() (const Point& p1, const Point& p2) const {
    const Point p0 = {1, 0};
    int64_t c1 = p0 * p1;
    int64_t c2 = p0 * p2;
    if (c1 == 0 && c2 == 0) {
      return p1.x > p2.x;
    } else if (c1 == 0) {
      if (p1.x > 0) {
        return true;
      } else {
        return c2 < 0;
      }
    } else if (c2 == 0) {
      if (p2.x > 0) {
        return false;
      } else {
        return c1 > 0;
      }
    } else {
      if ((c1 > 0 && c2 > 0) || (c1 < 0 && c2 < 0)) {
        return p1 * p2 > 0;
      } else if (c1 > 0 && c2 < 0) {
        return true;
      } else {
        return false;
      }
    }
  }
};

Point southWest(const Convex& c) {
  Point p = c.pts_[0];
  for (int i = 1; i < c.n_; i++) {
    if (c.pts_[i].x < p.x || (c.pts_[i].x == p.x && c.pts_[i].y < p.y)) {
      p = c.pts_[i];
    }
  }
  return p;
}

Point northEast(const Convex& c) {
  Point p = c.pts_[0];
  for (int i = 1; i < c.n_; i++) {
    if (c.pts_[i].x > p.x || (c.pts_[i].x == p.x && c.pts_[i].y > p.y)) {
      p = c.pts_[i];
    }
  }
  return p;
}

Point southWest(const vector<Point>& c) {
  Point p = c[0];
  for (const auto& q : c) {
    if (q.x < p.x || (q.x == p.x && q.y < p.y)) {
      p = q;
    }
  }
  return p;
}

Point calcShift(const Convex& c1, const Convex& c2,
    const vector<Point>& poly) {
  Point sw1 = southWest(c1);
  Point ne2 = northEast(c2);
  Point sw2 = southWest(c2);
  Point swq = sw1 + (sw2 - ne2);
  Point swp = southWest(poly);
  return swq - swp;
}

void rotate(vector<Point>& c) {
  int pivot = 0;
  for (int i = 1; i < (int)c.size(); i++) {
    if (c[i].x < c[pivot].x || (c[i].x == c[pivot].x && c[i].y < c[pivot].y)) {
      pivot = i;
    }
  }
  rotate(c.begin(), c.begin()+pivot, c.end());
}

void move(vector<Point>& c, const Point& r) {
  for (auto& p : c) {
    p += r;
  }
}

void reduce(vector<Point>& c) {
  vector<Point> ret;
  ret.push_back(c[0]);
  const int n = c.size();
  for (int i = 1; i < n; i++) {
    Point p = c[i] - c[i-1];
    Point q = c[(i+1)%n] - c[i];
    int64_t cross = p * q;
    int64_t dot = dot_product(p, q);
    if (cross == 0 && dot > 0) continue;
    ret.push_back(c[i]);
  }
  c = std::move(ret);
}

bool check(const vector<Point>& c, const Point& p) {
  const int n = c.size();
  if ((p-c[0])*(c[1]-c[0]) > 0 || (c[n-1]-c[0])*(p-c[0]) > 0) {
    return false;
  }
  if ((p-c[0])*(c[1]-c[0]) == 0) {
    return dot_product(p-c[0], c[1]-p) >= 0;
  }
  if ((c[n-1]-c[0])*(p-c[0]) == 0) {
    return dot_product(p-c[0], c[n-1]-p) >= 0;
  }
  int lo = 1, hi = n-1;
  while (lo < hi-1) {
    int mid = (lo + hi) / 2;
    if ((c[mid]-c[0])*(p-c[0]) > 0) lo = mid;
    else hi = mid;
  }
  return (c[hi]-c[lo])*(p-c[lo]) >= 0;
}

int N, M, Q;
Point P1[MAXN], P2[MAXN];

int main() {
  scanf("%d%d%d", &N, &M, &Q);
  for (int i = 0; i < N; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    P1[i] = {x, y};
  }
  for (int i = 0; i < M; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    P2[i] = {x, y};
  }
  sort(P1, P1+N);
  sort(P1+1, P1+N, Sorter(P1[0]));
  Convex c1(N);
  for (int i = 0; i < N; i++) {
    c1.push(P1[i]);
  }
  sort(P2, P2+M);
  sort(P2+1, P2+N, Sorter(P2[0]));
  Convex c2(M);
  for (int i = 0; i < M; i++) {
    c2.push(P2[i]);
  }

  vector<Point> edges;
  for (int i = 0; i < c1.n_; i++) {
    edges.push_back(c1.pts_[(i+1)%c1.n_] - c1.pts_[i]);
  }
  for (int i = 0; i < c2.n_; i++) {
    edges.push_back(c2.pts_[i] - c2.pts_[(i+1)%c2.n_]);
  }
  sort(edges.begin(), edges.end(), EdgeSorter());
  // build polygon
  vector<Point> poly;
  poly.push_back({0, 0});
  for (int i = 0, px = 0, py = 0; i < (int)edges.size() - 1; i++) {
    int x = px + edges[i].x;
    int y = py + edges[i].y;
    poly.push_back({x, y});
    px = x;
    py = y;
  }
  Point r = calcShift(c1, c2, poly);

  rotate(poly); // rotate to start from sw corner
  move(poly, r);
  reduce(poly);

  const Point sw2 = southWest(c2);
  for (int i = 0; i < Q; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    Point q = {sw2.x +  x, sw2.y + y};
    printf("%d\n", check(poly, q));
  }
  return 0;
}
