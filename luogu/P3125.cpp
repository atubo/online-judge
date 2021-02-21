// https://www.luogu.com.cn/problem/P3125
// [USACO15OPEN]Bessie's Birthday Buffet S

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

const int MAXN = 1010;
int N;
int64_t E;
bool vis[MAXN];
int D[MAXN][MAXN];
int Q[MAXN];
int64_t dp[MAXN];
int P[MAXN];

void bfs(const Graph& g, int u) {
  memset(vis, 0, N*sizeof(bool));
  queue<int> q;
  D[u][u] = 0;
  vis[u] = true;
  q.push(u);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int eidx = g.head[x]; ~eidx; eidx = g.E[eidx].next) {
      int y = g.E[eidx].to;
      if (!vis[y]) {
        D[u][y] = min(D[u][y], D[u][x]+1);
        vis[y] = true;
        q.push(y);
      }
    }
  }
}

int main() {
  memset(D, 0x3F, sizeof(D));
  scanf("%d%ld", &N, &E);
  Graph g(N, 20*N);
  for (int i = 0; i < N; i++) {
    int d;
    scanf("%d%d", &Q[i], &d);
    for (int j = 0; j < d; j++) {
      int y;
      scanf("%d", &y);
      y--;
      g.addEdge(i, y);
      g.addEdge(y, i);
    }
  }
  for (int u = 0; u < N; u++) {
    bfs(g, u);
  }
  for (int i = 0; i < N; i++) {
    P[i] = i;
  }
  sort(P, P+N, [](int i, int j) { return Q[i] < Q[j]; });
  for (int i = 0; i < N; i++) {
    int u = P[i];
    dp[i] = Q[u];
    for (int j = i-1; j >= 0; j--) {
      int v = P[j];
      dp[i] = max(dp[i], dp[j] - E*D[u][v] + Q[u]);
    }
  }
  int64_t ans = 0;
  for (int i = 0; i < N; i++) {
    ans = max(ans, dp[i]);
  }
  printf("%ld\n", ans);
  return 0;
}
