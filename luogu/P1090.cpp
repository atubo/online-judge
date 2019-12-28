// https://www.luogu.com.cn/problem/P1090
// 合并果子

#include <bits/stdc++.h>
using namespace std;

int N;

int main() {
  priority_queue<int, vector<int>, greater<int>> pq;
  scanf("%d", &N);
  for (int i = 0, x; i < N; i++) {
    scanf("%d", &x);
    pq.push(x);
  }
  int ans = 0;
  while (pq.size() >= 2) {
    int a = pq.top(); pq.pop();
    int b = pq.top(); pq.pop();
    int c = a + b;
    ans += c;
    pq.push(c);
  }
  printf("%d\n", ans);
  return 0;
}
