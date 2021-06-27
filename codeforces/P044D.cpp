// https://codeforces.com/problemset/problem/44/D
// Hyperdrive

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;
struct Point {
  int x, y, z;
} P[MAXN];
int N;
double D[MAXN];

double dist(const Point& p, const Point& q) {
  int dx = p.x - q.x;
  int dy = p.y - q.y;
  int dz = p.z - q.z;
  return sqrt(dx*dx + dy*dy + dz*dz);
}

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].z);
  }
  for (int i = 1; i < N; i++) {
    D[i] = dist(P[i], P[0]);
  }
  double ret = 1e9;
  for (int i = 1; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      ret = min(ret, 0.5*(D[i] + D[j] + dist(P[i], P[j])));
    }
  }
  printf("%.10f\n", ret);
  return 0;
}
