// https://www.luogu.com.cn/problem/P2499
// [SDOI2012]象棋

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

template <typename T>
struct hungarian {  // km
  int n;
  vector<int> matchx;  // 左集合对应的匹配点
  vector<int> matchy;  // 右集合对应的匹配点
  vector<int> pre;     // 连接右集合的左点
  vector<bool> visx;   // 拜访数组 左
  vector<bool> visy;   // 拜访数组 右
  vector<T> lx;
  vector<T> ly;
  vector<vector<T> > g;
  vector<T> slack;
  T inf;
  T res;
  queue<int> q;
  int org_n;
  int org_m;

  hungarian(int _n, int _m) {
    org_n = _n;
    org_m = _m;
    n = max(_n, _m);
    inf = numeric_limits<T>::max();
    res = 0;
    g = vector<vector<T> >(n, vector<T>(n));
    matchx = vector<int>(n, -1);
    matchy = vector<int>(n, -1);
    pre = vector<int>(n);
    visx = vector<bool>(n);
    visy = vector<bool>(n);
    lx = vector<T>(n, -inf);
    ly = vector<T>(n);
    slack = vector<T>(n);
  }

  void addEdge(int u, int v, int w) {
    g[u][v] = max(w, 0);  // 负值还不如不匹配 因此设为0不影响
  }

  bool check(int v) {
    visy[v] = true;
    if (matchy[v] != -1) {
      q.push(matchy[v]);
      visx[matchy[v]] = true;  // in S
      return false;
    }
    // 找到新的未匹配点 更新匹配点 pre 数组记录着"非匹配边"上与之相连的点
    while (v != -1) {
      matchy[v] = pre[v];
      swap(v, matchx[pre[v]]);
    }
    return true;
  }

  void bfs(int i) {
    while (!q.empty()) {
      q.pop();
    }
    q.push(i);
    visx[i] = true;
    while (true) {
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
          if (!visy[v]) {
            T delta = lx[u] + ly[v] - g[u][v];
            if (slack[v] >= delta) {
              pre[v] = u;
              if (delta) {
                slack[v] = delta;
              } else if (check(v)) {  // delta=0 代表有机会加入相等子图 找增广路
                                      // 找到就return 重建交错树
                return;
              }
            }
          }
        }
      }
      // 没有增广路 修改顶标
      T a = inf;
      for (int j = 0; j < n; j++) {
        if (!visy[j]) {
          a = min(a, slack[j]);
        }
      }
      for (int j = 0; j < n; j++) {
        if (visx[j]) {  // S
          lx[j] -= a;
        }
        if (visy[j]) {  // T
          ly[j] += a;
        } else {  // T'
          slack[j] -= a;
        }
      }
      for (int j = 0; j < n; j++) {
        if (!visy[j] && slack[j] == 0 && check(j)) {
          return;
        }
      }
    }
  }

  T solve() {
    // 初始顶标
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        lx[i] = max(lx[i], g[i][j]);
      }
    }

    for (int i = 0; i < n; i++) {
      fill(slack.begin(), slack.end(), inf);
      fill(visx.begin(), visx.end(), false);
      fill(visy.begin(), visy.end(), false);
      bfs(i);
    }

    // custom
    for (int i = 0; i < n; i++) {
      if (g[i][matchx[i]] > 0) {
        res += g[i][matchx[i]];
      } else {
        matchx[i] = -1;
      }
    }
#if 0
    cout << res << "\n";
    for (int i = 0; i < org_n; i++) {
      cout << matchx[i] + 1 << " ";
    }
    cout << "\n";
#endif
    return res;
  }
};

const int MAXN = 105;
const int MAXK = 512;
int N, M, K, A, B;
int C[MAXN][MAXN]; // 0: empty, -1: obstacle, >0: destinations
int D[MAXK][MAXK];
bool vis[MAXN][MAXN];
const int DX[4] = {1, 1, -1, -1};
const int DY[4] = {1, -1, 1, -1};

struct Pos {
  int x, y;
} P[MAXK], Q[MAXK];

struct Node {
  int x, y, d;
} QU[MAXN*MAXN];

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

