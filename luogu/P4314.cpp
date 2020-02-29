// https://www.luogu.com.cn/problem/P4314
// CPU监控

#include <bits/stdc++.h>
using namespace std;

int add(int a, int b) {
  if (a == INT_MIN || b == INT_MIN) return INT_MIN;
  return a + b;
}

struct Tag {
  int a, b;

  Tag(int aa = 0, int bb = INT_MIN) {
    a = aa;
    b = bb;
  }

  void merge1(const Tag& t) {
    int c = t.a;
    int d = t.b;
    a = add(a, c);
    b = max(add(b, c), d);
  }

  void merge2(const Tag& t) {
    int c = t.a;
    int d = t.b;
    a = max(a, c);
    b = max(b, d);
  }

  Tag operator + (const Tag& t) const {
    int c = t.a, d = t.b;
    return Tag(add(a, c), max(add(b, c), d));
  }

  Tag operator * (const Tag& t) const {
    int c = t.a, d = t.b;
    return Tag(max(a, c), max(b, d));
  }
};

// note it's 1-indexed
class SegmentTree {
    int N;
    int *val1_, *val2_;
    Tag *lazy1_, *lazy2_;

public:
    SegmentTree(int N_): N(N_) {
      val1_ = new int[4*N+1]{};
      val2_ = new int[4*N+1]{};
      lazy1_ = new Tag[4*N+1]{};
      lazy2_ = new Tag[4*N+1]{};
    }

    ~SegmentTree() {
      delete[] val1_;
      delete[] val2_;
      delete[] lazy1_;
      delete[] lazy2_;
    }

    // add t to range [a, b]
    void add(int t, int a, int b) {
      Tag x(t, INT_MIN);
      update(x, a, b);
    }

    void set(int t, int a, int b) {
      Tag x(INT_MIN, t);
      update(x, a, b);
    }

    void update(const Tag& t, int a, int b) {
      update(1, t, 1, N, a, b);
    }

    // query range max in [a, b]
    int query(bool flag, int a, int b) {
      return query(1, flag, 1, N, a, b);
    }

    void build(int *v) {
      build(1, 1, N, v);
    }

private:
    void build(int k, int l, int r, int *v) {
      if (l == r) {
        val1_[k] = val2_[k] = v[l];
        return;
      }
      int mid = (l + r) / 2;
      build(2*k, l, mid, v);
      build(2*k+1, mid+1, r, v);
      val1_[k] = max(val1_[2*k], val1_[2*k+1]);
      val2_[k] = max(val2_[2*k], val2_[2*k+1]);
    }

    void update(int k, const Tag& t, int l, int r, int a, int b) {
      if (a <= l && r <= b) {
        lazy2_[k] = lazy2_[k] * (lazy1_[k] + t);
        lazy1_[k] = lazy1_[k] + t;
        val2_[k] = max(val2_[k], max(::add(val1_[k], t.a), t.b));
        val1_[k] = max(::add(val1_[k],  t.a), t.b);
        return;
      }
      pushDown(k);
      int mid = (l + r) / 2;
      if (a <= mid) update(2*k, t, l, mid, a, b);
      if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
      val1_[k] = max(val1_[2*k], val1_[2*k+1]);
      val2_[k] = max(val2_[2*k], val2_[2*k+1]);
    }

    void doPushDown(int k) {
      int x = k/2;
      lazy2_[k] = lazy2_[k] * (lazy1_[k] + lazy2_[x]);
      lazy1_[k] = lazy1_[k] + lazy1_[x];
      val2_[k] = max(val2_[k], max(::add(val1_[k], lazy2_[x].a), lazy2_[x].b));
      val1_[k] = max(::add(val1_[k], lazy1_[x].a), lazy1_[x].b);
    }

    void pushDown(int k) {
      doPushDown(2*k);
      doPushDown(2*k+1);
      lazy1_[k] = lazy2_[k] = Tag{};
    }

    int query(int k, bool flag, int l, int r, int a, int b) {
      if (a <= l && r <= b) {
        return flag ? val2_[k] : val1_[k];
      }
      int ans = INT_MIN;
      pushDown(k);
      int mid = (l + r) / 2;
      if (a <= mid) ans = max(ans, query(2*k, flag, l, mid, a, b));
      if (mid < b)  ans = max(ans, query(2*k+1, flag, mid+1, r, a, b));
      return ans;
    }
};

const int MAXN = 100010;
int T, E;
int A[MAXN];

int main() {
  scanf("%d", &T);
  for (int i = 1; i <= T; i++) {
    scanf("%d", &A[i]);
  }
  SegmentTree st(T);
  st.build(A);
  scanf("%d", &E);
  char cmd[10];
  int x, y, z;
  for (int i = 0; i < E; i++) {
    scanf("%s", cmd);
    if (cmd[0] == 'Q') {
      scanf("%d%d", &x, &y);
      printf("%d\n", st.query(false, x, y));
    } else if (cmd[0] == 'A') {
      scanf("%d%d", &x, &y);
      printf("%d\n", st.query(true, x, y));
    } else if (cmd[0] == 'P') {
      scanf("%d%d%d", &x, &y, &z);
      st.add(z, x, y);
    } else {
      scanf("%d%d%d", &x, &y, &z);
      st.set(z, x, y);
    }
  }

  return 0;
}
