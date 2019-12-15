// https://www.luogu.com.cn/problem/P4376
// [USACO18OPEN]Milking Order

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
 public:
  struct Edge {
    int next, to, id;
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
  void addEdge(int u, int v, int idx) {
    E[eidx].to = v;
    E[eidx].next = head[u];
    E[eidx].id = idx;
    head[u] = eidx++;
  }
};

const int MAXN = 100010;
const int MAXM = 200010;
int N, M;
bool vis[MAXN], ins[MAXN];
int deg[MAXN];

bool dfs1(const Graph& g, int u, int x) {
  vis[u] = true;
  ins[u] = true;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    int id = g.E[eidx].id;
    if (id > x) continue;
    if (ins[v]) return false;
    if (!vis[v]) {
      bool ok = dfs1(g, v, x);
      if (!ok) return false;
    }
  }
  ins[u] = false;
  return true;
}

bool feasible(int x, const Graph& g) {
  memset(vis, 0, N*sizeof(bool));
  memset(ins, 0, N*sizeof(bool));
  for (int i = 0; i < N; i++) {
    if (!vis[i]) {
      bool ok = dfs1(g, i, x);
      if (!ok) return false;
    }
  }
  return true;
}

void dfs2(const Graph& g, int u, int x, vector<int>& topo) {
  vis[u] = true;
  vector<int> succ;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    int id = g.E[eidx].id;
    if (id > x) continue;
    if (!vis[v]) succ.push_back(v);
  }
  sort(succ.begin(), succ.end(), greater<int>());
  for (int v : succ) {
    if (!vis[v]) dfs2(g, v, x, topo);
  }
  topo.push_back(u);
}

void solve(const Graph& g, int x) {
  for (int i = 0; i < N; i++) {
    for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      int id = g.E[eidx].id;
      if (id > x) continue;
      deg[v]++;
    }
  }

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < N; i++) {
    if (deg[i] == 0) pq.push(i);
  }

  while (!pq.empty()) {
    int u = pq.top();
    pq.pop();
    printf("%d ", u+1);
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      int id = g.E[eidx].id;
      if (id > x) continue;
      if (--deg[v] == 0) pq.push(v);
    }
  }
  printf("\n");
}

int main() {
  scanf("%d%d", &N, &M);
  Graph g(N, MAXM);
  for (int i = 0; i < M; i++) {
    int m;
    scanf("%d", &m);
    int last = -1;
    for (int j = 0; j < m; j++) {
      int u;
      scanf("%d", &u);
      u--;
      if (last >= 0) {
        g.addEdge(last, u, i);
      }
      last = u;
    }
  }

  int lo = -1, hi = M;
  while (lo < hi-1) {
    int mid = (lo + hi) / 2;
    if (feasible(mid, g)) lo = mid;
    else hi = mid;
  }
  solve(g, lo);

  return 0;
}
