// https://www.luogu.com.cn/problem/P4654
// [CEOI2017]Mousetrap

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
int FA[MAXN], DEG[MAXN], F[MAXN];
int st[MAXN], sm[MAXN];
int top;

void dfs(const Graph& g, int u, int fa) {
  FA[u] = fa;
  int h1 = 0, h2 = 0;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v != fa) {
      dfs(g, v, u);
      if (F[v] >= h1) {
        h2 = h1;
        h1 = F[v];
      } else if (F[v] > h2) {
        h2 = F[v];
      }
    }
  }
  F[u] = h2 + DEG[u] - 1;
}

bool check(const Graph& g, int x) {
  int re = 0;
  for (int h = 1; h < top; h++) {
    int c = 0;
    int u = st[h];
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      if (v != st[h+1] && v != st[h-1] &&
          sm[h] + F[v] + 1 - (h != 1) > x - re) {
        c++;
      }
    }
    re += c;
    if (re > x || re > h) return 0;
  }
  return 1;
}

int main() {
  int n, t, m;
  scanf("%d%d%d", &n, &t, &m);
  Graph g(n+1, 2*(n-1));
  for (int i = 0; i < n-1; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    DEG[x]++;
    DEG[y]++;
    g.addEdge(x, y);
    g.addEdge(y, x);
  }
  dfs(g, t, 0);
  for (int u = m; u != t; u = FA[u]) {
    st[++top] = u;
  }
  st[++top] = t;
  for (int i = top-1; i > 0; i--) {
    sm[i] = sm[i+1] + DEG[st[i]] - 2;
  }
  int lo = -1, hi = n;
  while (lo < hi-1) {
    int mid = (lo + hi) / 2;
    if (check(g, mid)) hi = mid;
    else lo = mid;
  }
  printf("%d\n", hi);
  return 0;
}
