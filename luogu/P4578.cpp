// https://www.luogu.com.cn/problem/P4578
// [FJOI2018]所罗门王的宝藏

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

const int MAXN = 1010;
int N, M, K;
bool vis[2*MAXN];
int A[2*MAXN];

bool dfs(const Graph& g, int u) {
  vis[u] = true;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    int w = g.E[eidx].wt;
    if (vis[v]) {
      if (A[v] + A[u] != w) return false;
    } else {
      A[v] = w - A[u];
      bool ok = dfs(g, v);
      if (!ok) return false;
    }
  }
  return true;
}

void solve() {
  scanf("%d%d%d", &N, &M, &K);
  Graph g(N+M, 2*K);
  for (int i = 0; i < K; i++) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    x--; y--;
    g.addEdge(x, N+y, c);
    g.addEdge(N+y, x, c);
  }
  memset(vis, 0, (N+M)*sizeof(bool));
  memset(A, 0, (N+M)*sizeof(int));
  for (int i = 0; i < N; i++) {
    if (!vis[i]) {
      bool ok = dfs(g, i);
      if (!ok) {
        printf("No\n");
        return;
      }
    }
  }
  printf("Yes\n");
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}
