// https://www.luogu.com.cn/problem/P4383
// [八省联考2018]林克卡特树lct

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

const int MAXN = 3e5+10;
struct Data {
  int nchain;
  int64_t profit;
  bool operator < (const Data& other) const {
    return profit == other.profit ?
        nchain > other.nchain : profit < other.profit;
  }

  Data operator + (const Data& other) const {
    return Data{nchain + other.nchain, profit + other.profit};
  }

  Data operator + (int x) const {
    return Data{nchain, profit+x};
  }
} dp[3][MAXN];

Data update(const Data& d, int64_t x) {
  return Data{d.nchain+1, d.profit-x};
}

void dfs(const Graph& g, int u, int f, int64_t x) {
  dp[2][u] = max(dp[2][u], Data{1, -x});
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    int w = g.E[eidx].wt;
    if (v == f) continue;
    dfs(g, v, u, x);
    dp[2][u] = max(dp[2][u]+dp[0][v], update(dp[1][u]+dp[1][v]+w, x));
    dp[1][u] = max(dp[1][u]+dp[0][v], dp[0][u]+dp[1][v]+w);
    dp[0][u] = dp[0][u] + dp[0][v];
  }
  dp[0][u] = max(dp[0][u], max(update(dp[1][u], x), dp[2][u]));
}

int N, K;

int main() {
  scanf("%d%d", &N, &K);
  K++;
  Graph g(N, 2*(N-1));
  int64_t tot = 0;
  for (int i = 0; i < N-1; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--; v--;
    g.addEdge(u, v, w);
    g.addEdge(v, u, w);
    tot += abs(w);
  }
  int64_t lo = -tot-1, hi = tot+1;
  while (lo < hi-1) {
    int64_t mid = (lo + hi) / 2;
    memset(dp, 0, sizeof(dp));
    dfs(g, 0, -1, mid);
    if (dp[0][0].nchain <= K) hi = mid;
    else lo = mid;
  }
  memset(dp, 0, sizeof(dp));
  dfs(g, 0, -1, hi);
  printf("%ld\n", hi*K + dp[0][0].profit);

  return 0;
}
