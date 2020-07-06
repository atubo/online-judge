// https://www.luogu.com.cn/problem/P4249
// [WC2007]剪刀石头布

#include <bits/stdc++.h>
using namespace std;


class MincostMaxflow {
  // NOTE
  // 1. nodes are 0-indexed
  // 2. call init() before you use it again
 public:
  const static int64_t INF = 1e13;

  MincostMaxflow(int N_, int M):N(N_), Q(N_) {
    V = new Edge*[N]{};
    ES = new Edge[2*M]{};
    sp = new int64_t[N]{};
    prev = new int[N]{};
    path = new Edge*[N]{};
    init();
  }

  ~MincostMaxflow() {
    delete[] V;
    delete[] ES;
    delete[] sp;
    delete[] prev;
    delete[] path;
  }

  void addEdge(int a, int b, int64_t cost, int64_t capacity) {
    Edge e1 = {V[a], 0, b, capacity, cost}, e2 = {V[b], 0, a, 0, -cost};
    ES[++EC] = e1; V[a] = &ES[EC];
    ES[++EC] = e2; V[b] = &ES[EC];
    V[a]->op = V[b]; V[b]->op = V[a];
  }

  struct FlowCost {
    int64_t flow, cost;
    FlowCost& operator += (const FlowCost &other) {
      flow += other.flow;
      cost += other.cost;
      return *this;
    }
  };

  // returns maxflow, mincost
  pair<int64_t, int64_t> mincostFlow(int s, int t) {
    FlowCost fc{};
    while (SPFA(s, t)) {
      fc += augment(t);
    }
    return make_pair(fc.flow, fc.cost);
  }

 private:
  int N;
  struct Edge {
    Edge *next, *op;
    int t;
    int64_t c, v;    // node, residual, cost
  };

  Edge *ES;
 public:
  Edge **V;
 private:
  int EC = -1;

  void init() {
    EC = -1;
    memset(V, 0, N * sizeof(Edge*));
  }

  struct Queue {
    Queue(int N_): N(N_) {
      Q = new int[N]{};
      inq = new bool[N]{};
    }

    ~Queue() {
      delete[] Q;
      delete[] inq;
    }

    int N;
    int *Q;
    int QH, QL, Size;
    bool *inq;

    void ins(int v) {
      if (++QL >= N) QL = 0;
      Q[QL] = v;
      inq[v] = true;
      Size++;
    }

    int pop() {
      int r = Q[QH];
      inq[r] = false;
      Size--;
      if (++QH >= N) QH = 0;
      return r;
    }

    void reset() {
      memset(Q, 0, N* sizeof(int));
      QH = Size = 0;
      QL = -1;
    }
  };
  Queue Q;

  int64_t *sp;
  int *prev;
  Edge **path;

  bool SPFA(int s, int t) {
    int u, v;
    for (u = 0; u < N; u++) sp[u] = INF;
    Q.reset();
    Q.ins(s);
    sp[s] = 0; prev[s] = -1;
    while (Q.Size) {
      u = Q.pop();
      for (Edge *k = V[u]; k; k = k->next) {
        v = k->t;
        if (k->c > 0 && sp[u] + k->v < sp[v]) {
          sp[v] = sp[u] + k->v;
          prev[v] = u;
          path[v] = k;
          if (!Q.inq[v]) Q.ins(v);
        }
      }
    }
    return sp[t] != INF;
  }

  FlowCost augment(int t) {
    int i;
    int64_t low = INF, cost = 0;
    Edge *e;
    for (i = t; prev[i] != -1; i = prev[i]) {
      e = path[i];
      if (e->c < low) low = e->c;
    }
    for (i = t; prev[i] != -1; i = prev[i]) {
      e = path[i];
      e->c -= low; e->op->c += low;
      cost += e->v * low;
    }
    return FlowCost{low, cost};
  }
};

const int MAXN = 105;
int N;
int D[MAXN][MAXN];
int W[MAXN], L[MAXN];

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &D[i][j]);
    }
  }
  vector<pair<int, int>> tbd;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      if (D[i][j] == 1) {
        W[i]++;
        L[j]++;
      } else if (D[i][j] == 0) {
        W[j]++;
        L[i]++;
      } else {
        tbd.push_back(make_pair(i, j));
      }
    }
  }
  const int nd = tbd.size();
  MincostMaxflow netflow(2+nd+N, 2*nd+3*N*(N-1)/2);
  for (int i = 0; i < nd; i++) {
    netflow.addEdge(0, i+1, 0, 1);
    netflow.addEdge(i+1, nd+1+tbd[i].first, 0, 1);
    netflow.addEdge(i+1, nd+1+tbd[i].second, 0, 1);
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (D[i][j] == 1) {
        netflow.addEdge(0, nd+1+i, 0, 1);
      }
    }
    for (int j = 0; j < N-1-L[i]; j++) {
      netflow.addEdge(nd+1+i, nd+1+N, j, 1);
    }
  }
  auto ret = netflow.mincostFlow(0, nd+1+N);
  printf("%ld\n", N*(N-1)*(N-2)/6 - ret.second);

  for (int i = 0; i < nd; i++) {
    int y = -1;
    for (const auto* e = netflow.V[i+1]; e; e = e->next) {
      if (e->c == 0) {
        y = e->t - nd - 1;
        break;
      }
    }
    int x = tbd[i].second == y ? tbd[i].first : tbd[i].second;
    D[x][y] = 0;
    D[y][x] = 1;
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%d ", D[i][j]);
    }
    printf("\n");
  }
  return 0;
}
