// https://www.luogu.com.cn/problem/P4581
// [BJOI2014]想法

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

const int MAXN = 1000010;
const int K = 100;
int ans[MAXN];
int C[MAXN][2];
int N, M;
int in[MAXN];
vector<vector<int>> firstK(MAXN);
bool vis[MAXN];

vector<int> merge(const vector<int>& a, const vector<int>& b) {
  vector<int> ret;
  int i = 0, j = 0;
  while (ret.size() < K && i < (int)a.size() && j < (int)b.size()) {
    if (a[i] < b[j]) {
      ret.push_back(a[i++]);
    } else if (a[i] > b[j]) {
      ret.push_back(b[j++]);
    } else {
      ret.push_back(a[i++]);
      j++;
    }
  }
  if (ret.size() < K) {
    if (i < (int)a.size()) {
      int k = min((int)a.size()-i, K-(int)ret.size());
      for (int l = 0; l < k; l++) {
        ret.push_back(a[i+l]);
      }
    } else {
      int k = min((int)b.size()-j, K-(int)ret.size());
      for (int l = 0; l < k; l++) {
        ret.push_back(b[j+l]);
      }
    }
  }
  return ret;
}

void dfs(int u) {
  if (vis[u]) return;
  vis[u] = true;
  if (u < M) {
    firstK[u].push_back(rand()%RAND_MAX+1);
    return;
  }
  int l = C[u][0], r = C[u][1];
  dfs(l);
  dfs(r);
  firstK[u] = merge(firstK[l], firstK[r]);
  if (firstK[u].size() < K) {
    ans[u] = firstK[u].size();
  } else {
    ans[u] = 1LL * K * RAND_MAX / firstK[u][K-1];
  }
}

int main() {
  scanf("%d%d", &N, &M);
  srand(19271115);
  for (int i = M; i < N; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    C[i][0] = x;
    C[i][1] = y;
    in[x]++;
    in[y]++;
  }
  for (int i = M; i < N; i++) {
    if (in[i] == 0) dfs(i);
  }
  for (int i = M; i < N; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
