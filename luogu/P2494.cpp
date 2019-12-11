// https://www.luogu.com.cn/problem/P2494
// [SDOI2011]保密

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
public:
    struct Edge {
        int next, to, t, s;
    };

    //vector<int> head;
    int *head;
    int eidx;
    int N, M;

    Edge *E;

    Graph(int N_, int M_):N(N_), M(M_) {
        //head.resize(N);
        head = new int[N];
        eidx = 0;

        for (int i = 0; i < N; i++) {
            head[i] = -1;
        }

        E = new Edge[M]{};
    }

    ~Graph() {
        delete[] head;
        delete[] E;
    }

    // assume 0-indexed and no duplication
    void addEdge(int u, int v, int t, int s) {
        E[eidx].to = v;
        E[eidx].next = head[u];
        E[eidx].t = t;
        E[eidx].s = s;
        head[u] = eidx++;
    }
};

class Dinic {
public:
    static const int inf = 0x3f3f3f3f;
    struct Edge {
        int to, next, cap;
    };

    const int N, MAXM;
    int *head;
    Edge *E;
    int e;
private:
    int *curr;

public:
    Dinic(int N_, int M_): N(N_), MAXM(2*M_) {
        alloc();
        reset();
    }

    ~Dinic() {
        dealloc();
    }

    void reset() {
        e = 0;
        memset(head, -1, N * sizeof(int));
    }

    void addEdge(int x, int y, int w, int rw = 0) {
        E[e] = {y, head[x], w};
        head[x] = e++;
        E[e] = {x, head[y], rw};
        head[y] = e++;
    }

    int64_t dinic(int s, int t) {
        int64_t ans = 0;
        while (bfs(s, t)) {
            for (int i = 0; i < N; i++) {
                curr[i] = head[i];
            }
            int k = dfs(s, inf, t);
            if (k > 0) ans += k;
        }
        return ans;
    }

private:
    void alloc() {
        head = new int[N]{};
        curr = new int[N]{};
        E    = new Edge[MAXM]{};
        d    = new int[N]{};
        q    = new int[N]{};
    }

    void dealloc() {
        delete[] head;
        delete[] curr;
        delete[] E;
        delete[] d;
        delete[] q;
    }

    int *d;
    int *q;

    bool bfs(int s, int t) {
        memset(d, -1, N * sizeof(int));
        int front = 0, back = 0;
        q[back++] = t;

        d[t] = 0;
        while (front != back) {
            int u = q[front];
            front++;
            for (int i = head[u]; i != -1; i = E[i].next) {
                int v = E[i].to;
                if (d[v] == -1 && E[i^1].cap) {
                    d[v] = d[u] + 1;
                    q[back++] = v;
                    if (v == s) return true;
                }
            }
        }
        return false;
    }

    int dfs(int x, int low, int t) {
        if (x == t || !low) return low;
        int ret = 0;
        for (int &i = curr[x]; i != -1; i = E[i].next) {
            int v = E[i].to;
            if (d[v] == d[x] - 1 && E[i].cap) {
                int k = dfs(v, min(low-ret, E[i].cap), t);
                if (k > 0) {
                    E[i].cap -= k;
                    E[i^1].cap += k;
                    ret += k;
                }
            }
            // without the following line curr[x] might change
            // prematurely, causing runtime increase
            if (low == ret) break;
        }
        return ret;
    }
};

const int MAXN = 705;
const double INF = 1e9;
const double EPS = 1e-4;
const int SCALE = 1000;
int N, M;
double WMAX;
bool vis[MAXN];
int G[MAXN];
double D[MAXN];
int T[MAXN], S[MAXN];
int M1, N1;

void dfs(const Graph& g, int u, vector<int>& topo) {
  vis[u] = true;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (!vis[v]) dfs(g, v, topo);
  }
  topo.push_back(u);
}

double feasible(double x, const Graph& g, const vector<int>& topo, int t) {
  for (int u : topo) {
    D[u] = INF;
    T[u] = S[u] = 0;
  }
  D[N-1] = 0;
  for (int u : topo) {
    if (D[u] == INF) continue;
    if (u == t) break;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      double d = D[u] + g.E[eidx].t - x*g.E[eidx].s;
      if (d < D[v]) {
        D[v] = d;
        T[v] = T[u] + g.E[eidx].t;
        S[v] = S[u] + g.E[eidx].s;
      }
    }
  }
  return 1.0*T[t]/S[t];
}

double solve(const Graph& g, const vector<int>& topo, int u) {
  double x0 = WMAX;
  while (true) {
    double x = feasible(x0, g, topo, u);
    if (x >= x0 || fabs(x-x0) < EPS) break;
    x0 = x;
  }
  return x0;
}

int main() {
  scanf("%d%d", &N, &M);
  Graph g(N, M);
  for (int i = 0; i < M; i++) {
    int a, b, t, s;
    scanf("%d%d%d%d", &a, &b, &t, &s);
    a--; b--;
    g.addEdge(a, b, t, s);
    WMAX = max(1.0*t/s, WMAX);
  }

  vector<int> topo;
  dfs(g, N-1, topo);
  reverse(topo.begin(), topo.end());

  scanf("%d%d", &M1, &N1);

  for (int i = 0; i < N1; i++) {
    if (vis[i]) G[i] = int(solve(g, topo, i)*SCALE+0.5);
    else G[i] = Dinic::inf;
  }

  Dinic dinic(N1+2, N1+M1);
  const int src = 0, dst = N1+1;
  for (int i = 1; i <= N1; i+=2) {
    dinic.addEdge(src, i, G[i-1]);
  }
  for (int i = 2; i <= N1; i+=2) {
    dinic.addEdge(i, dst, G[i-1]);
  }

  for (int i = 0; i < M1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    dinic.addEdge(u, v, Dinic::inf);
  }

  int64_t flow = dinic.dinic(src, dst);
  if (flow >= Dinic::inf) {
    printf("-1\n");
  } else {
    printf("%.1f\n", 1.0*flow/SCALE+0.0001);
  }

  return 0;
}
