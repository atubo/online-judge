// https://www.luogu.com.cn/problem/P3590
// [POI2015]TRZ

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3F3F3F3F;
const int MAXN = 1000005;

struct Triplet {
  int x, y, z, id;
  bool operator < (const Triplet& other) {
    return x < other.x;
  }
} R[MAXN], A[MAXN], B[MAXN];

class SegmentTree {
  struct Node {
    int mn = INF, cmn = INF, mx = -1, cmx = -1;
  };
 public:
  SegmentTree(int n) : n_(n) {
    alloc();
  }

  ~SegmentTree() {
    dealloc();
  }

  int query(int x, int y, int v) {
    if (x > y) return 0;
    return query(1, 0, n_-1, x, y, v);
  }

  int query(int k, int l, int r, int x, int y, int v) {
    if (!k) return 0;
    if (x <= l && r <= y) {
      int amin, amax;
      if (val_[k].mn == INF) return 0;
      if (B[val_[k].mn].z == A[v].z) {
        amin = val_[k].cmn;
      } else {
        amin = val_[k].mn;
      }
      if (B[val_[k].mx].z == A[v].z) {
        amax = val_[k].cmx;
      } else {
        amax = val_[k].mx;
      }
      if (amin == INF || amax == -1) return 0;
      return max(abs(A[v].id-amin), abs(A[v].id-amax));
    }
    int mid = (l + r) / 2;
    int ans = 0;
    if (mid >= x) ans = max(ans, query(2*k, l, mid, x, y, v));
    if (mid < y) ans = max(ans, query(2*k+1, mid+1, r, x, y, v));
    return ans;
  }

  void update(int v) {
    update(1, 0, n_-1, v);
  }

  void update(int k, int l, int r, int v) {
    if (val_[k].mn > A[v].id) {
      if (val_[k].mn != INF && B[val_[k].mn].z != A[v].z) {
        val_[k].cmn = val_[k].mn;
      }
      val_[k].mn = A[v].id;
    } else if (val_[k].cmn > A[v].id && A[v].z != B[val_[k].mn].z) {
      val_[k].cmn = A[v].id;
    }
    if (val_[k].mx < A[v].id) {
      if (val_[k].mx != -1 && B[val_[k].mx].z != A[v].z) {
        val_[k].cmx = val_[k].mx;
      }
      val_[k].mx = A[v].id;
    } else if (val_[k].cmx < A[v].id && A[v].z != B[val_[k].mx].z) {
      val_[k].cmx = A[v].id;
    }
    if (l == r) return;
    int mid = (l + r) / 2;
    if (mid >= A[v].y) {
      update(2*k, l, mid, v);
    } else {
      update(2*k+1, mid+1, r, v);
    }
  }

 private:
  int n_;
  Node* val_;

  void alloc() {
    val_ = new Node[4*n_+1]{};
  }

  void dealloc() {
    delete[] val_;
  }
};

int N;
int X[MAXN], Y[MAXN], Z[MAXN];

void sortuniq(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

int findId(const vector<int>& v, int x) {
  return lower_bound(v.begin(), v.end(), x) - v.begin();
}

int main() {
  scanf("%d", &N);
  string s;
  cin >> s;
  for (int i = 1; i <= N; i++) {
    X[i] = X[i-1];
    Y[i] = Y[i-1];
    Z[i] = Z[i-1];
    if (s[i-1] == 'B') X[i] = X[i-1] + 1;
    if (s[i-1] == 'C') Y[i] = Y[i-1] + 1;
    if (s[i-1] == 'S') Z[i] = Z[i-1] + 1;
  }

  int ans = 0;
  int p = 0, q = 1;
  while (p < N) {
    while (q < N && s[q] == s[p]) q++;
    ans = max(ans, q-p);
    p = q;
  }

  vector<int> xs, ys, zs;
  A[0] = {0, 0, 0, 0};
  xs.push_back(0);
  ys.push_back(0);
  zs.push_back(0);
  for (int i = 1; i <= N; i++) {
    A[i].x = X[i] - Y[i];
    A[i].y = X[i] - Z[i];
    A[i].z = Y[i] - Z[i];
    A[i].id = i;
    xs.push_back(A[i].x);
    ys.push_back(A[i].y);
    zs.push_back(A[i].z);
  }

  sortuniq(xs);
  sortuniq(ys);
  sortuniq(zs);

  for (int i = 0; i <= N; i++) {
    A[i].x = findId(xs, A[i].x);
    A[i].y = findId(ys, A[i].y);
    A[i].z = findId(zs, A[i].z);
  }

  for (int i = 0; i <= N; i++) {
    B[i] = A[i];
  }
  sort(A, A+N+1);
  SegmentTree st(ys.size());
  p = 0, q = 1;
  while (p <= N) {
    while (q <= N && A[q].x == A[p].x) q++;
    for (int i = p; i < q; i++) {
      ans = max(ans, max(st.query(0, A[i].y-1, i),
                         st.query(A[i].y+1, ys.size()-1, i)));
    }
    for (int i = p; i < q; i++) {
      st.update(i);
    }
    p = q;
  }
  printf("%d\n", ans);

  return 0;
}
