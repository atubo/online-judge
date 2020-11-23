// https://www.luogu.com.cn/problem/P3350
// [ZJOI2016]旅行者

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20010;
const int MAXQ = 100010;
int N, M;
// S, E, N, W
const int DX[4] = {1, 0, -1, 0};
const int DY[4] = {0, 1, 0, -1};

struct Query {
  int x1, y1, x2, y2, id;
} Q[MAXQ], Q1[MAXQ], Q2[MAXQ];
int ans[MAXQ];

#define P(a, b) ((a)*M + b)

int dis[MAXN];
bool vis[MAXN];
int D[MAXN][4];

struct Node {
  int val, x, y;
  Node() {}
  Node(int a, int b, int c): val(a), x(b), y(c) {}
  bool operator < (const Node& other) const {
    return val > other.val;
  }
};

void dijkstra(int sx, int sy, int lx, int rx, int ly, int ry) {
  for (int i = lx; i <= rx; i++) {
    for (int j = ly; j <= ry; j++) {
      dis[P(i, j)] = 1<<30;
      vis[P(i, j)] = 0;
    }
  }
  dis[P(sx, sy)] = 0;
  priority_queue<Node> pq;
  pq.push(Node(0, sx, sy));
  while (!pq.empty()) {
    int x = pq.top().x;
    int y = pq.top().y;
    pq.pop();
    if (vis[P(x, y)]) continue;
    vis[P(x, y)] = true;
    for (int d = 0; d < 4; d++) {
      int tx = x + DX[d];
      int ty = y + DY[d];
      if (lx <= tx && tx <= rx && ly <= ty && ty <= ry &&
          dis[P(tx, ty)] > dis[P(x, y)] + D[P(x, y)][d]) {
        dis[P(tx, ty)] = dis[P(x, y)] + D[P(x, y)][d];
        pq.push(Node(dis[P(tx, ty)], tx, ty));
      }
    }
  }
}

void solve(int lx, int rx, int ly, int ry, int lq, int rq) {
  if (lq > rq) return;
  if (lx == rx && ly == ry) {
    for (int i = lq; i <= rq; i++) {
      ans[Q[i].id] = 0;
    }
    return;
  }
  int h1 = 0, h2 = 0;
  if (rx - lx > ry - ly) {
    int mid = (lx + rx) / 2;
    for (int i = ly; i <= ry; i++) {
      dijkstra(mid, i, lx, rx, ly, ry);
      for (int j = lq; j <= rq; j++) {
        ans[Q[j].id] = min(ans[Q[j].id],
            dis[P(Q[j].x1, Q[j].y1)] + dis[P(Q[j].x2, Q[j].y2)]);
      }
    }
    for (int i = lq; i <= rq; i++) {
      if (Q[i].x1 <= mid && Q[i].x2 <= mid) Q1[h1++] = Q[i];
      if (Q[i].x1 > mid && Q[i].x2 > mid) Q2[h2++] = Q[i];
    }
    for (int i = lq; i < lq + h1; i++) {
      Q[i] = Q1[i-lq];
    }
    for (int i = lq + h1; i < lq+h1+h2; i++) {
      Q[i] = Q2[i-lq-h1];
    }
    solve(lx, mid, ly, ry, lq, lq+h1-1);
    solve(mid+1, rx, ly, ry, lq+h1, lq+h1+h2-1);
  } else {
    int mid = (ly + ry) / 2;
    for (int i = lx; i <= rx; i++) {
      dijkstra(i, mid, lx, rx, ly, ry);
      for (int j = lq; j <= rq; j++) {
        ans[Q[j].id] = min(ans[Q[j].id],
            dis[P(Q[j].x1, Q[j].y1)] + dis[P(Q[j].x2, Q[j].y2)]);
      }
    }
    for (int i = lq; i <= rq; i++) {
      if (Q[i].y1 <= mid && Q[i].y2 <= mid) Q1[h1++] = Q[i];
      if (Q[i].y1 > mid && Q[i].y2 > mid) Q2[h2++] = Q[i];
    }
    for (int i = lq; i < lq + h1; i++) {
      Q[i] = Q1[i-lq];
    }
    for (int i = lq + h1; i < lq + h1 + h2; i++) {
      Q[i] = Q2[i-lq-h1];
    }
    solve(lx, rx, ly, mid, lq, lq+h1-1);
    solve(lx, rx, mid+1, ry, lq+h1, lq+h1+h2-1);
  }
}

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M-1; j++) {
      int r;
      scanf("%d", &r);
      D[P(i, j)][1] = D[P(i, j+1)][3] = r;
    }
  }
  for (int i = 0; i < N-1; i++) {
    for (int j = 0; j < M; j++) {
      int c;
      scanf("%d", &c);
      D[P(i, j)][0] = D[P(i+1, j)][2] = c;
    }
  }
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    x1--; y1--; x2--; y2--;
    Q[i] = {x1, y1, x2, y2, i};
  }
  memset(ans, 0x3f, sizeof(ans));
  solve(0, N-1, 0, M-1, 0, q-1);
  for (int i = 0; i < q; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
