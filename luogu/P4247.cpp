// https://www.luogu.com.cn/problem/P4247
// [清华集训2012]序列操作

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;
const int MOD = 19940417;
int A[MAXN];
int C[MAXN][21];

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

// note it's 1-indexed
class SegmentTree {
  struct Node {
    Node() {
      c1 = c2 = 0;
      memset(c, 0, sizeof(c));
    }
    int64_t c[21], c1;
    bool c2;
  };
  int N;
  Node* nodes_;

 public:
  SegmentTree(int N_): N(N_) {
    nodes_ = new Node[4*N+1]{};
  }

  ~SegmentTree() {
    delete[] nodes_;
  }

  void build() {
    build(1, 0, N-1);
  }

  void modify1(int a, int b, int c) {
    modify1(1, 0, N-1, a, b, c);
  }

  void modify2(int a, int b) {
    modify2(1, 0, N-1, a, b);
  }

  int query(int a, int b, int c) {
    return query(1, 0, N-1, a, b).c[c];
  }

 private:
  void build(int k, int l, int r) {
    if (l == r) {
      nodes_[k].c[0] = 1;
      nodes_[k].c[1] = (A[l]%MOD + MOD) % MOD;
      return;
    }
    int mid = (l + r) / 2;
    build(2*k, l, mid);
    build(2*k+1, mid+1, r);
    pushUp(k, l, r);
  }

  void incr(int k, int l, int r, int t) {
    assert(t >= 0);
    if (!t) return;
    int tmp[21] = {0};
    tmp[0] = 1;
    for (int i = 1; i <= min(20, r-l+1); i++) {
      tmp[i] = (1LL * tmp[i-1] * t) % MOD;
    }
    for (int i = min(20, r-l+1); i > 0; i--) {
      for (int j = 0; j < i; j++) {
        nodes_[k].c[i] = add(nodes_[k].c[i],
            mul(mul(nodes_[k].c[j], tmp[i-j]), C[r-l+1-j][i-j]));
      }
    }
    nodes_[k].c1 = (nodes_[k].c1 + t) % MOD;
  }

  void rev(int k, int l, int r) {
    for (int i = 1; i <= min(r-l+1, 20); i++) {
      if (i & 1) nodes_[k].c[i] = (MOD - nodes_[k].c[i]) % MOD;
    }
    nodes_[k].c1 = (MOD - nodes_[k].c1) % MOD;
    nodes_[k].c2 ^= 1;
  }

  void pushDown(int k, int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    if (nodes_[k].c2) {
      rev(2*k, l, mid);
      rev(2*k+1, mid+1, r);
      nodes_[k].c2 = 0;
    }
    if (nodes_[k].c1) {
      incr(2*k, l, mid, nodes_[k].c1);
      incr(2*k+1, mid+1, r, nodes_[k].c1);
      nodes_[k].c1 = 0;
    }
  }

  void pushUp(int k, int l, int r) {
    assert(l != r);
    memset(nodes_[k].c, 0, sizeof(nodes_[k].c));
    int mid = (l + r) / 2;
    for (int i = 0; i <= min(20, mid-l+1); i++) {
      for (int j = 0; j <= min(20-i, r-mid); j++) {
        nodes_[k].c[i+j] =
            add(nodes_[k].c[i+j], mul(nodes_[2*k].c[i], nodes_[2*k+1].c[j]));
      }
    }
  }

  void modify1(int k, int l, int r, int a, int b, int t) {
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      incr(k, l, r, t);
      return;
    }
    int mid = (l + r) / 2;
    if (a <= mid) modify1(2*k, l, mid, a, b, t);
    if (mid < b) modify1(2*k+1, mid+1, r, a, b, t);
    pushUp(k, l, r);
  }

  void modify2(int k, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      rev(k, l, r);
      return;
    }
    int mid = (l + r) / 2;
    if (a <= mid) modify2(2*k, l, mid, a, b);
    if (mid < b) modify2(2*k+1, mid+1, r, a, b);
    pushUp(k, l, r);
  }

  struct Result {
    Result(int64_t* c1, int sz1) {
      memcpy(c, c1, sizeof(c));
      sz = sz1;
    }
    int64_t c[21];
    int sz;
  };

  Result merge(const Result& r1, const Result& r2) {
    int sz = r1.sz + r2.sz;
    int64_t c[21] = {0};
    for (int i = 0; i <= min(20, r1.sz); i++) {
      for (int j = 0; j <= min(20-i, r2.sz); j++) {
        c[i+j] = add(c[i+j], mul(r1.c[i], r2.c[j]));
      }
    }
    return Result{c, sz};
  }

  Result query(int k, int l, int r, int a, int b) {
    pushDown(k, l, r);
    if (a <= l && r <= b) {
      return Result{nodes_[k].c, r-l+1};
    }
    int mid = (l + r) / 2;
    if (b <= mid) return query(2*k, l, mid, a, b);
    else if (mid < a) return query(2*k+1, mid+1, r, a, b);
    return merge(query(2*k, l, mid, a, b), query(2*k+1, mid+1, r, a, b));
  }
};

int N, Q;

void init() {
  C[0][0] = 1;
  for (int i = 1; i <= N; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= min(20, i); j++) {
      C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
    }
  }
}

int main() {
  scanf("%d%d", &N, &Q);
  init();
  for (int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
    A[i] = (A[i]%MOD + MOD) % MOD;
  }
  SegmentTree st(N);
  st.build();
  char op[5];
  int a, b, c;
  for (int i = 0; i < Q; i++) {
    scanf("%s%d%d", op, &a, &b);
    a--; b--;
    if (op[0] == 'I') {
      scanf("%d", &c);
      st.modify1(a, b, (c%MOD+MOD)%MOD);
    } else if (op[0] == 'R') {
      st.modify2(a, b);
    } else {
      scanf("%d", &c);
      printf("%d\n", st.query(a, b, c));
    }
  }
  return 0;
}
