// https://www.luogu.com.cn/problem/P4643
// [国家集训队]阿狸和桃子的游戏

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

const int MAXN = 10010;
int W[MAXN], W2[MAXN];

int N, M;

int main() {
  scanf("%d%d", &N, &M);
  Graph g(N, 2*M);
  for (int i = 0; i < N; i++) {
    scanf("%d", &W[i]);
  }
  for (int i = 0; i < M; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    a--; b--;
    g.addEdge(a, b, c);
    g.addEdge(b, a, c);
  }
  for (int i = 0; i < N; i++) {
    W2[i] = 2 * W[i];
    for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
      W2[i] += g.E[eidx].wt;
    }
  }
  sort(W2, W2+N, greater<int>());
  int a[2] = {0, 0};
  for (int i = 0; i < N; i++) {
    a[i&1] += W2[i];
  }
  printf("%d\n", (a[0]-a[1])/2);

  return 0;
}
