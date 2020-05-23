// https://www.luogu.com.cn/problem/P4323
// [JSOI2016]独特的树叶

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

const uint64_t W = 1e9+7;

void dfs1(const Graph& g, int u, int fa, uint64_t* f, int* sz) {
  uint64_t ret = 0;
  sz[u] = 1;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v != fa) {
      dfs1(g, v, u, f, sz);
      ret = ret ^ (f[v] * W + sz[v]);
      sz[u] += sz[v];
    }
  }
  f[u] = ret;
}

void
dfs2(const Graph& g, int u, int fa, uint64_t* f, uint64_t* h, int* sz, int n) {
  if (fa == -1) {
    h[u] = f[u];
  } else {
    h[u] = f[u] ^ ((h[fa] ^ (f[u] * W + sz[u])) * W + (n - sz[u]));
  }
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v != fa) {
      dfs2(g, v, u, f, h, sz, n);
    }
  }
}

const int MAXN = 500010;
int N;
uint64_t FA[MAXN], FB[MAXN], HA[MAXN], HB[MAXN];
int SA[MAXN], SB[MAXN];

int main() {
  scanf("%d", &N);
  Graph g1(N, 2*(N-1)), g2(N+1, 2*N);
  for (int i = 0; i < N-1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    g1.addEdge(u, v);
    g1.addEdge(v, u);
  }
  for (int i = 0; i < N; i ++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    g2.addEdge(u, v);
    g2.addEdge(v, u);
  }
  dfs1(g1, 0, -1, FA, SA);
  dfs1(g2, 0, -1, FB, SB);
  dfs2(g1, 0, -1, FA, HA, SA, N);
  dfs2(g2, 0, -1, FB, HB, SB, N+1);

  map<uint64_t, int> hashToId;
  for (int i = N; i >= 0; i--) {
    hashToId[HB[i]] = i;
  }

  int ans = INT_MAX;
  for (int i = 0; i < N; i++) {
    uint64_t h = HA[i]*W + N;
    auto it = hashToId.find(h);
    if (it != hashToId.end() && it->second < ans) {
      ans = it->second;
    }
  }
  printf("%d\n", ans + 1);
  return 0;
}
