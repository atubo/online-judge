// https://www.luogu.com.cn/problem/P3357
// 最长k可重线段集问题

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
  Edge **V;
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

const int MAXN = 510;

struct Segment {
  int64_t x0, x1, l;
} S[MAXN];

int64_t length(int64_t x0, int64_t y0, int64_t x1, int64_t y1) {
  return sqrt(double(x1-x0)*double(x1-x0) + double(y1-y0)*double(y1-y0));
}

int findIdx(const vector<int64_t>& sorted, int64_t x) {
  return lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin() + 1;
}

int N, K;
int M;

int main() {
  scanf("%d%d", &N, &K);
  vector<int64_t> sorted;
  for (int i = 0; i < N; i++) {
    int64_t x0, y0, x1, y1;
    scanf("%ld%ld%ld%ld", &x0, &y0, &x1, &y1);
    if (x0 > x1) {
      swap(x0, x1);
      swap(y0, y1);
    }
    int64_t l = length(x0, y0, x1, y1);
    S[i] = {x0, x1, l};
    sorted.push_back(x0);
    sorted.push_back(x1);
  }
  sort(sorted.begin(), sorted.end());
  sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
  M = sorted.size();

  for (int i = 0; i < N; i++) {
    if (S[i].x0 == S[i].x1) {
      S[i].x0 = 2*findIdx(sorted, S[i].x0) - 1;
      S[i].x1 = 2*findIdx(sorted, S[i].x1);
    } else {
      S[i].x0 = 2*findIdx(sorted, S[i].x0);
      S[i].x1 = 2*findIdx(sorted, S[i].x1) - 1;
    }
  }

  MincostMaxflow flow(2*M+2, 2*M+1+N);
  flow.addEdge(0, 1, 0, K);
  for (int i = 1; i < 2*M; i++) {
    flow.addEdge(i, i+1, 0, MincostMaxflow::INF);
  }
  flow.addEdge(2*M, 2*M+1, 0, K);
  for (int i = 0; i < N; i++) {
    flow.addEdge(S[i].x0, S[i].x1, -S[i].l, 1);
  }

  auto ans = flow.mincostFlow(0, 2*M+1);
  printf("%ld\n", -ans.second);

  return 0;
}
