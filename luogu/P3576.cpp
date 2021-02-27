// https://www.luogu.com.cn/problem/P3576
// [POI2014]MRO-Ant colony

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
const int64_t INF = 1e9 + 1;
int N, G, K;
int M[MAXN];
int A, B;
int D[MAXN];
int mul(int64_t x, int d) {
  if (x >= INF) return INF;
  return min(INF, x * d);
}

int mul2(int64_t x, int d) {
  if (x >= INF) return INF;
  return min(INF, (x+1) * d - 1);
}

struct Range {
  int64_t l, r;
  Range calc(int d) const {
    Range ret;
    ret.l = mul(l, d);
    ret.r = mul2(r, d);
    return ret;
  }
} R[MAXN];

void dfs(const Graph& g, int u, int fa, const Range& r) {
  R[u] = r;
  if (D[u] == 1) return;
  Range r2 = r.calc(D[u]-1);
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v != fa) {
      dfs(g, v, u, r2);
    }
  }
}

int main() {
  scanf("%d%d%d", &N, &G, &K);
  for (int i = 0; i < G; i++) {
    scanf("%d", &M[i]);
  }
  Graph g(N, 2*(N-1));
  for (int i = 0; i < N-1; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    if (i == 0) {
      A = a;
      B = b;
    }
    g.addEdge(a, b);
    g.addEdge(b, a);
    D[a]++;
    D[b]++;
  }

  dfs(g, A, B, Range{K, K});
  dfs(g, B, A, Range{K, K});

  sort(M, M+G);
  int64_t ans = 0;
  for (int i = 0; i < N; i++) {
    if (D[i] == 1) {
      int m = upper_bound(M, M+G, R[i].r) - lower_bound(M, M+G, R[i].l);
      ans += m;
    }
  }
  ans *= K;
  printf("%ld\n", ans);
  return 0;
}
