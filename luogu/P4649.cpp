// https://www.luogu.com.cn/problem/P4649
// [IOI2007] training 训练路径

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
  struct Edge {
    int next, to;
  };

 public:
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

const int MAXM = 5010;
const int MAXN = 1010;
int N, M;
int D[MAXN];
int P[MAXN][12];

struct Edge {
  int u, v, w;
} H[MAXM];

void dfs(const Graph& g, int u, int f, int d) {
  D[u] = d;
  P[u][0] = f;
  for (int i = 1; i < 12; i++) {
    P[u][i] = P[P[u][i-1]][i-1];
  }
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v != f) dfs(g, v, u, d+1);
  }
}

int lca(int u, int v) {
  if (D[u] < D[v]) swap(u, v);
  int d = D[u] - D[v];
  for (int i = 11; i >= 0; i--) {
    if ((d >> i)& 1) {
      u = P[u][i];
    }
  }

  if (u == v) return u;
  for (int i = 11; i >= 0; i--) {
    if (P[u][i] != P[v][i]) {
      u = P[u][i];
      v = P[v][i];
    }
  }
  return P[u][0];
}

int f[MAXN][1024];
int rid[MAXN];
vector<int> B[MAXN];

void solve(const Graph& g, int u) {
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v == P[u][0]) continue;
    solve(g, v);
  }

  int nc = 0;
  int id[10] = {0};
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v == P[u][0]) continue;
    id[nc] = v;
    rid[v] = (1 << nc);
    nc++;
  }

  for (int s = 0; s < (1<<nc); s++) {
    int t = 0;
    for (int i = 0; i < nc; i++) {
      if (((s>>i) & 1) == 0) {
        t += f[id[i]][0];
      }
    }
    f[u][s] = t;
  }
  for (int k = 0; k < (int)B[u].size(); k++) {
    Edge e = H[B[u][k]];
    int t = e.w;
    int from = e.u, to = e.v;
    if (from != u) t += f[from][0];
    if (to != u) t += f[to][0];
    int a = 0, b = 0;
    if (from != u) {
      for (a = from; P[a][0] != u; a = P[a][0]) {
        t += f[P[a][0]][rid[a]];
      }
    }
    if (to != u) {
      for (b = to; P[b][0] != u; b = P[b][0]) {
        t += f[P[b][0]][rid[b]];
      }
    }
    for (int s = 0; s < (1<<nc); s++) {
      if ((s & rid[a]) == 0 && (s & rid[b]) == 0) {
        f[u][s] = max(f[u][s], f[u][s|rid[a]|rid[b]] + t);
      }
    }
  }
}

int main() {
  scanf("%d%d", &N, &M);
  Graph g(N+1, 2*N);
  int tot = 0;
  int ne = 0;
  for (int i = 0; i < M; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if (c == 0) {
      g.addEdge(a, b);
      g.addEdge(b, a);
    } else {
      H[ne++] = Edge{a, b, c};
      tot += c;
    }
  }

  dfs(g, 1, 0, 0);

  for (int i = 0; i < ne; i++) {
    Edge e = H[i];
    if ((abs(D[e.u] - D[e.v]) & 1) == 0) {
      int p = lca(e.u, e.v);
      B[p].push_back(i);
    }
  }
  solve(g, 1);

  printf("%d\n", tot - f[1][0]);

  return 0;
}
