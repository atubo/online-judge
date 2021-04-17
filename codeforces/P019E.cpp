// https://codeforces.com/problemset/problem/19/E
// E. Fairy

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

const int MAXN = 10010;
int depth[MAXN];
bool vis[MAXN];
int Co, Ce;
int So[MAXN], Se[MAXN];

void dfs(const Graph& g, int u, int fa, int d) {
  vis[u] = true;
  depth[u] = d;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v == fa) continue;
    if (!vis[v]) {
      dfs(g, v, u, d+1);
    } else if (depth[u] > depth[v]) {
      int len = depth[u] - depth[v] + 1;
      if (len & 1) {
        Co++;
        So[u]++;
        So[v]--;
      } else {
        Ce++;
        Se[u]++;
        Se[v]--;
      }
    }
  }
}

void dfs2(const Graph& g, int u) {
  vis[u] = true;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (!vis[v]) {
      dfs2(g, v);
      So[u] += So[v];
      Se[u] += Se[v];
    }
  }
}
    
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  Graph g(n, 2*m);
  vector<pair<int, int>> edges;
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    g.addEdge(u, v);
    g.addEdge(v, u);
    edges.push_back(make_pair(u, v));
  }

  for (int i = 0; i < n; i++) {
    if (!vis[i]) dfs(g, i, -1, 0);
  }

  memset(vis, 0, n*sizeof(bool));

  for (int i = 0; i < n; i++) {
    if (!vis[i]) dfs2(g, i);
  }

  vector<int> ret;
  for (int i = 0; i < m; i++) {
    int u, v;
    tie(u, v) = edges[i];
    if (depth[u] < depth[v]) swap(u, v);
    bool oc = ((depth[u] - depth[v] + 1) & 1);
    bool ot = (depth[u] == depth[v] + 1);
    if (Co == 0 || (Co == 1 && oc) || (ot && So[u] == Co && Se[u] == 0)) {
      ret.push_back(i);
    }
  }
  printf("%d\n", (int)ret.size());
  for (int i = 0; i < (int)ret.size(); i++) {
    printf("%d%c", ret[i] + 1, i == (int)ret.size()-1 ? '\n' : ' ');
  }

  return 0;
}
