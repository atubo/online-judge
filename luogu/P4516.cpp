// https://www.luogu.com.cn/problem/P4516
// [JSOI2018]潜入行动

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

const int MOD = 1000000007;

int dp[100010][2][2][102];
int64_t tmp[2][2][102];

int N, K;

int dfs(const Graph& g, int u, int fa) {
  int sz = 1;
  dp[u][0][0][0] = dp[u][1][0][1] = 1;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v != fa) {
      int szv = dfs(g, v, u);
      memset(tmp, 0, sizeof(tmp));
      for (int j = 0; j <= min(K, sz); j++) {
        for (int l = 0; l <= min(K-j, szv); l++) {
          tmp[0][0][j+l] += 1LL * dp[u][0][0][j] * dp[v][0][1][l];
          tmp[0][0][j+l] %= MOD;
          tmp[0][1][j+l] +=
              1LL * dp[u][0][0][j] * dp[v][1][1][l] +
              1LL * dp[u][0][1][j] * dp[v][0][1][l] +
              1LL * dp[u][0][1][j] * dp[v][1][1][l];
          tmp[0][1][j+l] %= MOD;
          tmp[1][0][j+l] +=
              1LL * dp[u][1][0][j] * dp[v][0][1][l] +
              1LL * dp[u][1][0][j] * dp[v][0][0][l];
          tmp[1][0][j+l] %= MOD;
          tmp[1][1][j+l] +=
              1LL * dp[u][1][1][j] * dp[v][0][0][l] +
              1LL * dp[u][1][1][j] * dp[v][0][1][l] +
              1LL * dp[u][1][1][j] * dp[v][1][0][l] +
              1LL * dp[u][1][1][j] * dp[v][1][1][l] +
              1LL * dp[u][1][0][j] * dp[v][1][0][l] +
              1LL * dp[u][1][0][j] * dp[v][1][1][l];
          tmp[1][1][j+l] %= MOD;
        }
      }
      sz += szv;
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          for (int k = 0; k <= K; k++) {
            dp[u][i][j][k] = tmp[i][j][k];
          }
        }
      }
    }
  }
  return sz;
}

int main() {
  scanf("%d%d", &N, &K);
  Graph g(N, 2*(N-1));
  for (int i = 0; i < N-1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    g.addEdge(u, v);
    g.addEdge(v, u);
  }
  dfs(g, 0, -1);
  printf("%d\n", (dp[0][0][1][K] + dp[0][1][1][K]) % MOD);
  return 0;
}
