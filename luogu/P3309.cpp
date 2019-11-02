// https://www.luogu.org/problem/P3309
// [SDOI2014]向量集

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

  Convex(int cap=1): cap_(cap), n_(0) {
    alloc();
  }

  Convex(Convex&& o) noexcept :
      cap_(std::move(o.cap_)),
      n_(std::move(o.n_)),
      pts_(std::move(o.pts_)) {}

  ~Convex() {
    dealloc();
  }

  Convex& operator = (Convex&& other) {
    swap(cap_, other.cap_);
    swap(n_, other.n_);
    swap(pts_, other.pts_);
    return *this;
  }

  void push(const Point& x) {
    while (n_ >= 2 && (pts_[n_-1]-pts_[n_-2])*(x-pts_[n_-1]) >= 0) n_--;
    pts_[n_++] = x;
  }

  static Convex merge(const Convex& q1, const Convex& q2) {
    Convex c(q1.n_ + q2.n_);

    int h1 = 0, h2 = 0;
    while (h1 < q1.n_ && h2 < q2.n_) {
      if (q1.pts_[h1] < q2.pts_[h2]) {
        c.push(q1.pts_[h1++]);
      } else {
        c.push(q2.pts_[h2++]);
      }
    }
    while (h1 < q1.n_) {
      c.push(q1.pts_[h1++]);
    }
    while (h2 < q2.n_) {
      c.push(q2.pts_[h2++]);
    }
    return c;
  }

  int64_t search(const Point& p) const {
    int lo = 0, hi = n_-1;
    while (lo != hi) {
      int mid = (lo + hi) / 2;
      if (dot_product(pts_[mid], p) <= dot_product(pts_[mid+1], p)) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
    return dot_product(pts_[lo], p);
  }

 private:
  int cap_;
  int n_;
  Point* pts_;

  void alloc() {
    pts_ = new Point[cap_];
  }

  void dealloc() {
    delete[] pts_;
  }

  friend class SegmentTree;
};

class SegmentTree {
  using Point = Convex::Point;
  struct Data {
    Convex c[2];
    int64_t query(const Point& p) const {
      if (p.y > 0) return c[0].search(p);
      return c[1].search({-p.x, -p.y});
    }
  };

  int n_;
  int *lid_;
  Data *d_;
  int tot_ = 0;

  void alloc() {
    lid_ = new int[n_]{};
    d_ = new Data[4*n_]{};
  }

  void dealloc() {
    delete[] lid_;
    delete[] d_;
  }

  void init(int k, int l, int r) {
    if (l == r) {
      lid_[l] = k;
      return;
    }
    int mid = (l + r) / 2;
    init(2*k, l, mid);
    init(2*k+1, mid+1, r);
  }

  int64_t query(int k, int l, int r, int a, int b, const Point& p) const {
    int64_t ret = -1e18;
    if (a <= l && r <= b) {
      return d_[k].query(p);
    }
    int mid = (l + r) / 2;
    if (a <= mid) ret = max(ret, query(2*k, l, mid, a, b, p));
    if (mid < b)  ret = max(ret, query(2*k+1, mid+1, r, a, b, p));
    return ret;
  }

 public:
  SegmentTree(int n): n_(n) {
    alloc();
    init(1, 0, n_-1);
  }

  ~SegmentTree() {
    dealloc();
  }

  void add(const Point& p) {
    int k = lid_[tot_++];
    d_[k].c[0].push(p);
    d_[k].c[1].push(Point({-p.x, -p.y}));
    while ((k&1) && k > 1) {
      k >>= 1;
      for (int j = 0; j < 2; j++) {
        d_[k].c[j] = Convex::merge(d_[2*k].c[j], d_[2*k+1].c[j]);
      }
    }
  }

  int64_t query(int a, int b, const Point& p) const {
    return query(1, 0, n_-1, a, b, p);
  }
};

int N;
bool encoded;
int64_t lastans;

void decode(int& x) {
  if (!encoded) return;
  x = (x ^ (lastans & 0x7fffffff));
}

int main() {
  using Point = Convex::Point;
  char s[10];
  scanf("%d%s", &N, s);
  encoded = (s[0] != 'E');
  SegmentTree st(N);
  for (int i = 0; i < N; i++) {
    int x, y, l, r;
    scanf("%s", s);
    if (s[0] == 'A') {
      scanf("%d%d", &x, &y);
      decode(x); decode(y);
      st.add(Point{x, y});
    } else {
      scanf("%d%d%d%d", &x, &y, &l, &r);
      decode(x); decode(y); decode(l); decode(r);
      l--; r--;
      int64_t ans = st.query(l, r, Point({x, y}));
      printf("%ld\n", ans);
      lastans = ans;
    }
  }
  return 0;
}
