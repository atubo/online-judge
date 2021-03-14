//https://www.luogu.com.cn/problem/P3835
// 【模板】可持久化平衡树

#include <bits/stdc++.h>
using namespace std;

const int INF = 2147483647;
vector<int> S;

class PersistentSegmentTree {
 public:
  struct Node {
    // L and R are indices of its children
    // real left and right boundaries are not kept in the node
    // to save memory
    int L, R;
    int sum;

    Node(): L(0), R(0), sum(0) {}
  };

  int N; // number of positions, index is 1-based
  int M; // number of weights, index is 0-based
  int *root;
  Node *T;
  int T_cnt = 1;

  PersistentSegmentTree(int N_, int M_): N(N_), M(M_) {
    root = new int[N+1]{};
    T = new Node[(N+1) * int(log2(M)+2)]{};
  }

  ~PersistentSegmentTree() {
    delete[] root;
    delete[] T;
  }

  // for user's convenience
  void insert(int currRootIndex, int prevRootIndex, int x, int t) {
    root[currRootIndex] = root[prevRootIndex];
    insert(root[currRootIndex], x, t, 0, M-1);
  }

  void remove(int currRootIndex, int prevRootIndex, int x) {
    root[currRootIndex] = root[prevRootIndex];
    remove(root[currRootIndex], x, 0, M-1);
  }

  // query in range [start, end]
  int query(int rootIndex, int start, int end) const {
    return query(root[rootIndex], start, end, 0, M-1);
  }

  int rank(int rootIndex, int x) const {
    if (x < 0) return 1;
    if (x >= M) return T[root[rootIndex]].sum + 1;
    return rank(root[rootIndex], x, 0, M-1) + 1;
  }

  int findByRank(int rootIndex, int x) const {
    assert(1 <= x && x <= T[root[rootIndex]].sum);
    return findByRank(root[rootIndex], x-1, 0, M-1);
  }

  int predecessor(int rootIndex, int x) const {
    int r = rank(rootIndex, x);
    if (r <= 1) return -INF;
    return findByRank(rootIndex, r-1);
  }

  int successor(int rootIndex, int x) const {
    int r = rank(rootIndex, x);
    if (r > T[root[rootIndex]].sum) return INF;
    return findByRank(rootIndex, r);
  }

  void print(int rootIndex) const {
    print(root[rootIndex], 0, M-1);
  }

  void link(int x, int y) {
    root[x] = root[y];
  }

 private:
  // insert a new weight node x with value t
  // current range is [l, r]
  void insert(int &now, int x, int t, int l, int r) {
    T[T_cnt++] = T[now];
    now = T_cnt-1;
    T[now].sum += t;
    if (l == r) return;
    int mid = (l + r) / 2;
    if (x <= mid) insert(T[now].L, x, t, l, mid);
    else          insert(T[now].R, x, t, mid+1, r);
  }

  bool remove(int &now, int x, int l, int r) {
    if (now == 0) return false;
    T[T_cnt++] = T[now];
    now = T_cnt-1;
    if (l == r) {
      return T[now].sum--;
    }
    bool found;
    int mid = (l + r) / 2;
    if (x <= mid) found = remove(T[now].L, x, l, mid);
    else          found = remove(T[now].R, x, mid+1, r);
    T[now].sum -= found;
    return found;
  }

  int query(int node, int start, int end, int l, int r) const {
    if (l > r) return 0;
    if (start <= l && r <= end) return T[node].sum;
    int mid = (l + r) / 2;
    int ret = 0;
    if (start <= mid) ret += query(T[node].L, start, end, l, mid);
    if (mid+1 <= end) ret += query(T[node].R, start, end, mid+1, r);
    return ret;
  }

  int rank(int node, int x, int l, int r) const {
    if (l == r) return 0;
    int mid = (l + r) / 2;
    if (x > mid) return T[T[node].L].sum + rank(T[node].R, x, mid+1, r);
    return rank(T[node].L, x, l, mid);
  }

  int findByRank(int node, int x, int l, int r) const {
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (x >= T[T[node].L].sum) {
      return findByRank(T[node].R, x - T[T[node].L].sum, mid+1, r);
    }
    return findByRank(T[node].L, x, l, mid);
  }

  void print(int node, int l, int r) const {
    if (node == 0) return;
    if (l == r) {
      for (int i = 0; i < T[node].sum; i++) {
        printf("%d ", S[l]);
      }
      return;
    }
    int mid = (l + r) / 2;
    print(T[node].L, l, mid);
    print(T[node].R, mid+1, r);
  }
};

const int MAXN = 500010;
struct Query {
  int v, op, x;
} Q[MAXN];
int N;

int findIndex(int x) {
  return lower_bound(S.begin(), S.end(), x) - S.begin();
}

int findIndex2(int x) {
  return upper_bound(S.begin(), S.end(), x) - S.begin();
}

int main() {
  scanf("%d", &N);
  for (int i = 1; i <= N; i++) {
    scanf("%d%d%d", &Q[i].v, &Q[i].op, &Q[i].x);
    if (Q[i].op <= 2) S.push_back(Q[i].x);
  }
  sort(S.begin(), S.end());
  S.erase(unique(S.begin(), S.end()), S.end());
  int m = S.size();
  PersistentSegmentTree pst(N, m);
  for (int i = 1; i <= N; i++) {
    if (Q[i].op == 1) {
      int x = findIndex(Q[i].x);
      pst.insert(i, Q[i].v, x, 1);
    } else if (Q[i].op == 2) {
      int x = findIndex(Q[i].x);
      pst.remove(i, Q[i].v, x);
    } else if (Q[i].op == 3) {
      int x = findIndex(Q[i].x);
      printf("%d\n", pst.rank(Q[i].v, x));
      pst.link(i, Q[i].v);
    } else if (Q[i].op == 4) {
      int x = pst.findByRank(Q[i].v, Q[i].x);
      printf("%d\n", S[x]);
      pst.link(i, Q[i].v);
    } else if (Q[i].op == 5) {
      int x = findIndex(Q[i].x);
      int y = pst.predecessor(Q[i].v, x);
      if (y == -INF) printf("%d\n", -INF);
      else printf("%d\n", S[y]);
      pst.link(i, Q[i].v);
    } else {
      int x = findIndex2(Q[i].x);
      int y = pst.successor(Q[i].v, x);
      if (y == INF) printf("%d\n", INF);
      else printf("%d\n", S[y]);
      pst.link(i, Q[i].v);
    }
#if 0
    printf("i=%d ", i);
    pst.print(i);
    printf("\n");
#endif
  }
  return 0;
}
