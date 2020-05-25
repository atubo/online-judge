// https://www.luogu.com.cn/problem/P4962
// 朋也与光玉

#include <bits/stdc++.h>
using namespace std;

// Note graph node is 0-indexed
class Graph {
 public:
  struct Edge {
    int next, to, wt;
  };

  //vector<int> head;
  int * head;
  int eidx;
  int N, M;

  Edge *E;

  Graph(int N_, int M_):N(N_), M(M_) {
    //head.resize(N);
    head = new int[N]{};
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
  void addEdge(int u, int v, int w) {
    E[eidx].to = v;
    E[eidx].wt = w;
    E[eidx].next = head[u];
    head[u] = eidx++;
  }
};

struct Key {
  int u, s, d;
};

const int INF = 0x3F3F3F3F;
const int MAXN = 105;
int N, M, K;
int A[MAXN];
int dp[MAXN][1<<13];
int F[MAXN][1<<13], B[MAXN][1<<13];
Key Q[MAXN*4000];

void spfa(const Graph& g, int dmax) {
  memset(dp, 0x3F, sizeof(dp));
  int front = 0, back = 0;
  for (int u = 0; u < N; u++) {
    dp[u][1<<A[u]] = 0;
    Q[back++] = {u, 1<<A[u], 1};
  }
  while (front != back) {
    Key key = Q[front++];
    int u = key.u, s = key.s, d = key.d;
    if (d == dmax) continue;
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      int w = g.E[eidx].wt;
      int a = A[v];
      if ((s >> a) & 1) continue;
      int sv = s | (1 << a);
      if (dp[v][sv] == INF) {
        dp[v][sv] = dp[u][s] + w;
        Q[back++] = {v, sv, d+1};
      } else {
        dp[v][sv] = (dp[v][sv] < dp[u][s] + w ? dp[v][sv] : dp[u][s] + w);
      }
    }
  }
}

int main() {
  scanf("%d%d%d", &N, &M, &K);
  for (int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }
  Graph g(N, M), gr(N, M);
  for (int i = 0; i < M; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--; v--;
    g.addEdge(u, v, w);
    gr.addEdge(v, u, w);
  }
  memset(F, 0x3F, sizeof(F));
  memset(B, 0x3F, sizeof(B));
  const int nb = (K + 1) / 2;
  const int nf = (K + 2) / 2;
  vector<int> sb, sf;
  for (int s = 0; s < (1 << K); s++) {
    if (__builtin_popcount(s) == nb) {
      sb.push_back(s);
    }
    if (__builtin_popcount(s) == nf) {
      sf.push_back(s);
    }
  }
  spfa(g, nf);
  for (int u = 0; u < N; u++) {
    for (int s : sf) {
      F[u][s] = (F[u][s] < dp[u][s] ? F[u][s] : dp[u][s]);
    }
  }
  spfa(gr, nb);
  for (int u = 0; u < N; u++) {
    for (int s : sb) {
      B[u][s] = (B[u][s] < dp[u][s] ? B[u][s] : dp[u][s]);
    }
  }

  const int ALL = (1 << K) - 1;
  int ans = INF;
  for (int u = 0; u < N; u++) {
    for (int s1 : sf) {
      int s2 = (ALL ^ s1) | (1 << A[u]);
      if (F[u][s1] < INF && B[u][s2] < INF) {
        ans = min(ans, F[u][s1] + B[u][s2]);
      }
    }
  }

  if (ans == INF) printf("Ushio!\n");
  else printf("%d\n", ans);

  return 0;
}
