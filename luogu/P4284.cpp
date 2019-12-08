// https://www.luogu.com.cn/problem/P4284
// [SHOI2014]概率充电器

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

const int MAXN = 500010;
const double EPS = 1e-7;
double P[MAXN];
double Q[MAXN], R[MAXN];

void dfs1(const Graph& g, int u, int f) {
  Q[u] = 1 - P[u];
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v == f) continue;
    dfs1(g, v, u);
    double w = 1.0 * g.E[eidx].wt / 100;
    Q[u] *= 1 - w * Q[v];
  }
  Q[u] = 1 - Q[u];
}

void dfs2(const Graph& g, int u, int f, double w) {
  if (f >= 0 && 1-Q[u] > EPS) {
    R[u] = 1 - (1-Q[u])*(1-w*(1-(1-R[f])/(1-w*Q[u])));
  } else {
    R[u] = Q[u];
  }
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v == f) continue;
    dfs2(g, v, u, 1.0*g.E[eidx].wt/100);
  }
}

int N;

int main() {
  scanf("%d", &N);
  Graph g(N, 2*(N-1));
  for (int i = 0; i < N-1; i++) {
    int a, b, p;
    scanf("%d%d%d", &a, &b, &p);
    a--; b--;
    g.addEdge(a, b, p);
    g.addEdge(b, a, p);
  }

  for (int i = 0; i < N; i++) {
    int q;
    scanf("%d", &q);
    P[i] = 1.0*q/100;
  }

  dfs1(g, 0, -1);
  dfs2(g, 0, -1, 0.0);

  double ans = 0;
  for (int i = 0; i < N; i++) {
    ans += R[i];
  }
  printf("%.6f", ans);

  return 0;
}
