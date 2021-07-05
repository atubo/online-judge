// https://codeforces.com/problemset/problem/50/C
// Happy Farm 5

#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;

  bool operator < (const Point& other) const {
    return x < other.x || (x == other.x && y < other.y);
  }

  bool operator == (const Point& other) const {
    return x == other.x && y == other.y;
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

class Convex {
 public:
  Convex(int cap): cap_(cap), n_(0) {
    alloc();
  }

  Convex(vector<Point> pts): Convex(pts.size()) {
    sort(pts.begin(), pts.end(), [](const Point& p, const Point& q) {
        if (p.x != q.x) return p.x < q.x;
        return p.y < q.y;
        });
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    sort(pts.begin() + 1, pts.end(),
        [p0 = pts[0]](const Point& p, const Point& q) {
        if ((p - p0) * (q - p) == 0) {
          return (dot_product(p-p0, p-p0) < dot_product(q-p0, q-p0));
        }

        return atan2(p.y-p0.y, p.x-p0.x) < atan2(q.y-p0.y, q.x-p0.x);
        });
    for (int i = 0; i < (int)pts.size(); i++) {
      push(pts[i]);
    }
    push(pts[0]);
    n_--;
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

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

int dist(const Point& p, const Point& q) {
  int dx = abs(p.x - q.x);
  int dy = abs(p.y - q.y);
  return max(dx, dy);
}

int main() {
  int n;
  scanf("%d", &n);
  vector<Point> pts(4*n);
  for (int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    for (int d = 0; d < 4; d++) {
      pts[4*i + d] = Point{x + DX[d], y + DY[d]};
    }
  }
  Convex convex(pts);
  int64_t ans = 0;
  for (int i = 0; i < convex.n_; i++) {
    ans += dist(convex.pts_[i], convex.pts_[(i+1)%convex.n_]);
  }
  cout << ans << endl;
  return 0;
}
