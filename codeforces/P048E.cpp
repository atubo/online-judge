// https://codeforces.com/problemset/problem/48/E
// Ivan the Fool VS Gorynych the Dragon

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

int encode(int h, int t) {
  return (h << 8) | t;
}

struct Edge {
  int u, v;
};

bool vis[1<<16];
int D[1<<16];

int bfs(const Graph& g, int s) {
  memset(D, -1, sizeof(D));
  queue<int> q;
  q.push(s);
  D[s] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (u == 0) return D[u];
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      if (D[v] == -1) {
        D[v] = D[u] + 1;
        q.push(v);
      }
    }
  }
  return D[0];
}

bool dfs(const Graph& g, int u) {
  vis[u] = true;
  D[u] = 1;
  bool ret = false;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (D[v] == 1) return true;
    if (!vis[v]) ret = ret || dfs(g, v);
  }
  D[u] = 0;
  return ret;
}

void dfs2(const Graph& g, int u, stack<int>& st) {
  vis[u] = true;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (!vis[v]) dfs2(g, v, st);
  }
  st.push(u);
}

int solve(const Graph& g, int s) {
  stack<int> st;
  dfs2(g, s, st);
  int ans = 0;
  while (!st.empty()) {
    int u = st.top();
    st.pop();
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      D[v] = max(D[v], D[u] + 1);
      ans = max(ans, D[v]);
    }
  }
  return ans + 1;
}

int main() {
  int h, t, R;
  scanf("%d%d%d", &h, &t, &R);
  int s = encode(h, t);
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> head(n+1);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &head[i].first, &head[i].second);
  }
  int m;
  scanf("%d", &m);
  vector<pair<int, int>> tail(m+1);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &tail[i].first, &tail[i].second);
  }

  vector<Edge> edges;
  for (h = 0; h <= R; h++) {
    for (t = 0; t <= R; t++) {
      if (h + t == 0 || h + t > R) continue;
      int u = encode(h, t);
      for (int c = 1; c <= min(h, n); c++) {
        int h2 = h - c + head[c].first;
        int t2 = t + head[c].second;
        if (h2 + t2 <= R) {
          int v = encode(h2, t2);
          edges.push_back({u, v});
        }
      }
      for (int c = 1; c <= min(t, m); c++) {
        int h2 = h + tail[c].first;
        int t2 = t - c + tail[c].second;
        if (h2 + t2 <= R) {
          int v = encode(h2, t2);
          edges.push_back({u, v});
        }
      }
    }
  }
  Graph g(1<<16, edges.size());
  for (const auto& e : edges) {
    g.addEdge(e.u, e.v);
  }

  int ans = bfs(g, s);
  if (ans >= 0) {
    printf("Ivan\n%d\n", ans);
    return 0;
  }
  memset(D, 0, sizeof(D));
  if (dfs(g, s)) {
    printf("Draw\n");
    return 0;
  }
  memset(vis, 0, sizeof(vis));
  memset(D, 0, sizeof(D));
  printf("Zmey\n%d\n", solve(g, s));
  return 0;
}
