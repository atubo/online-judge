// https://www.luogu.com.cn/problem/P4097
// [HEOI2013]Segment

#include <bits/stdc++.h>
using namespace std;

struct Rational {
  explicit Rational(int64_t pp=0, int64_t qq=1) : p(pp), q(qq) {}

  Rational operator * (int x) const {
    if (x == 0) return Rational(0, 1);

    int64_t s = p * x;
    int64_t t = q;
    Rational ret{s, t};
    return ret;
  }

  Rational operator + (int x) const {
    assert(q != 0);
    Rational ret{p + q*x, q};
    return ret;
  }

  bool operator == (const Rational& other) const {
    return p == other.p && q == other.q;
  }

  bool operator != (const Rational& other) const {
    return !((*this) == other);
  }

  bool operator < (const Rational& other) const {
    assert(q > 0 && other.q > 0);
    return p * other.q < q * other.p;
  }

  int64_t p, q;

  const static Rational VERT;
};

const Rational Rational::VERT{1, 0};

int sgn(const Rational& r1, const Rational& r2) {
  int64_t p1 = r1.p, q1 = r1.q;
  int64_t p2 = r2.p, q2 = r2.q;
  assert(q1 > 0 && q2 > 0);
  int64_t d = p1*q2 - p2*q1;
  return d > 0 ? 1 : (d < 0 ? -1 : 0);
}

struct Result {
  Result(const Rational& x0, int id0): x(x0), id(id0) {}
  Rational x;
  int id;
  bool operator < (const Result& other) const {
    if (x != other.x) return x < other.x;
    return id > other.id;
  }
};

// 1-indexed
class LcSegmentTree {
 public:
  struct Line {
    Line(
        int64_t p=0,
        int64_t q=1,
        int bb=0,
        int ll=0,
        int rr=0,
        int id0=0) : k(p, q), b(bb), l(ll), r(rr), id(id0) {}
    Rational k;
    int b;
    int l, r;
    int id;
  };

  static Rational calc(const Line &a, int pos) {
    return a.k*(pos-a.l) + a.b;
  }

  static int cross(const Line &a, const Line &b) {
    assert(a.k != Rational::VERT && b.k != Rational::VERT);
    Rational k1 = a.k, k2 = b.k;
    int64_t b1 = a.b, b2 = b.b;
    int64_t p1 = k1.p, q1 = k1.q, p2 = k2.p, q2 = k2.q;
    int64_t l1 = a.l, l2 = b.l;
    int64_t s = p2*q1*l2 - p1*q2*l1 + (b1-b2)*q1*q2;
    int64_t t = p2*q1 - p1*q2;
    return s / t;
  }

  LcSegmentTree(int n): n_(n) {
    alloc();
  }

  ~LcSegmentTree() {
    dealloc();
  }

  void modify(int x0, int y0, int x1, int y1, int id) {
    if (x0 == x1) {
      if (y0 > y1) swap(y0, y1);
      Line l(1, 0, y1, x0, x1, id);
      modify(1, 1, n_, l);
      return;
    }
    if (x0 > x1) {
      swap(x0, x1);
      swap(y0, y1);
    }
    Line l(y1-y0, x1-x0, y0, x0, x1, id);
    modify(1, 1, n_, l);
  }

  int query(int x) const {
    return query(1, 1, n_, x).id;
  }

 private:
  int n_;
  Line *sgt_;

  void alloc() {
    sgt_ = new Line[4*n_+1]{};
  }

  void dealloc() {
    delete[] sgt_;
  }

  void modify(int k, int l, int r, Line line) {
    // current range is [l, r], modify range is [a, b]
    if (line.l <= l && r <= line.r) {
      if (!sgt_[k].id) {
        sgt_[k] = line;
        return;
      }
      int dl = sgn(calc(line, l), calc(sgt_[k], l));
      int dr = sgn(calc(line, r), calc(sgt_[k], r));

      if (dl > 0 && dr > 0) {
        sgt_[k] = line;
      } else if (dl > 0 || dr > 0) {
        int mid = (l + r) / 2;
        int dm = sgn(calc(line, mid), calc(sgt_[k], mid));
        if (dm != 0) {
          if (dm > 0) {
            swap(line, sgt_[k]);
          }
          if (cross(line, sgt_[k]) < mid) {
            modify(2*k, l, mid, line);
          } else {
            modify(2*k+1, mid+1, r, line);
          }
        } else {
          if (dl > 0) {
            modify(2*k, l, mid, line);
          } else {
            modify(2*k+1, mid+1, r, line);
          }
        }
      }
    } else {
      int mid = (l + r) / 2;
      if (line.l <= mid) modify(2*k, l, mid, line);
      if (mid < line.r)  modify(2*k+1, mid+1, r, line);
    }
  }

  Result query(int k, int l, int r, int x) const {
    if (l == r) return Result(calc(sgt_[k], x), sgt_[k].id);
    int mid = (l + r) / 2;
    Result ans = Result(calc(sgt_[k], x), sgt_[k].id);
    if (x <= mid) ans = max(ans, query(2*k, l, mid, x));
    else ans = max(ans, query(2*k+1, mid+1, r, x));
    return ans;
  }
};

const int MAXX = 39989;
const int MAXY = 1000000000;
int N;
int lastans;

int decode(int x, int mod) {
  return (x + lastans - 1) % mod + 1;
}

int main() {
  scanf("%d", &N);
  LcSegmentTree lc(MAXX);
  int op, k, x0, y0, x1, y1;
  int id = 1;
  for (int i = 0; i < N; i++) {
    scanf("%d", &op);
    if (op == 0) {
      scanf("%d", &k);
      int x = decode(k, MAXX);
      lastans = lc.query(x);
      printf("%d\n", lastans);
    } else {
      scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
      x0 = decode(x0, MAXX);
      y0 = decode(y0, MAXY);
      x1 = decode(x1, MAXX);
      y1 = decode(y1, MAXY);
      lc.modify(x0, y0, x1, y1, id++);
    }
  }
  return 0;
}