bool inRange(int x, int y) {
  return 0 <= x && x < N && 0 <= y && y < M;
}

void bfs(int u, int x0, int y0) {
  int first = 0;
  int last = 0;
  vector<Pos> marked;
  QU[last++] = {x0, y0, 0};
  vis[x0][y0] = true;
  marked.push_back({x0, y0});
  while (first < last) {
    Node p = QU[first++];
    int x = p.x;
    int y = p.y;
    int d = p.d;
    if (C[x][y] > 0) {
      D[u][C[x][y]-1] = d;
    }
    for (int dir = 0; dir < 4; dir++) {
      int x2 = x + DX[dir]*A;
      int y2 = y + DY[dir]*B;
      if (inRange(x2, y2) && C[x2][y2] >= 0 && !vis[x2][y2]) {
        QU[last++] = {x2, y2, d+1};
        vis[x2][y2] = true;
        marked.push_back({x2, y2});
      }
    }
    if (A != B) {
      for (int dir = 0; dir < 4; dir++) {
        int x2 = x + DX[dir]*B;
        int y2 = y + DY[dir]*A;
        if (inRange(x2, y2) && C[x2][y2] >= 0 && !vis[x2][y2]) {
          QU[last++] = {x2, y2, d+1};
          vis[x2][y2] = true;
          marked.push_back({x2, y2});
        }
      }
    }
  }

  for (const auto& p : marked) {
    vis[p.x][p.y] = false;
  }
}

int solve(const vector<Pos>& pv, const vector<Pos>& qv) {
  const int MAXC = 1000000;
  assert(pv.size() == qv.size());
  if (pv.empty()) return 0;
  const int m = pv.size();
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      D[i][j] = MAXC;
    }
  }
  // mark destinations
  for (int i = 0; i < m; i++) {
    int x = qv[i].x;
    int y = qv[i].y;
    assert(C[x][y] == 0);
    C[x][y] = i + 1;
  }

  for (int i = 0; i < m; i++) {
    bfs(i, pv[i].x, pv[i].y);
  }

  // restore
  for (int i = 0; i < m; i++) {
    int x = qv[i].x;
    int y = qv[i].y;
    C[x][y] = 0;
  }

#if 0
  MincostMaxflow flow(2*m+2, 2*m + m*m);
  for (int i = 0; i < m; i++) {
    flow.addEdge(0, i+1, 0, 1);
    for (int j = 0; j < m; j++) {
      if (D[i][j] < MAXC) {
        flow.addEdge(i+1, m+1+j, D[i][j], 1);
      }
    }
    flow.addEdge(m+1+i, 2*m+1, 0, 1);
  }
  pair<int64_t, int64_t> ret = flow.mincostFlow(0, 2*m+1);

  return ret.second;
#endif
  const int CEIL = 20000;
  hungarian<int> h(m, m);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      if (D[i][j] < MAXC) {
        h.addEdge(i, j, CEIL - D[i][j]);
      }
    }
  }
  return m*CEIL - h.solve();
}

int main() {
  scanf("%d%d%d%d%d", &N, &M, &K, &A, &B);
  A = abs(A);
  B = abs(B);
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < M; j++) {
      if (s[j] == '*') C[i][j] = -1;
    }
  }
  for (int i = 0; i < K; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    P[i] = {x, y};
  }
  for (int i = 0; i < K; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    Q[i] = {x, y};
  }
  int g = gcd(A, B);
  int ans = 0;
  for (int x0 = 0; x0 < g; x0++) {
    for (int y0 = 0; y0 < g; y0++) {
      vector<Pos> pv, qv;
      for (int i = 0; i < K; i++) {
        const Pos p = P[i];
        if (abs(p.x - x0) % g == 0 && abs(p.y - y0) % g == 0) {
          pv.push_back(p);
        }
      }
      for (int i = 0; i < K; i++) {
        const Pos q = Q[i];
        if (abs(q.x - x0) % g == 0 && abs(q.y - y0) % g == 0) {
          qv.push_back(q);
        }
      }
      ans += solve(pv, qv);
    }
  }
  printf("%d\n", ans);
  return 0;
}
