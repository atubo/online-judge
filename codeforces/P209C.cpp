// https://codeforces.com/problemset/problem/209/C
// Trails and Glades

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

const int MAXN = 1000010;
int C[MAXN], D[MAXN];
int N, M;
int NG;
int O[MAXN], E[MAXN];
bool vis[MAXN];

void dfs(const Graph& g, int u, int id) {
  C[u] = id;
  vis[u] = true;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (!vis[v]) dfs(g, v, id);
  }
}

int main() {
  scanf("%d%d", &N, &M);
  Graph g(N, 2*M);
  for (int i = 0; i < M; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    g.addEdge(x, y);
    g.addEdge(y, x);
    D[x]++;
    D[y]++;
  }
  int np = 0;
  for (int i = 0; i < N; i++) {
    if (!vis[i]) dfs(g, i, np++);
  }
  for (int i = 0; i < N; i++) {
    if (D[i] & 1) O[C[i]]++;
    else if (i == 0 || D[i] > 0) E[C[i]]++;
  }
  int no = 0, ne = 0, oddSum = 0;
  for (int i = 0; i < np; i++) {
    if (O[i] > 0) {
      no++;
      oddSum += O[i]/2;
    }
    else if (E[i] > 0) {
      ne++;
    }
  }
  int ans = (ne + no > 1 ? ne + oddSum : oddSum);
  printf("%d\n", ans);
  return 0;
}
