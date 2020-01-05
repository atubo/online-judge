// https://www.luogu.com.cn/problem/P1223
// 排队接水

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;

struct Person {
  int id, t;
  bool operator <  (const Person& other) const {
    if (t != other.t) return t < other.t;
    return id < other.id;
  }
} P[MAXN];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int t;
    scanf("%d", &t);
    P[i] = {i+1, t};
  }
  sort(P, P+n);
  double ans = 0;
  for (int i = 0; i < n; i++) {
    printf("%d ", P[i].id);
    ans += 1.0 * P[i].t * (n-1-i);
  }
  printf("\n%.2f\n", ans/n);

  return 0;
}
