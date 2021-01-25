// https://www.luogu.com.cn/problem/P4366
// [Code+#4]最短路

#include <bits/stdc++.h>
using namespace std;

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
int C;

class FastDijkstra {
 public:
  FastDijkstra(int N_): N(N_) {
    alloc();
  }

  ~FastDijkstra() {
    dealloc();
  }

  int getDist(int t) const {
    return dist[t];
  }

  void solve(const Graph& g, int s, int t) {
    // use priority queue in which top element has the "smallest" priority
    priority_queue<int64_t, vector<int64_t>, greater<int64_t> > Q;
    Q.push(s);
    dist[s] = 0;
    while (!Q.empty()){
      int64_t p = Q.top();
      // break here if we want to stop when we find a target node
      Q.pop();

      int u = p & INT_MAX;
      if (u == t) return;
      for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
        int v = g.E[eidx].to;
        int w = g.E[eidx].wt;
        if (dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
          Q.push(((1LL*dist[v]) << 32) | v);
        }
      }
      const int m = 32 - __builtin_clz(N);
      for (int i = 0; i < m; i++) {
        int v = u ^ (1<<i);
        if (v < N) {
          if (dist[u] + (C<<i) < dist[v]) {
            dist[v] = dist[u] + (C<<i);
            Q.push(((1LL*dist[v]) << 32) | v);
          }
        }
      }
    }
  }

 private:
  const int N;
  int* dist;

  void alloc() {
    dist = new int[N]{};
    memset(dist, 0x7F, N*sizeof(int));
  }

  void dealloc() {
    delete[] dist;
  }
};

int N, M;

int main() {
  scanf("%d%d%d", &N, &M, &C);
  Graph g(N+1, M);
  for (int i = 0; i < M; i++) {
    int f, t, v;
    scanf("%d%d%d", &f, &t, &v);
    g.addEdge(f, t, v);
  }
  FastDijkstra dij(N+1);
  int a, b;
  scanf("%d%d", &a, &b);
  dij.solve(g, a, b);
  printf("%d\n", dij.getDist(b));
  return 0;
}
