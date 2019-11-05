// https://www.luogu.org/problem/P3373
// 【模板】线段树 2

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int P;
int A[MAXN];

// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *val, *lazy0, *lazy1;

public:
    SegmentTree(int N_): N(N_) {
        val = new int64_t[4*N+1]{};
        lazy0 = new int64_t[4*N+1]{};
        lazy1 = new int64_t[4*N+1]{};
    }

    ~SegmentTree() {
        delete[] val;
        delete[] lazy0;
        delete[] lazy1;
    }

    void add(int t, int a, int b) {
      add(1, t, 1, N, a, b);
    }

    void mul(int t, int a, int b) {
      mul(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    int query(int a, int b) {
        return query(1, 1, N, a, b);
    }

    void build() {
      build(1, 1, N);
    }

    void print() {
      for (int i = 1; i <= N; i++) {
        printf("%d ", query(i, i));
      }
      printf("\n");
    }

private:
    void build(int k, int l, int r) {
      lazy0[k] = 0;
      lazy1[k] = 1;
      if (l == r) {
        val[k] = A[l];
        return;
      }
      int mid = (l + r) / 2;
      build(2*k, l, mid);
      build(2*k+1, mid+1, r);
      val[k] = add(val[2*k], val[2*k+1]);
    }

    int add(int64_t a, int64_t b) {
      //return (a + b) % P;
      int64_t ret = a + b;
      return ret >= P ? ret-P: ret;
    }

    int mul(int64_t a, int64_t b) {
      return (a * b) % P;
    }

    void add(int k, int t, int l, int r, int a, int b) {
      if (a > b) return;
      pushDown(k, l, r);
      if (a <= l && r <= b) {
        val[k] = add(val[k], mul(t, r-l+1));
        lazy0[k] = add(lazy0[k], t);
        return;
      }
      if (l == r) return;
      int mid = (l + r) / 2;
      if (a <= mid) add(2*k, t, l, mid, a, b);
      if (mid < b)  add(2*k+1, t, mid+1, r, a, b);
      val[k] = add(val[2*k], val[2*k+1]);
    }

    void mul(int k, int t, int l, int r, int a, int b) {
      if (a > b) return;
      pushDown(k, l, r);
      if (a <= l && r <= b) {
        val[k] = mul(val[k], t);
        lazy0[k] = mul(lazy0[k], t);
        lazy1[k] = mul(lazy1[k], t);
        return;
      }
      if (l == r) return;
      int mid = (l + r) / 2;
      if (a <= mid) mul(2*k, t, l, mid, a, b);
      if (mid < b) mul(2*k+1, t, mid+1, r, a, b);
      val[k] = add(val[2*k], val[2*k+1]);
    }

    void pushDown(int k, int l, int r) {
        if (l == r) return;
        lazy1[2*k] = mul(lazy1[k], lazy1[2*k]);
        lazy1[2*k+1] = mul(lazy1[k], lazy1[2*k+1]);
        lazy0[2*k] = add(mul(lazy1[k], lazy0[2*k]), lazy0[k]);
        lazy0[2*k+1] = add(mul(lazy1[k], lazy0[2*k+1]), lazy0[k]);
        int mid = (l + r) / 2;
        val[2*k] = add(mul(val[2*k], lazy1[k]), mul(mid - l + 1, lazy0[k]));
        val[2*k+1] = add(mul(val[2*k+1], lazy1[k]), mul(r - mid, lazy0[k]));
        lazy0[k] = 0;
        lazy1[k] = 1;
    }

    // query range sum in [a, b], current node is [l, r]
    int query(int k, int l, int r, int a, int b) {
        if (!k) return 0;
        if (b < l || a > r) return 0;
        pushDown(k, l, r);
        if (a <= l && r <= b) return val[k];
        int64_t sum = 0;
        int mid = (l + r) / 2;
        if (a <= mid) sum = add(sum, query(2*k, l, mid, a, b));
        if (mid < b)  sum = add(sum, query(2*k+1, mid+1, r, a, b));
        return sum;
    }
};

int N, M;

int modp(int x) {
  int ret = x % P;
  if (ret < 0) ret += P;
  return ret;
}

int main() {
  scanf("%d%d%d", &N, &M, &P);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
    A[i] = modp(A[i]);
  }
  SegmentTree st(N);
  st.build();

  for (int i = 0; i < M; i++) {
    int t, x, y, k;
    scanf("%d", &t);
    if (t == 1) {
      scanf("%d%d%d", &x, &y, &k);
      st.mul(modp(k), x, y);
    } else if (t == 2) {
      scanf("%d%d%d", &x, &y, &k);
      st.add(modp(k), x, y);
    } else {
      scanf("%d%d", &x, &y);
      int ret = st.query(x, y);
      if (ret < 0) ret = (ret + P) % P;
      printf("%d\n", ret);
    }
  }

  return 0;
}
