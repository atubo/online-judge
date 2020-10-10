// https://www.luogu.com.cn/problem/P3573
// [POI2014]RAJ-Rally

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

// Note: be sure it's DAG
class TopologicalSort {
public:
    vector<int> topo;  // topologically sorted result

private:
    void topologicalSortUtil(const Graph &g, int v, bool visited[],
                             stack<int> &order) {
        visited[v] = true;

        for (int i = g.head[v]; i != -1; i = g.E[i].next) {
            int m = g.E[i].to;
            if (!visited[m]) {
                topologicalSortUtil(g, m, visited, order);
            }
        }

        order.push(v);
    }

public:
    TopologicalSort() {}

    void sort(const Graph &g) {
        const int N = g.N;
        topo.resize(N);

        stack<int> order;
        bool visited[N];
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                topologicalSortUtil(g, i, visited, order);
            }
        }

        int i = 0;
        while (!order.empty()) {
            topo[i++] = order.top();
            order.pop();
        }
    }
};

const int MAXN = 500010;
int N, M;
int L[MAXN], R[MAXN], X[MAXN], A[MAXN];
int ML[MAXN], MR[MAXN];

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    L[i] = R[i] = 1;
  }
  Graph g(N, M), gr(N, M);
  for (int i = 0; i < M; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    g.addEdge(a, b);
    gr.addEdge(b, a);
  }
  TopologicalSort topo;
  topo.sort(g);
  for (int i = 0; i < N; i++) {
    X[topo.topo[i]] = i;
  }
  for (int i = 0; i < N; i++) {
    int u = topo.topo[i];
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      int j = X[v];
      L[j] = max(L[j], L[i]+1);
    }
  }
  for (int i = N-1; i >= 0; i--) {
    int u = topo.topo[i];
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      int j = X[v];
      R[i] = max(R[i], R[j]+1);
    }
  }

  ML[0] = L[0];
  for (int i = 1; i < N; i++) {
    ML[i] = max(ML[i-1], L[i]);
  }
  MR[N-1] = R[N-1];
  for (int i = N-2; i >= 0; i--) {
    MR[i] = max(MR[i+1], R[i]);
  }

  multiset<int> s;
  A[0] = MR[1];
  for (int u = topo.topo[0], eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {

    int v = g.E[eidx].to;
    int j = X[v];
    s.insert(L[0] + R[j]);
  }

  for (int i = 1; i < N; i++) {
    A[i] = ML[i-1];
    if (i < N-1) {
      A[i] = max(A[i], MR[i+1]);
    }
    int u = topo.topo[i];
    for (int eidx = gr.head[u]; ~eidx; eidx = gr.E[eidx].next) {
      int v = gr.E[eidx].to;
      int j = X[v];
      int x = L[j] + R[i];
      const auto it = s.find(x);
      assert(it != s.end());
      s.erase(it);
    }
    if (!s.empty()) {
      A[i] = max(A[i], *s.rbegin());
    }
    for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
      int v = g.E[eidx].to;
      int j = X[v];
      s.insert(L[i] + R[j]);
    }
  }

  int ans = INT_MAX, pos = -1;
  for (int i = 0; i < N; i++) {
    if (A[i] < ans) {
      ans = A[i];
      pos = topo.topo[i];
    }
  }
  printf("%d %d\n", pos+1, ans-1);

  return 0;
}
