// https://codeforces.com/problemset/problem/311/E
// Biologist

#include <bits/stdc++.h>
using namespace std;

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

  int dinic(int s, int t) {
    int ans = 0;
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

const int MAXN = 10010;
int N, M, G;
int S[MAXN];
int V[MAXN];

struct Rich {
  int s, w;
  vector<int> dogs;
  int g;
  void print() const {
    printf("%d %d [", s, w);
    for (int x : dogs) {
      printf("%d ", x);
    }
    printf("] %d\n", g);
  }
};

int addRich(vector<Rich>& rich) {
  int s, w, k;
  scanf("%d%d%d", &s, &w, &k);
  Rich r{.s = s, .w = w};
  for (int i = 0; i < k; i++) {
    int d;
    scanf("%d", &d);
    d--;
    r.dogs.push_back(d);
  }
  int g;
  scanf("%d", &g);
  r.g = g;
  rich.push_back(r);
  return w;
}

int main() {
  scanf("%d%d%d", &N, &M, &G);
  for (int i = 0; i < N; i++) {
    scanf("%d", &S[i]);
  }
  for (int i = 0; i < N; i++) {
    scanf("%d", &V[i]);
  }
  vector<Rich> rich;
  int tot = 0;
  for (int i = 0; i < M; i++) {
    tot += addRich(rich);
  }

  int totk = 0;
  for (const auto& r : rich) {
    totk += r.dogs.size();
  }

  Dinic dinic(N+M+2, 2*N+M+totk);
  int src = N+M, snk = N+M+1;
  for (int i = 0; i < N; i++) {
    if (S[i] == 0) {
      dinic.addEdge(src, i, V[i]);
      dinic.addEdge(i, snk, 0);
    } else {
      dinic.addEdge(src, i, 0);
      dinic.addEdge(i, snk, V[i]);
    }
  }
  for (int i = 0; i < M; i++) {
    int u = i + N;
    int c = rich[i].w + (rich[i].g ? G : 0);
    if (rich[i].s == 0) {
      dinic.addEdge(src, u, c);
      for (int d : rich[i].dogs) {
        dinic.addEdge(u, d, Dinic::inf);
      }
    } else {
      dinic.addEdge(u, snk, c);
      for (int d : rich[i].dogs) {
        dinic.addEdge(d, u, Dinic::inf);
      }
    }
  }

  int flow = dinic.dinic(src, snk);
  printf("%d\n", tot - flow);

  return 0;
}
