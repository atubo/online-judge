// https://www.luogu.com.cn/problem/P5465
// [PKUSC2018]星际穿越

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


const int MAXN = 300010;
int N;
int L[MAXN];
int R[MAXN];
int D[MAXN]; // depth
int64_t W[MAXN];
int X[MAXN][19];

void dfs1(const Graph& g, int u, int f, int d) {
  D[u] = d;
  X[u][0] = f;
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v != f) dfs1(g, v, u, d+1);
  }
}

void dfs2(const Graph& g, int u, int f) {
  W[u] = u;
  if (f != -1) {
    W[u] += W[f] - (f - L[u]);
  }
  for (int eidx = g.head[u]; ~eidx; eidx = g.E[eidx].next) {
    int v = g.E[eidx].to;
    if (v != f) dfs2(g, v, u);
  }
}


void binaryLift(const Graph& g) {
  for (int d = 1; d < 19; d++) {
    for (int u = 0; u < N; u++) {
      if (X[u][d-1] >= 0) {
        X[u][d] = X[X[u][d-1]][d-1];
      }
    }
  }
}

int findLower(int u, int b) {
  // starting from u, find lowest node with l <= b
  if (L[u] <= b) return u;
  for (int d = 18; d >= 0; d--) {
    if (X[u][d] >= 0 && L[X[u][d]] > b) {
      u = X[u][d];
    }
  }
  u = X[u][0];
  return u;
}

int64_t gcd(int64_t a, int64_t b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

void output(int64_t p, int64_t q) {
  int64_t g = gcd(p, q);
  printf("%ld/%ld\n", p/g, q/g);
}

int64_t solve(int r, int x) {
  int p = findLower(x, r);
  int h = D[x] - D[p];
  return W[p] - (p - r - 1) + 1LL * (r + 1) * h;
}

int64_t solve(int l, int r, int x) {
  int64_t ans = solve(r, x);
  if (l > 0) ans -= solve(l-1, x);
  return ans;
}

struct Node {
  int l, i;
};

int main() {
  memset(R, 0x3F, sizeof(R));
  memset(X, -1, sizeof(X));

  scanf("%d", &N);
  for (int i = 0; i < N-1; i++) {
    int l;
    scanf("%d", &l);
    L[i+1] = l - 1;
  }
  stack<Node> st;
  for (int i = 1; i < N; i++) {
    while (!st.empty() && st.top().l >= L[i]) st.pop();
    st.push(Node{L[i], i});
  }
  vector<Node> nodes;
  while (!st.empty()) {
    nodes.push_back(st.top());
    st.pop();
  }
  reverse(nodes.begin(), nodes.end());

  for (int i = 0; i < (int)nodes.size(); i++) {
    R[nodes[i].i]= nodes[i].i;
  }
  for (int i = N-1; i >= 0; i--) {
    R[i] = min(R[i], R[i+1]);
  }

  Graph g(N, 2*(N-1));
  for (int u = 0; u < N; u++) {
    int v = R[L[u]];
    if (v != u) {
      g.addEdge(u, v);
      g.addEdge(v, u);
    }
  }

  dfs1(g, R[0], -1, 0);
  dfs2(g, R[0], -1);

  binaryLift(g);

  int t;
  scanf("%d", &t);
  while (t--) {
    int l, r, x;
    scanf("%d%d%d", &l, &r, &x);
    l--; r--; x--;
    int64_t p = solve(l, r, x);
    int64_t q = r - l + 1;
    output(p, q);
  }

  return 0;
}
