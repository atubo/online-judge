// https://www.luogu.com.cn/problem/P2742
// [USACO5.1]圈奶牛Fencing the Cows /【模板】二维凸包

#include <bits/stdc++.h>
using namespace std;

class Convex {
 public:
  struct Point {
    double x, y;

    bool operator < (const Point& other) const {
      return x < other.x || (x == other.x && y < other.y);
    }

    bool operator == (const Point& other) const {
      return x == other.x && y == other.y;
    }

    friend Point operator - (const Point& p1, const Point& p2) {
      return Point{p1.x-p2.x, p1.y-p2.y};
    }

    friend double operator * (const Point& p1, const Point& p2) {
      return p1.x*p2.y - p1.y*p2.x;
    }

    friend double dot_product(const Point& p1, const Point& p2) {
      return p1.x*p2.x + p1.y*p2.y;
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

const int MAXN = 100000;
int N;
using Point = Convex::Point;
Point P[MAXN];

double dist(const Point& p1, const Point& p2) {
  double dx = p1.x - p2.x;
  double dy = p1.y - p2.y;
  return sqrt(dx*dx + dy*dy);
}

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    double x, y;
    scanf("%lf%lf", &x, &y);
    P[i] = {x, y};
  }
  sort(P, P+N);
  sort(P+1, P+N, [p0=P[0]](const Point& p1, const Point& p2) {
      return (p1-p0)*(p2-p0) > 0;
      });
  Convex convex(N);
  for (int i = 0; i < N; i++) {
    convex.push(P[i]);
  }
  double ans = 0 ;
  for (int i = 0; i < convex.n_; i++) {
    ans += dist(convex.pts_[(i+1)%convex.n_], convex.pts_[i]);
  }
  printf("%.2f\n", ans);
  return 0;
}
