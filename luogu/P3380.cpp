// https://www.luogu.com.cn/problem/P3380
// 【模板】二逼平衡树（树套树）

#include <bits/stdc++.h>
using namespace std;

struct SegmentInFenwick {
  int N;  // number of positions, index is 1-based
  int M;  // number of weights, index is 0-based
  int T_cnt;
  int *root;
  int *val, *lc, *rc;

  // cap is the number of elements to be added
  SegmentInFenwick(int N_, int M_, int cap): N(N_), M(M_), T_cnt(1) {
    root = new int[N+1]{};
    const int numOfNodes = cap * int(log2(N)+2) * int(log2(M)+2);
    val = new int[numOfNodes]{};
    lc = new int[numOfNodes]{};
    rc = new int[numOfNodes]{};
  }

  ~SegmentInFenwick() {
    delete[] root;
    delete[] val;
    delete[] lc;
    delete[] rc;
  }

  // add t to weight node w at position x
  void add(int x, int w, int t) {
    for (int i = x; i <= N; i += lowbit(i)) {
      update(root[i], w, t, 0, M-1);
    }
  }

  // weight sum [l, r] for position [1, k]
  int query(int k, int l, int r) const {
    if (l > r) return 0;
    int sum = 0;
    for (int j = k; j; j -= lowbit(j)) {
      sum += querySingleTree(root[j], 0, M-1, l, r);
    }
    return sum;
  }

  // weight sum [l, r] for position [p, q]
  int query(int p, int q, int l, int r) const {
    return query(q, l, r) - query(p-1, l, r);
  }

  int nth(int p, int q, int k) const {
    assert(q-p+1 >= k);
    int lo = -1, hi = M;
    while (lo < hi-1) {
      int mid = (lo + hi) / 2;
      if (query(p, q, 0, mid) < k) lo = mid;
      else hi = mid;
    }
    return hi;
  }

  int rank(int p, int q, int k) const {
    return query(p, q, 0, k-1) + 1;
  }

  int pred(int p, int q, int k) const {
    int r = rank(p, q, k);
    if (r == 1) return -1;
    return nth(p, q, r-1);
  }

  int succ(int p, int q, int k) const {
    int r = rank(p, q, k);
    if (r == q - p + 2) return -1;
    return nth(p, q, r);
  }

 private:
  int lowbit(int x) const {return x & -x;}

  void update(int &now, int w, int t, int l, int r) {
    if (!now) now = T_cnt++;
    val[now] += t;
    if (l == r) return;
    int mid = (l + r) / 2;
    if (w <= mid) update(lc[now], w, t, l, mid);
    else          update(rc[now], w, t, mid+1, r);
  }

  int querySingleTree(int node, int L, int R, int l, int r) const {
    if (L >= l && R <= r) return val[node];
    if (L > r || R < l) return 0;
    int sum = 0;
    int mid = (L + R) / 2;
    if (l <= mid) sum += querySingleTree(lc[node], L, mid, l, r);
    if (mid < r)  sum += querySingleTree(rc[node], mid+1, R, l, r);
    return sum;
  }
};

const int MAXN = 50010;
int N, M;

struct Query {
  int op, l, r, k;
} Q[MAXN];

int A[MAXN];
vector<int> S;

int lower(int x) {
  return lower_bound(S.begin(), S.end(), x) - S.begin();
}

int upper(int x) {
  return upper_bound(S.begin(), S.end(), x) - S.begin();
}

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
    S.push_back(A[i]);
  }
  int cnt = 0;
  for (int i = 0; i < M; i++) {
    int op, l, r=0, k;
    scanf("%d", &op);
    if (op == 3) {
      scanf("%d%d", &l, &k);
      S.push_back(k);
      cnt++;
    } else {
      scanf("%d%d%d", &l, &r, &k);
    }
    Q[i] = {op, l, r, k};
  }
  sort(S.begin(), S.end());
  S.erase(unique(S.begin(), S.end()), S.end());

  SegmentInFenwick sif(N, S.size(), N+cnt);
  for (int i = 1; i <= N; i++) {
    A[i] = lower(A[i]);
    sif.add(i, A[i], 1);
  }

  for (int i = 0; i < M; i++) {
    switch (Q[i].op) {
      case 1:
        {
          int x = lower(Q[i].k);
          printf("%d\n", sif.rank(Q[i].l, Q[i].r, x));
          break;
        }
      case 2:
        {
          int x = sif.nth(Q[i].l, Q[i].r, Q[i].k);
          printf("%d\n", S[x]);
          break;
        }
      case 3:
        {
          int x = Q[i].l;
          int w0 = A[x];
          int w1 = lower(Q[i].k);
          sif.add(Q[i].l, w0, -1);
          sif.add(Q[i].l, w1, 1);
          A[x] = w1;
          break;
        }
      case 4:
        {
          int x = sif.pred(Q[i].l, Q[i].r, lower(Q[i].k));
          if (x == -1) {
            printf("-2147483647\n");
          } else {
            printf("%d\n", S[x]);
          }
          break;
        }
      case 5:
        {
          int x = sif.succ(Q[i].l, Q[i].r, upper(Q[i].k));
          if (x == -1) {
            printf("2147483647\n");
          } else {
            printf("%d\n", S[x]);
          }
          break;
        }
      default:
        assert(0);
        break;
    }
  }

  return 0;
}
