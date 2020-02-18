// https://www.luogu.com.cn/problem/P2859
// [USACO06FEB]摊位预订Stall Reservations

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50010;

struct Point {
  int type, x, id;
  bool operator < (const Point& other) const {
    if (x != other.x) return x < other.x;
    if (type != other.type) return type < other.type;
    return id < other.id;
  }
} P[2*MAXN];

int N;
int C[MAXN];

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    P[2*i] = {0, a, i};
    P[2*i+1] = {1, b, i};
  }
  sort(P, P+2*N);
  vector<int> slots;
  int ans = 0, cnt = 0;
  for (int i = 0; i < 2*N; i++) {
    if (P[i].type == 0) {
      if (!slots.empty()) {
        C[P[i].id] = slots.back();
        slots.pop_back();
        cnt++;
      } else {
        C[P[i].id] = ++cnt;
      }
      ans = max(ans, cnt);
    } else {
      cnt--;
      slots.push_back(C[P[i].id]);
    }
  }
  printf("%d\n", ans);
  for (int i = 0; i < N; i++) {
    printf("%d\n", C[i]);
  }

  return 0;
}
