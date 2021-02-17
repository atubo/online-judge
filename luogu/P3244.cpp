// https://www.luogu.com.cn/problem/P3244
// [HNOI2015]落忆枫音

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
 public:
  struct Edge {
    int next, to;
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
  void addEdge(int u, int v) {
    E[eidx].to = v;
    E[eidx].next = head[u];
    head[u] = eidx++;
  }
};

// Note: be sure it's DAG
class TopologicalSort {
 public:
  vector<int> topo;  // topologically sorted result

 private:
  void topologicalSortUtil(const Graph &g, int v, bool visited[],
      stack<int> &order) {
    visited[v] = true;

    for (int i = g.head[v]; i != -1; i = g.E[i].next) {
      int m = g.E[i].to;
      if (!visited[m]) {
        topologicalSortUtil(g, m, visited, order);
      }
    }

    order.push(v);
  }

 public:
  TopologicalSort() {}

  void sort(const Graph &g) {
    const int N = g.N;
    topo.resize(N);

    stack<int> order;
    bool visited[N];
    for (int i = 0; i < N; i++) {
      visited[i] = false;
    }

    for (int i = 0; i < N; i++) {
      if (!visited[i]) {
        topologicalSortUtil(g, i, visited, order);
      }
    }

    int i = 0;
    while (!order.empty()) {
      topo[i++] = order.top();
      order.pop();
    }
  }
};

const int MAXN = 100010;
const int MOD = 1000000007;
int N, M, X, Y;
int P;
int INV[MAXN];
int D[MAXN];
int dp[MAXN];

int add(int64_t a, int64_t b) {
  return (a + b) % MOD;
}

int mul(int64_t a, int64_t b) {
  return (a * b) % MOD;
}

int sub(int64_t a, int64_t b) {
  return (a + MOD - b) % MOD;
}

void init() {
  INV[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    INV[i] = mul(MOD-MOD/i, INV[MOD%i]);
  }
}

int main() {
  init();
  scanf("%d%d%d%d", &N, &M, &X, &Y);
  X--; Y--;

  Graph g(N, M);
  for (int i = 0; i < M; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    g.addEdge(u, v);
    D[v]++;
  }
  D[Y]++;
  TopologicalSort topo;
  topo.sort(g);

  P = 1;
  for (int i = 1; i < N; i++) {
    P = mul(P, D[topo.topo[i]]);
  }

  for (int u : topo.topo) {
    if (u == X) break;
    if (u == Y && u != 0) {
      dp[u] = mul(P, INV[D[u]]);
    }
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      dp[v] = add(dp[v], mul(dp[u], INV[D[v]]));
    }
  }
  int ans = sub(P, dp[X]);
  printf("%d\n", ans);

  return 0;
}
