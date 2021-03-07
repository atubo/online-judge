// https://www.luogu.com.cn/problem/P3356
// 火星探险问题

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
 public:
  struct Edge {
    int next, to, cap, cost;
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
  void addEdge(int u, int v, int cap, int cost) {
    E[eidx].to = v;
    E[eidx].next = head[u];
    E[eidx].cap = cap;
    E[eidx].cost = cost;
    head[u] = eidx++;
  }
};

const int INF = 0x3f3f3f3f;
const int DX[2] = {1, 0};
const int DY[2] = {0, 1};

class Solution {
 public:
  Solution(int n, int p, int q):
    n_(n), p_(p), q_(q), sz_(2*p*q+2), g_(sz_, 1e6) {
    s_ = 2*p_*q_;
    t_ = s_ + 1;
    alloc();
  }

  ~Solution() {
    dealloc();
  }

  void solve() {
    for (int i = 0; i < p_; i++) {
      for (int j = 0; j < q_; j++) {
        scanf("%d", &m_[i][j]);
      }
    }
    for (int i = 0; i < p_; i++) {
      for (int j = 0; j < q_; j++) {
        if (m_[i][j] == 1) continue;
        int u = getId(i, j);
        for (int k = 0; k < 2; k++) {
          int nx = i + DX[k];
          int ny = j + DY[k];
          if (nx >= p_ || ny >= q_) continue;
          if (m_[nx][ny] == 1) continue;
          int v = getId(nx, ny);
          g_.addEdge(u+p_*q_, v, INF, 0);
          g_.addEdge(v, u+p_*q_, 0, 0);
        }
        if (m_[i][j] == 2) {
          g_.addEdge(u, u+p_*q_, 1, 1);
          g_.addEdge(u+p_*q_, u, 0, -1);
        }
        g_.addEdge(u, u+p_*q_, INF, 0);
        g_.addEdge(u+p_*q_, u, 0, 0);
      }
    }

    if (m_[0][0] != 1) {
      g_.addEdge(s_, 0, n_, 0);
      g_.addEdge(0, s_, 0, 0);
    }
    if (m_[p_][q_] != 1) {
      g_.addEdge(getId(p_-1, q_-1) + p_*q_, t_, n_, 0);
      g_.addEdge(t_, getId(p_-1, q_-1) + p_*q_, 0, 0);
    }
    ek();
    for (int i = 1; i <= maxf_; i++) {
      dfs(0, 0, 0, i);
    }
  }

 private:
  const int n_, p_, q_;
  const int sz_;
  int s_, t_;
  Graph g_;
  bool *vis_;
  int *dis_;
  int *min_;
  int *pre_;
  int m_[40][40];
  int maxf_;

  void alloc() {
    vis_ = new bool[sz_]{};
    dis_ = new int[sz_]{};
    min_ = new int[sz_]{};
    pre_ = new int[sz_]{};
  }

  void dealloc() {
    delete[] vis_;
    delete[] dis_;
    delete[] min_;
    delete[] pre_;
  }

  bool spfa() {
    memset(vis_, 0, sz_*sizeof(bool));
    for (int i = 0; i <= t_; i++) dis_[i] = -INF;
    queue<int> q;
    q.push(s_);
    vis_[s_] = true;
    dis_[s_] = 0;
    min_[s_] = INF;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis_[u] = false;
      for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
        int v = g_.E[eidx].to;
        if (!g_.E[eidx].cap) continue;
        if (dis_[v] < dis_[u] + g_.E[eidx].cost) {
          dis_[v] = dis_[u] + g_.E[eidx].cost;
          min_[v] = min(min_[u], g_.E[eidx].cap);
          pre_[v] = eidx;
          if (!vis_[v]) {
            q.push(v);
            vis_[v] = true;
          }
        }
      }
    }
    return dis_[t_] != -INF;;
  }

  void ek() {
    maxf_ = 0;
    while (spfa()) {
      maxf_ += min_[t_];
      int u = t_;
      while (u != s_) {
        int i = pre_[u];
        g_.E[i].cap -= min_[t_];
        g_.E[i^1].cap += min_[t_];
        u = g_.E[i^1].to;
      }
    }
  }

  int getId(int x, int y) {
    return x * q_ + y;
  }

  void dfs(int x, int y, int u, int k) {
    int kx, ky, dir;
    for (int eidx = g_.head[u]; ~eidx; eidx = g_.E[eidx].next) {
      int v = g_.E[eidx].to;
      if (v == s_ || v == t_ || v == u-p_*q_ || !g_.E[eidx^1].cap) continue;
      g_.E[eidx^1].cap--;
      if (v >= p_*q_) {
        dfs(x, y, v, k);
        return;
      }
      if (v == getId(x, y) + 1) {
        kx = x;
        ky = y + 1;
        dir = 1;
      } else {
        kx = x + 1;
        ky = y;
        dir = 0;
      }
      printf("%d %d\n", k, dir);
      dfs(kx, ky, v + p_*q_, k);
      return;
    }
  }
};

int main() {
  int n, q, p;
  scanf("%d%d%d", &n, &q, &p);
  Solution solution(n, p, q);
  solution.solve();
  return 0;
}
