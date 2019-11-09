// https://www.luogu.org/problem/P4408
// [NOI2003]逃学的小孩

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

// T[u]: result of merge at u
// D[u]: depth of u itself
// D1[u]: largest depth for u and its subtree

const int MAXN = 200010;
int N, M;
int64_t D[MAXN], D1[MAXN], T[MAXN];

void dfs1(const Graph& g, int u, int f, int64_t d) {
  D1[u] = D[u] = d;
  vector<int64_t> tmp;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    int w = g.E[eidx].wt;
    if (v == f) continue;
    dfs1(g, v, u, d+w);
    D1[u] = max(D1[u], D1[v]);
  }
}

int64_t calc(const vector<pair<int64_t, int>>& d) {
  int64_t t[3] = {0, 0, 0};
  for (int i = 0; i < min((int)d.size(), 3); i++) {
    t[i] = d[i].first;
  }
  return t[0] + 2LL*t[1] + t[2];
}

void dfs2(const Graph& g, int u, int f, int64_t d) {
  vector<pair<int64_t, int>> tmp;
  tmp.push_back(make_pair(d, f));

  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v == f) continue;
    tmp.push_back(make_pair(D1[v]-D[u], v));
  }
  sort(tmp.begin(), tmp.end(), greater<pair<int64_t, int>>());
  T[u] = calc(tmp);

  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    int w = g.E[eidx].wt;
    if (v == f) continue;
    if (v == tmp[0].second) {
      dfs2(g, v, u, tmp[1].first+w);
    } else {
      dfs2(g, v, u, tmp[0].first+w);
    }
  }
}

int main() {
  scanf("%d%d", &N, &M);
  Graph g(N, 2*M);
  for (int i = 0; i < M; i++) {
    int u, v, t;
    scanf("%d%d%d", &u, &v, &t);
    u--; v--;
    g.addEdge(u, v, t);
    g.addEdge(v, u, t);
  }
  dfs1(g, 0, -1, 0);
  dfs2(g, 0, -1, 0);

  int64_t ans = 0;
  for (int i = 0; i < N; i++) {
    ans = max(ans, T[i]);
  }
  printf("%ld\n", ans);
  return 0;
}
