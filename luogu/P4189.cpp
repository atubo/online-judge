// https://www.luogu.com.cn/problem/P4189
// [CTSC2010]星际旅行

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

const int MAXN = 50010;
int N;
int H[MAXN];
int F[MAXN], F0[MAXN], G[MAXN], G0[MAXN], S[MAXN];
int ans[MAXN];

void dfs1(const Graph& g, int u, int f) {
  F[u] = H[u];
  G[u] = 0;
  int s = 0;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v == f) continue;
    dfs1(g, v, u);
    if (F[v] <= 0) G[u] += G[v];
    else G[u] += G[v] + 2;
    F[u]--;
    s += max(0, F[v]-1);
  }
  S[u] = s;
  s = min(F[u], s);
  F0[u] = F[u];
  F[u] -= s;
  G0[u] = G[u];
  G[u] += 2*s;
}

pair<int, int> cancel(int u, int v) {
  int s = S[u];
  int f0 = F0[u] + 1;
  int g0 = G0[u] - G[v] - (F[v] <= 0 ? 0 : 2);
  s -= max(0, F[v] - 1);
  s = min(f0, s);
  int fu = f0 - s;
  int gu = g0 + 2*s;
  return make_pair(fu, gu);
}

pair<int, int> merge(int f0, int g0, int f1, int g1) {
  int g = g1;
  if (f0 <= 0) g += g0 - 1;
  else g += g0 + 1;
  g += 2 * min(max(0, f1), max(0, f0-1));
  int f = f1 - min(max(0, f0-1), f1);
  return make_pair(f, g);
}

void dfs2(const Graph& g, int f0, int g0, int u, int fa) {
  if (f0 <= 0) ans[u] = G[u] + g0 - 1;
  else ans[u] = G[u] + g0 + 1;
  ans[u] += 2 * min(max(0, F[u]), max(0, f0-1));
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v == fa) continue;
    int fup, gup;
    tie(fup, gup) = cancel(u, v);
    if (fa != -1) tie(fup, gup) = merge(f0, g0, fup, gup);
    dfs2(g, fup, gup, v, u);
  }
}

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &H[i]);
  }
  Graph g(N, 2*(N-1));
  for (int i = 0; i < N-1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g.addEdge(u, v);
    g.addEdge(v, u);
  }
  dfs1(g, 0, -1);
  dfs2(g, 0, 1, 0, -1);
  for (int i = 0; i < N; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
