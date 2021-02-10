// https://www.luogu.com.cn/problem/P3771
// [CTSC2017]网络

#include <bits/stdc++.h>
using namespace std;

const int64_t INF = 0x3f3f3f3f3f3f3f3f;

// Note graph node is 0-indexed
class Graph {
 public:
  struct Edge {
    int next, to, wt;
  };

  vector<int> head;
  int eidx;
  int N, M;

  Edge *E;

  Graph(int N_, int M_):N(N_), M(M_) {
    head.resize(N);
    eidx = 0;

    for (int i = 0; i < N; i++) {
      head[i] = -1;
    }

    E = new Edge[M]{};
  }

  ~Graph() {
    delete[] E;
  }

  // assume 0-indexed and no duplication
  void addEdge(int u, int v, int w) {
    E[eidx].to = v;
    E[eidx].wt = w;
    E[eidx].next = head[u];
    head[u] = eidx++;
  }
};

class Solution {
 public:
  Solution(int n, int l) : n_(n), l_(l), g_(n+1, 2*(n-1)) {
    alloc();
  }

  ~Solution() {
    dealloc();
  }

  void solve() {
    for (int i = 0; i < n_-1; i++) {
      int a, b, l;
      scanf("%d%d%d", &a, &b, &l);
      g_.addEdge(a, b, l);
      g_.addEdge(b, a, l);
    }

    init();

    for (int i = 1; i <= cnt_; i++) {
      tmp_ = 0;
      dfs2(q_[i], 0, 0);
      d_[i] = depth_[q_[i]];
      dis_[i] = tmp_;
      a_[i] = b_[i] = i;
    }
    sort(a_+1, a_+cnt_+1, [this](int x, int y) {
        return d_[x] + dis_[x] < d_[y] + dis_[y];
        });
    sort(b_+1, b_+cnt_+1, [this](int x, int y) {
        return d_[x] - dis_[x] < d_[y] - dis_[y];
        });
    int64_t lo = -1, hi = d_[cnt_];
    while (lo < hi-1) {
      int64_t mid = (lo + hi) / 2;
      if (check(mid)) hi = mid;
      else lo = mid;
    }
    printf("%ld\n", hi);
  }

  void dfs(int u, int f, int64_t z) {
    depth_[u] = z;
    fa_[u] = f;
    if (z > depth_[rt_]) rt_ = u;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      int w = g_.E[eidx].wt;
      if (v != f) dfs(v, u, z+w);
    }
  }

  void dfs2(int u, int f, int64_t z) {
    if (z > tmp_) tmp_ = z;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      int w = g_.E[eidx].wt;
      if (v != f && !on_[v]) dfs2(v, u, z+w);
    }
  }

  void init() {
    dfs(rt_=1, 0, 0);
    dfs(A=rt_, 0, 0);
    B = rt_;

    for (int i = B; i != A; i = fa_[i]) {
      on_[q_[++cnt_]=i] = true;
    }
    on_[q_[++cnt_]=A] = true;
    reverse(q_+1, q_+cnt_+1);
  }

  bool check(int64_t mid) {
    int64_t al = -INF, bl = -INF, amx = -INF;
    int64_t ar = INF, br = INF, bmi = INF;
    for (int i = 1, j = 1; i <= cnt_; i++) {
      while (j <= cnt_ &&
          d_[a_[i]] + dis_[a_[i]] - d_[b_[j]] + dis_[b_[j]] > mid) {
        amx = max(amx, d_[b_[j]]+dis_[b_[j]]);
        bmi = min(bmi, d_[b_[j]]-dis_[b_[j]]);
        j++;
      }
      if (j > 1) {
        al = max(al, d_[a_[i]]+dis_[a_[i]]+amx);
        ar = min(ar, d_[a_[i]]-dis_[a_[i]]+bmi);
        bl = max(bl, d_[a_[i]]+dis_[a_[i]]-bmi);
        br = min(br, d_[a_[i]]-dis_[a_[i]]-amx);
      }
    }
    al += l_ - mid;
    ar += mid - l_;
    bl += l_ - mid;
    br += mid - l_;
    if (al > ar || bl > br) return false;
    for (int i=1, j=1, k=1, x=cnt_, y=cnt_; i <= cnt_; i++) {
      while (j <= cnt_ && d_[i] - d_[j] >= bl) ++j;
      while (k <= cnt_ && d_[i] - d_[k] > br) ++k;
      while (x && d_[i] + d_[x] >= al) --x;
      while (y && d_[i] + d_[y] > ar) --y;
      if (max(k, x+1) <= min(j-1, y)) return true;
    }
    return false;
  }


 private:
  int n_;
  int64_t l_;
  Graph g_;
  int64_t* depth_;
  int* fa_;
  bool* on_;
  int rt_ = 0;
  int64_t tmp_ = 0;
  int A = 0;
  int B = 0;
  int cnt_ = 0;
  int* q_;
  int64_t* d_;
  int* a_;
  int* b_;
  int64_t* dis_;

  void alloc() {
    depth_ = new int64_t[n_+1]{};
    fa_ = new int[n_+1]{};
    on_ = new bool[n_+1]{};
    q_ = new int[n_+1]{};
    d_ = new int64_t[n_+1]{};
    a_ = new int[n_+1]{};
    b_ = new int[n_+1]{};
    dis_ = new int64_t[n_+1]{};
  }

  void dealloc() {
    delete[] depth_;
    delete[] fa_;
    delete[] on_;
    delete[] q_;
    delete[] d_;
    delete[] a_;
    delete[] b_;
    delete[] dis_;
  }
};

int main() {
  while (true) {
    int n, l;
    scanf("%d%d", &n, &l);
    if (n == 0 && l == 0) break;
    Solution solution(n, l);
    solution.solve();
  }
  return 0;
}
