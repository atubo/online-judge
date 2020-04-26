// https://www.luogu.com.cn/problem/P1399
// [NOI2013]快餐店

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;

using PQ = __gnu_pbds::priority_queue<int64_t>;
using PQIter = PQ::point_iterator;

int64_t max3(int64_t a, int64_t b, int64_t c) {
  return max(a, max(b, c));
}

class BaseTree {
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
      E[eidx].next = head[u];
      E[eidx].wt = w;
      head[u] = eidx++;
    }
  };

  class Ring {
   public:
    Ring(int n): n_(n) {
      alloc();
    }

    ~Ring() {
      dealloc();
    }

    int* w;   // distance to the next node
    int64_t* d;   // depth of its tree
   private:
    const int n_;

    void alloc() {
      w = new int[n_]{};
      d = new int64_t[n_]{};
    }

    void dealloc() {
      delete[] w;
      delete[] d;
    }
  };

 public:
  BaseTree(int n): n_(n), g_(n, 2*n) {
    alloc();
  }

  ~BaseTree() {
    dealloc();
  }

  void addEdge(int u, int v, int w) {
    g_.addEdge(u, v, w);
    g_.addEdge(v, u, w);
  }

  void build() {
    dfs1(0, -1);
    for (int x : rng_) {
      dfs2(x, -1);
    }
    Ring ring(rng_.size());
    for (int i = 0; i < (int)rng_.size(); i++) {
      int u = rng_[i];
      int v = rng_[(i+1)%rng_.size()];
      ring.d[i] = maxd_[u];
      for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
        if (g_.E[eidx].to == v) {
          ring.w[i] = g_.E[eidx].wt;
          break;
        }
      }
    }

    vector<int64_t> L(rng_.size());
    L[0] = 0;
    for (int i = 1; i < (int)rng_.size(); i++) {
      L[i] = ring.w[i-1] + L[i-1];
    }
    const int m = rng_.size();
    const int64_t C = L[m-1] + ring.w[m-1];
    PQ pq1, pq2;
    vector<PQIter> iters(m);
    int l = -1, r = m;
    for (int i = 1; i < m; i++) {
      if (L[i] <= C - L[i]) {
        iters[i] = pq1.push(L[i] + ring.d[i]);
      } else {
        r = i;
        break;
      }
    }
    for (int i = r; i < m; i++) {
      iters[i] = pq2.push(C - L[i] + ring.d[i]);
    }
    vector<int64_t> left(m), right(m);
    left[0] = pq2.empty() ? -1 : pq2.top();
    right[0] = pq1.empty() ? -1 : pq1.top();
    for (int i = 1; i < m; i++) {
      if (r <= i) pq2.erase(iters[i]);
      else pq1.erase(iters[i]);
      iters[i-1] = pq2.push(-L[i-1] + ring.d[i-1]);
      while (l+1 < i && L[i] - L[l+1] > C - (L[i] - L[l+1])) {
        l++;
        movepq(l, C + L[l] + ring.d[l], pq2, pq1, iters);
      }
      r = max(r, i+1);
      while (r < m && L[r] - L[i] <= C - (L[r] - L[i])) {
        movepq(r, L[r] + ring.d[r], pq2, pq1, iters);
        r++;
      }

      left[i] = pq2.empty() ? -1 : pq2.top() + L[i];
      right[i] = pq1.empty() ? -1 : pq1.top() - L[i];
    }
    double ans = 1e30;
    for (int i = 0; i < m; i++) {
      ans = min(ans, (double)max3(right[i], left[i], ring.d[i]));
      if (right[i] > max(left[i], ring.d[i])) {
        double x = min((double)ring.w[i], (right[i]-max(left[i], ring.d[i]))/2.0);
        ans = min(ans, right[i]-x);
      }
      if (left[i] > max(right[i], ring.d[i])) {
        double x = min((double)ring.w[(i+m-1)%m],
                       (left[i]-max(right[i], ring.d[i]))/2.0);
        ans = min(ans, left[i]-x);
      }
      if (ring.d[i] > max(left[i], right[i])) {
        ans = min(ans, dfs3(rng_[i], -1, max(left[i], right[i])) / 2.0);
      }
    }
    printf("%.1f\n", ans);
  }

 private:
  int n_;
  Graph g_;

  int* fa_;
  bool* vis_;
  int* nb_[2];
  int64_t* maxd_;
  int* fw_;   // weight of the father edge
  vector<int> rng_;

  void alloc() {
    fa_ = new int[n_]{};
    vis_ = new bool[n_]{};
    nb_[0] = new int[n_]{};
    nb_[1] = new int[n_]{};
    memset(nb_[0], -1, n_*sizeof(int));
    memset(nb_[1], -1, n_*sizeof(int));
    maxd_ = new int64_t[n_]{};
    fw_ = new int[n_]{};
  }

  void dealloc() {
    delete[] fa_;
    delete[] vis_;
    delete[] nb_[0];
    delete[] nb_[1];
    delete[] maxd_;
    delete[] fw_;
  }

  // to find the loop
  bool dfs1(int u, int f) {
    fa_[u] = f;
    vis_[u] = true;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (v != f) {
        if (vis_[v]) {
          traverse(u, v);
          return true;
        }
        if (dfs1(v, u)) return true;
      }
    }
    return false;
  }

  // traverse the loop, start point u, end point v
  void traverse(int u, int v) {
    int x = u, last = v;
    while (x != v) {
      nb_[0][x] = fa_[x];
      nb_[1][x] = last;
      rng_.push_back(x);
      last = x;
      x = fa_[x];
    }
    nb_[0][x] = u;
    nb_[1][x] = last;
    rng_.push_back(x);
  }

  // start from each node in the root, collect stat of subtree
  void dfs2(int u, int f) {
    maxd_[u] = 0;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      int w = g_.E[eidx].wt;
      if (v != nb_[0][u] && v != nb_[1][u] && v != f) {
        fw_[v] = w;
        dfs2(v, u);
        maxd_[u] = max(maxd_[u], maxd_[v] + w);
      }
    }
  }

  int64_t dfs3(int u, int f, int64_t up) {
    vector<pair<int64_t, int>> d;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      int w = g_.E[eidx].wt;
      if (v != nb_[0][u] && v != nb_[1][u] && v != f) {
        d.push_back(make_pair(maxd_[v] + w, v));
      }
    }
    sort(d.begin(), d.end(), greater<pair<int64_t, int>>());
    if (d.empty()) return up;
    if (d.size() == 1) {
      int v = d[0].second;
      return dfs3(v, u, up + fw_[v]);
    } else {
      int v = d[0].second;
      return dfs3(v, u, max(up, d[1].first) + fw_[v]);
    }
  }

  void movepq(int i, int64_t x, PQ& pq1, PQ& pq2, vector<PQIter>& iters) {
    pq1.erase(iters[i]);
    iters[i] = pq2.push(x);
  }
};

int N;

int main() {
  scanf("%d", &N);
  BaseTree bt(N);
  for (int i = 0; i < N; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--; v--;
    bt.addEdge(u, v, w);
  }
  bt.build();
  return 0;
}
