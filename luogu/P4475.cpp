// https://www.luogu.com.cn/problem/P4475
// 巧克力王国

#include <bits/stdc++.h>
using namespace std;

// 2-d implementation
// Note points are 1-indexed
class KdTree {
    struct Point {
        int x[2];
        int64_t w;
    };

    struct Node {
        int ls, rs;
        int64_t sum;
        int mi[2], mx[2];   // min and max
        Point tp;
    };

    struct PointComp {
        PointComp(int _wd): wd(_wd) {}
        bool operator ()(const Point &a, const Point &b) const {
            return a.x[wd] < b.x[wd];
        }
        int wd;
    };
public:
    KdTree(int n): n_(n) {
        alloc();
    }

    ~KdTree() {
        dealloc();
    }

    void build() {
      root_ = build(1, n_, 0);
    }

    int64_t query(int a, int b, int64_t c) {
      return query(root_, a, b, c);
    }

    Point *pts_;
private:
    const int n_;
    Node *tree_;
    int *garbage_;
    int gbg_top_ = 0;
    int curr_ = 0;
    int root_ = 0;

    void alloc() {
        pts_ = new Point[n_+1]{};
        tree_ = new Node[n_+1]{};
        garbage_ = new int[n_+1]{};
    }

    void dealloc() {
        delete[] pts_;
        delete[] tree_;
        delete[] garbage_;
    }

    /**
     * create a new node
     * @return: index of the new node
     */
    int newnode() {
        if (gbg_top_) return garbage_[gbg_top_--];
        else return ++curr_;
    }

    /**
     * Collect subtree statistics such as size, weight sum
     * @param k: index of subtree root
     */
    void pushUp(int k) {
        int l = tree_[k].ls, r = tree_[k].rs;
        for (int i = 0; i < 2; i++) {
            tree_[k].mi[i] = tree_[k].mx[i] = tree_[k].tp.x[i];
            if (l) tree_[k].mi[i] = min(tree_[k].mi[i], tree_[l].mi[i]);
            if (r) tree_[k].mi[i] = min(tree_[k].mi[i], tree_[r].mi[i]);
            if (l) tree_[k].mx[i] = max(tree_[k].mx[i], tree_[l].mx[i]);
            if (r) tree_[k].mx[i] = max(tree_[k].mx[i], tree_[r].mx[i]);
        }
        tree_[k].sum = tree_[l].sum + tree_[r].sum + tree_[k].tp.w;
    }

    /**
     * build subtree for range [l, r]
     * @param l: left boundary
     * @param r: right boundary
     * @param wd: direction
     * @return: root index
     */
    int build(int l, int r, int wd) {
        if (l > r) return 0;
        int mid = (l + r) / 2;
        int k = newnode();
        nth_element(pts_+l, pts_+mid, pts_+r+1, PointComp(wd));
        tree_[k].tp = pts_[mid];
        tree_[k].ls = build(l, mid-1, wd^1);
        tree_[k].rs = build(mid+1, r, wd^1);
        pushUp(k);
        return k;
    }

    int64_t eval(int a, int b, int x, int y) {
      return 1LL * a * x + 1LL * b * y;
    }

    int64_t query(int k, int a, int b, int c) {
      int x1 = tree_[k].mi[0], y1 = tree_[k].mi[1];
      int x2 = tree_[k].mx[0], y2 = tree_[k].mx[1];
      int64_t v1 = eval(a, b, x1, y1);
      int64_t v2 = eval(a, b, x1, y2);
      int64_t v3 = eval(a, b, x2, y1);
      int64_t v4 = eval(a, b, x2, y2);
      if (min(min(v1, v2), min(v3, v4)) >= c) return 0;
      if (max(max(v1, v2), max(v3, v4)) < c) return tree_[k].sum;
      int64_t ret = 0;
      if (eval(a, b, tree_[k].tp.x[0], tree_[k].tp.x[1]) < c) {
        ret += tree_[k].tp.w;
      }
      int l = tree_[k].ls, r = tree_[k].rs;
      if (l) ret += query(l, a, b, c);
      if (r) ret += query(r, a, b, c);
      return ret;
    }
};

int N, M;

int main() {
  scanf("%d%d", &N, &M);
  KdTree kd(N);
  for (int i = 1; i <= N; i++) {
    int x, y;
    int64_t h;
    scanf("%d%d%ld", &x, &y, &h);
    kd.pts_[i].x[0] = x;
    kd.pts_[i].x[1] = y;
    kd.pts_[i].w = h;
  }
  kd.build();
  for (int i = 0; i < M; i++) {
    int a, b;
    int64_t c;
    scanf("%d%d%ld", &a, &b, &c);
    printf("%ld\n", kd.query(a, b, c));
  }
  return 0;
}
