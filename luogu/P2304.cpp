// https://www.luogu.org/problem/P2304
// [NOI2015]小园丁与老司机

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;

void sortuniq(vector<int>& x) {
  sort(x.begin(), x.end());
  x.erase(unique(x.begin(), x.end()), x.end());
}

int findidx(const vector<int>& a, int x) {
  return lower_bound(a.begin(), a.end(), x) - a.begin();
}

int hcount(int i, int j, int n) {
  if (i == j) return 0;
  if (i > j) return n-1-j;
  return j;
}

void htravel(int p, int q, const vector<int>& h) {
  const int n = h.size();
  if (p > q) {
    for (int i = p; i < n; i++) {
      printf("%d ", h[i]);
    }
    for (int i = p-1; i >= q; i--) {
      printf("%d ", h[i]);
    }
  } else if (p < q) {
    for (int i = p; i >= 0; i--) {
      printf("%d ", h[i]);
    }
    for (int i = p+1; i <= q; i++) {
      printf("%d ", h[i]);
    }
  } else {
    printf("%d ", h[p]);
  }
}

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

struct Tree {
  int x, y;
  int id, hid, vid, neid, nwid;
  int nxt[3];
} T[MAXN];

int dp[MAXN], dp2[MAXN];
int succ[MAXN];
bool vis[MAXN];
int deg[MAXN], MP[MAXN];

int N;

void travel(const vector<vector<int>> &H) {
  int t = dp[0] - 1;
  int id = 0;
  while (t > 0) {
    int id2 = succ[id];
    int h = T[id2].hid;
    const int n = H[h].size();
    int p = -1;
    for (int i = 0; i < n; i++) {
      if (H[h][i] == id2) {
        p = i;
        break;
      }
    }
    assert(p >= 0);
    for (int q = 0; q < n; q++) {
      int id3 = H[h][q];
      int m = hcount(p, q, n);
      if (m + dp2[id3] == t) {
        htravel(p, q, H[h]);
        t -= m + 1;
        id = id3;
        break;
      }
    }
  }
  printf("\n");
}

Graph buildGraph(const vector<vector<int>> &H) {
  Graph g(N+1, 3*(N+1));
  queue<int> q;
  q.push(0);
  vis[0] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int d = 0; d < 3; d++) {
      int v = T[u].nxt[d];
      if (v >= 0 && dp2[u] == dp[v]+1) {
        g.addEdge(u, v);
        int h = T[v].hid;
        const int n = H[h].size();
        int x = -1;
        for (int i = 0; i < n; i++) {
          if (H[h][i] == v) {
            x = i;
            break;
          }
        }
        assert(x >= 0);
        for (int y = 0; y < n; y++) {
          int w = H[h][y];
          int m = hcount(x, y, n);
          if (dp[v] == m + dp2[w] && !vis[w]) {
            q.push(w);
            vis[w] = true;
          }
        }
      }
    }
  }
  return g;
}

void solve2(const Graph& g) {
  int n = 0;
  int m = 0;
  memset(MP, -1, sizeof(MP));
  for (int i = 0; i <= N; i++) {
    for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
      if (MP[i] == -1) MP[i] = n++;
      m++;
      int j = g.E[eidx].to;
      if (MP[j] == -1) MP[j] = n++;
      int u = MP[i];
      int v = MP[j];
      deg[u]--;
      deg[v]++;
    }
  }

  Dinic dinic(n+2, m+n);
  const int src = n, dst = n+1;
  int ans = 0;
  for (int i = 0; i <= N; i++) {
    int u = MP[i];
    if (u == -1) continue;
    ans += (deg[u] > 0 ? deg[u] : 0);
    if (deg[u] < 0) {
      dinic.addEdge(u, dst, -deg[u]);
    } else if (deg[u] > 0) {
      dinic.addEdge(src, u, deg[u]);
    }
    for (int eidx = g.head[i]; ~eidx; eidx = g.E[eidx].next) {
      int j = g.E[eidx].to;
      int v = MP[j];
      assert(v >= 0);
      dinic.addEdge(u, v, Dinic::inf);
    }
  }
  int flow = dinic.dinic(src, dst);
  printf("%d\n", ans-flow);
}

int main() {
  scanf("%d", &N);
  vector<int> xpos(N+1), ypos(N+1), nepos(N+1), nwpos(N+1);
  for (int d = 0; d < 3; d++) T[0].nxt[d] = -1;

  for (int i = 1; i <= N; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    T[i] = {x, y, i};
    for (int d = 0; d < 3; d++) T[i].nxt[d] = -1;
    xpos[i] = x;
    ypos[i] = y;
    nepos[i] = x - y;
    nwpos[i] = x + y;
  }

  sortuniq(xpos);
  sortuniq(ypos);
  sortuniq(nepos);
  sortuniq(nwpos);

  vector<vector<int>> H(ypos.size());
  vector<vector<int>> V(xpos.size());
  vector<vector<int>> NE(nepos.size());
  vector<vector<int>> NW(nwpos.size());

  for (int i = 0; i <= N; i++) {
    T[i].hid = findidx(ypos, T[i].y);
    T[i].vid = findidx(xpos, T[i].x);
    T[i].neid = findidx(nepos, T[i].x - T[i].y);
    T[i].nwid = findidx(nwpos, T[i].x + T[i].y);
    int id = T[i].id;
    H[T[i].hid].push_back(id);
    V[T[i].vid].push_back(id);
    NE[T[i].neid].push_back(id);
    NW[T[i].nwid].push_back(id);
  }

  for (auto&v : H) {
    sort(v.begin(), v.end(), [](int i, int j) {return T[i].x < T[j].x;});
  }
  for (auto&v : V) {
    sort(v.begin(), v.end(), [](int i, int j) {return T[i].y < T[j].y;});
    for (int i = 0; i < (int)v.size()-1; i++) {
      T[v[i]].nxt[1] = v[i+1];
    }
  }
  for (auto&v : NE) {
    sort(v.begin(), v.end(), [](int i, int j) {return T[i].y < T[j].y;});
    for (int i = 0; i < (int)v.size()-1; i++) {
      T[v[i]].nxt[2] = v[i+1];
    }
  }
  for (auto&v : NW) {
    sort(v.begin(), v.end(), [](int i, int j) {return T[i].y < T[j].y;});
    for (int i = 0; i < (int)v.size()-1; i++) {
      T[v[i]].nxt[0] = v[i+1];
    }
  }

  for (int h = H.size()-1; h >= 0; h--) {
    const int n = H[h].size();
    for (int i = 0; i < n; i++) {
      int id = H[h][i];
      dp2[id] = 1;
      succ[id] = -1;
      for (int d = 0; d < 3; d++) {
        int id2 = T[id].nxt[d];
        if (id2 != -1) {
          if (dp[id2] + 1 > dp2[id]) {
            dp2[id] = 1 + dp[id2];
            succ[id] = id2;
          }
        }
      }
    }
    for (int i = 0; i < n; i++) {
      int id = H[h][i];
      dp[id] = dp2[id];
      for (int j = 0; j < n; j++) {
        if (j == i) continue;
        int id2 = H[h][j];
        for (int d = 0; d < 3; d++) {
          int m = hcount(i, j, n);
          dp[id] = max(dp[id], m+dp2[id2]);
        }
      }
    }
  }

  printf("%d\n", dp[0]-1);

  travel(H);

  Graph g = buildGraph(H);

  solve2(g);
  return 0;
}
