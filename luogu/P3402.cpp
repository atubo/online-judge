// https://www.luogu.com.cn/problem/P3402
// 可持久化并查集

#include <bits/stdc++.h>
using namespace std;

class PersistentUnionFind {
  class PersistentSegmentTree {
    int n_;
    int m_;
    int time_ = 0;
    int cnt_ = 0;
    int* root_;
    int* val_;
    int* lc_;
    int* rc_;

    void alloc() {
      const int cap = (n_ + m_) * 17;
      root_ = new int[n_ + m_ + 1] {};
      val_ = new int[cap] {};
      lc_ = new int[cap] {};
      rc_ = new int[cap] {};
    }

    void dealloc() {
      delete[] root_;
      delete[] val_;
      delete[] lc_;
      delete[] rc_;
    }

   public:
    PersistentSegmentTree(int n, int m): n_(n), m_(m) {
      alloc();
    }

    ~PersistentSegmentTree() {
      dealloc();
    }

    void insert(int last, int& rt, int l, int r, int pos, int x) {
      rt = ++cnt_;
      lc_[rt] = lc_[last];
      rc_[rt] = rc_[last];
      if (l == r) {
        val_[rt] = x;
        return;
      }
      int mid = (l + r) / 2;
      if (pos <= mid) insert(lc_[last], lc_[rt], l, mid, pos, x);
      else insert(rc_[last], rc_[rt], mid+1, r, pos, x);
    }

    void update(int fromTime, int pos, int x) {
      insert(root_[fromTime], root_[++time_], 1, n_, pos, x);
    }

    int query(int fromTime, int pos) const {
      return query(root_[fromTime], 1, n_, pos);
    }

    int query(int rt, int l, int r, int pos) const {
      if (l == r) return val_[rt];
      int mid = (l + r) / 2;
      if (pos <= mid) return query(lc_[rt], l, mid, pos);
      else return query(rc_[rt], mid+1, r, pos);
    }

    int getTime() const {
      return time_;
    }
  };
 private:
  int n_;
  int m_;
  int time_ = 0;
  int* timeFa_;
  int* timeRank_;

  PersistentSegmentTree fa_, rank_;

  void alloc() {
    timeFa_ = new int[m_+1]{};
    timeRank_ = new int[m_+1]{};
  }

  void dealloc() {
    delete[] timeFa_;
    delete[] timeRank_;
  }

 public:
  PersistentUnionFind(int n, int m): n_(n), m_(m), fa_(n, m), rank_(n, m) {
    alloc();
    build();
  }

  ~PersistentUnionFind() {
    dealloc();
  }

  void build() {
    for (int i = 1; i <= n_; i++) {
      int t = fa_.getTime();
      fa_.update(t, i, i);
      rank_.update(t, i, 1);
    }
    timeFa_[time_] = fa_.getTime();
    timeRank_[time_] = fa_.getTime();
  }

  int find(int fromTime, int x) {
    int f = fa_.query(timeFa_[fromTime], x);
    if (f == x) return x;
    return find(fromTime, f);
  }

  int merge(int fromTime, int x, int y) {
    time_++;

    int a = find(fromTime, x), b = find(fromTime, y);
    int ra = rank_.query(timeRank_[fromTime], a);
    int rb = rank_.query(timeRank_[fromTime], b);
    if (ra > rb) {
      swap(a, b);
    }

    if (ra == rb) {
      rank_.update(timeRank_[fromTime], b, rb+1);
    }
    fa_.update(timeFa_[fromTime], a, b);
    timeFa_[time_] = fa_.getTime();
    timeRank_[time_] = rank_.getTime();
    return time_;
  }

  void print(int t) const {
    printf("fa: ");
    for (int i = 1; i <= n_; i++) {
      printf("%d ", fa_.query(timeFa_[t], i));
    }
    printf("\nrank:");
    for (int i = 1; i <= n_; i++) {
      printf("%d ", rank_.query(timeRank_[t], i));
    }
    printf("\n");
  }

  int getTime() const {
    return time_;
  }
};

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  vector<int> t(m+1);
  PersistentUnionFind uf(n, m);

  t[0] = uf.getTime();
  for (int i = 1; i <= m; i++) {
    int c, a, b;
    scanf("%d%d", &c, &a);
    if (c == 1) {
      scanf("%d", &b);
      t[i] = uf.merge(t[i-1], a, b);
    } else if (c == 2) {
      t[i] = t[a];
    } else {
      scanf("%d", &b);

      int fa = uf.find(t[i-1], a), fb = uf.find(t[i-1], b);
      printf("%d\n", fa == fb);
      t[i] = t[i-1];
    }
  }

  return 0;
}
