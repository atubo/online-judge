// https://www.luogu.com.cn/problem/P3476
// [POI2008]TRO-Triangles

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3010;

struct Point {
  int x, y;
  bool operator < (const Point& other) const {
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
} P[MAXN];

int N;
int Q[MAXN], Q2[MAXN];

class Cmp {
 public:
  Cmp(int _c) : c(_c) {}
  bool operator ()(int a, int b) const {
    int dx1 = P[Q[a]].x - P[Q[c]].x;
    int dy1 = P[Q[a]].y - P[Q[c]].y;
    int dx2 = P[Q[b]].x - P[Q[c]].x;
    int dy2 = P[Q[b]].y - P[Q[c]].y;
    return 1LL*dx1*dy2 > 1LL*dx2*dy1;
  }
 private:
  int c;
};

int main() {
  scanf("%d", &N);
  int64_t sx = 0, sy = 0;
  for (int i = 0; i < N; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    P[i] = {x, y};
    sx += x;
    sy += y;
  }
  sort(P, P+N);
  for (int i = 0; i < N; i++) {
    Q[i] = i;
  }
  long double ans = 0;
  for (int i = 0; i < N-2; i++) {
    memcpy(Q2+i+1, Q+i+1, (N-i-1)*sizeof(int));
    sx -= P[i].x;
    sy -= P[i].y;
    int64_t sx2 = sx;
    int64_t sy2 = sy;
    Cmp cmp(i);
    sort(Q2+i+1, Q2+N, cmp);
    int x1 = P[i].x, y1 = P[i].y;
    for (int j = i+1; j < N-1; j++) {
      int x2 = P[Q2[j]].x;
      int y2 = P[Q2[j]].y;
      sx2 -= x2;
      sy2 -= y2;
      ans += 1.0*x1*y2*(N-j-1) - 1.0*x2*y1*(N-j-1) +
             1.0*(x2-x1)*sy2 + 1.0*(y1-y2)*sx2;
    }
  }
  printf("%.1Lf\n", 0.5*ans);

  return 0;
}
