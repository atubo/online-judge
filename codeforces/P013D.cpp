// https://codeforces.com/problemset/problem/13/D
// Triangles

#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
};

#define cross(x1, y1, x2, y2) (1LL*(x1)*(y2)-1LL*(x2)*(y1))
#define sgn(x) ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0))

int N, M;
Point R[500], B[500];
int C[500][500];

int calc(int i, int j) {
  Point a = R[i], b = R[j];
  Point o = R[0];
  int64_t c = cross(a.x-o.x, a.y-o.y, b.x-o.x, b.y-o.y);
  int s = sgn(c);
  return s * C[i][j];
}

void build(int i, int j) {
  Point a = R[i], b = R[j];
  Point o = R[0];
  for (int k = 0; k < M; k++) {
    Point c = B[k];
    int64_t c1 = cross(a.x-o.x, a.y-o.y, c.x-o.x, c.y-o.y);
    int64_t c2 = cross(b.x-a.x, b.y-a.y, c.x-a.x, c.y-a.y);
    int64_t c3 = cross(o.x-b.x, o.y-b.y, c.x-b.x, c.y-b.y);
    if (sgn(c1) == sgn(c2) && sgn(c2) == sgn(c3)) C[i][j]++;
  }
}

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    scanf("%d%d", &R[i].x, &R[i].y);
  }
  for (int i = 0; i < M; i++) {
    scanf("%d%d", &B[i].x, &B[i].y);
  }
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      build(i, j);
      C[j][i] = C[i][j];
    }
  }
  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      for (int k = j+1; k < N; k++) {
        ans += (calc(i, j) + calc(j, k) + calc(k, i) == 0);
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
