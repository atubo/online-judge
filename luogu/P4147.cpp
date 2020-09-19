// https://www.luogu.com.cn/problem/P4147
// 玉蟾宫

#include <bits/stdc++.h>
using namespace std;

struct Data {
  Data(int xx, int yy) : x(xx), y(yy) {}
  int x, y;
};

int solve(const vector<int>& a) {
  stack<Data> st;
  st.push(Data{0, 0});
  int ans = 0;
  for (int i = 1; i < (int)a.size(); i++) {
    int y = a[i];
    int x = i;
    while (!st.empty() && y <= st.top().y) {
      ans = max(ans, st.top().y * (i - st.top().x));
      x = st.top().x;
      st.pop();
    }
    st.push(Data{x, y});
  }

  return ans;
}

int N, M;

int main() {
  scanf("%d%d", &N, &M);
  int ans = 0;
  vector<int> a(M+2, 0);
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      char c;
      cin >> c;
      if (c == 'R') a[j] = 0;
      else a[j]++;
    }
    ans = max(ans, solve(a));
  }
  printf("%d\n", 3 * ans);

  return 0;
}
