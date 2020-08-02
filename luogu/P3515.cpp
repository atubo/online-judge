// https://www.luogu.com.cn/problem/P3515
// [POI2011]Lightning Conductor

#include <bits/stdc++.h>
using namespace std;


class LcSegmentTree {
 public:
  struct Curve {
    Curve() : x(0), y(0), flag(false) {}
    Curve(int xx, int yy, bool f): x(xx), y(yy), flag(f) {}
    int x, y;
    bool flag;
  };

  LcSegmentTree(int n) : n_(n) {
    alloc();
  }

  ~LcSegmentTree() {
    dealloc();
  }

  void update(const Curve& curve) {
    update(1, 1, n_, curve);
  }

  int query(int x) const {
    return query(1, 1, n_, x);
  }

 private:
  void alloc() {
    curves_ = new Curve[4*n_+1];
  }

  void dealloc() {
    delete curves_;
  }

  void update(int k, int l, int r, Curve curve) {
    if (curve.x <= l) {
      if (!curves_[k].flag) {
        curves_[k] = curve;
        return;
      }
      if (curve.y <= curves_[k].y) return;
      if (curve.y >= curves_[k].y + sqrtc(curve.x - curves_[k].x)) {
        curves_[k] = curve;
        return;
      }
      double xc = solve(curves_[k].x, curve.x, curves_[k].y, curve.y);
      if (xc >= r) return;
      if (xc <= l) {
        curves_[k] = curve;
        return;
      }
      assert(l < r);
      int mid = (l + r) / 2;
      if (xc < mid) {
        swap(curve, curves_[k]);
        update(2*k, l, mid, curve);
      } else {
        update(2*k+1, mid+1, r, curve);
      }
    } else {
      assert(l < r);
      int mid = (l + r) / 2;
      if (curve.x <= mid) {
        update(2*k, l, mid, curve);
      }
      update(2*k+1, mid+1, r, curve);
    }
  }

  static double solve(int x0, int x1, int y0, int y1)   {
    assert(y0 != y1);
    double t1 = (1.0*(x0+x1) + 1.0*(y1-y0)*(y1-y0));
    double t2 = -4.0*x0*x1 + t1*t1;
    double t3 = 4.0*(y1-y0)*(y1-y0);
    return t2 / t3;
  }

  static int sqrtc(int x) {
    int ret = sqrt(x);
    return ret*ret == x ? ret : ret+1;
  }

  static int calc(const Curve& curve, int x) {
    return curve.y + sqrtc(x - curve.x);
  }

  int query(int k, int l, int r, int x) const {
    int ans = calc(curves_[k], x);
    if (l == r) return ans;
    int mid = (l + r) / 2;
    if (x <= mid) ans = max(ans, query(2*k, l, mid, x));
    else ans = max(ans, query(2*k+1, mid+1, r, x));
    return ans;
  }

  int n_;
  Curve* curves_;
};

const int MAXN = 500010;
int N;
int A[MAXN];
int ans[MAXN];

int main() {
  using Curve = LcSegmentTree::Curve;
  scanf("%d", &N);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
    ans[i] = A[i];
  }
  LcSegmentTree st1(N);
  st1.update(Curve{1, A[1], true});
  for (int i = 2; i <= N; i++) {
    ans[i] = max(ans[i], st1.query(i));
    st1.update(Curve{i, A[i], true});
  }

  LcSegmentTree st2(N);
  st2.update(Curve{1, A[N], true});
  for (int i = N-1; i >= 1; i--) {
    ans[i] = max(ans[i], st2.query(N+1-i));
    st2.update(Curve{N+1-i, A[i], true});
  }

  for (int i = 1; i <= N; i++) {
    printf("%d\n", ans[i]-A[i]);
  }

  return 0;
}
