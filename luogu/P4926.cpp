// https://www.luogu.com.cn/problem/P4926
// [1007]倍杀测量者

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to;
        double wt;
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
    void addEdge(int u, int v, double w) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].wt = w;
        head[u] = eidx++;
    }
};

const int INF = 1e9;
const int MAXN = 1010;
int N;
double D[MAXN];

// returns true if g has no negative weigth cycle
bool bellman(const Graph &g) {
  for (int i = 1; i <= N; i++) {
    D[i] = INF;
  }

  for (int i = 0; i < N-1; i++) {
    for (int u = 0; u <= N; u++) {
      if (D[u] == INF) continue;
      for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        double w = g.E[eidx].wt;
        D[v] = min(D[v], D[u] + w);
      }
    }
  }

  int ret = true;
  for (int u = 0; u <= N; u++) {
    if (D[u] == INF) continue;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      double w = g.E[eidx].wt;
      if (D[u] + w < D[v]) {
        ret = false;
        break;
      }
    }
  }
  return ret;
}

double EPS = 1e-20;

class Solution {
 private:
  int n_, s_, t_;
  Graph g_;
  vector<int> w_;
  vector<int> op_;

 public:
  Solution(int n, int s, int t)
      : n_(n), s_(s), t_(t), g_(n+1, s+2*t), w_(s), op_(s) {
    for (int i = 0; i < s; i++) {
      int o, a, b, k;
      scanf("%d%d%d%d", &o, &a, &b, &k);
      op_[i] = o;
      w_[i] = k;
      g_.addEdge(a, b, 0);
    }
    for (int i = 0; i < t; i++) {
      int c, x;
      scanf("%d%d", &c, &x);
      g_.addEdge(0, c, log(x));
      g_.addEdge(c, 0, -log(x));
    }
  }

  void update(double t) {
    for (int i = 0; i < s_; i++) {
      if (op_[i] == 1) {
        if (w_[i] > t)  g_.E[i].wt = -log(w_[i] - t);
        else g_.E[i].wt = INF;
      } else {
        g_.E[i].wt = log(w_[i] + t) + EPS;
      }
    }
  }

  void solve() {
    update(0);
    if (bellman(g_)) {
      printf("-1\n");
      return;
    }
    double delta = 1e-7;
    double lo = 0, hi = 1e9;
    while (lo < hi - delta) {
      double mid = (lo + hi) / 2;
      update(mid);
      if (bellman(g_)) hi = mid;
      else lo = mid;
    }
    printf("%.6f\n", lo);
  }
};

int main() {
  int s, t;
  scanf("%d%d%d", &N, &s, &t);
  Solution solution(N, s, t);
  solution.solve();

  return 0;
}
