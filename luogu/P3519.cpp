// https://www.luogu.com.cn/problem/P3519
// [POI2011]ROZ-Difference

#include <bits/stdc++.h>
using namespace std;


const int MAXN = 1000010;
int N;
char S[MAXN];
vector<int> bin[26];

int main() {
  scanf("%d", &N);
  scanf("%s", S+1);
  for (int i = 1; i <= N; i++) {
    bin[S[i]-'a'].push_back(i);
  }
  int ans = 0;
  for (int i = 0; i < 26; i++) {
    if (bin[i].empty()) continue;
    for (int j = 0; j < 26; j++) {
      if (i == j || bin[j].empty()) continue;
      int p = 0, q = 0;
      int all = -1;
      bool fir = false;
      while (p < (int)bin[i].size() || q < (int)bin[j].size()) {
        int ci = (p == (int)bin[i].size() ? 1e9 : bin[i][p]);
        int cj = (q == (int)bin[j].size() ? 1e9 : bin[j][q]);
        if (ci < cj) {
          all++;
          p++;
        }
        if (ci > cj) {
          if (fir) all--;
          q++;
          fir = true;
        }
        if (all < 0) {
          all = -1;
          fir = false;
        }
        ans = max(ans, all);
      }
    }
  }
  printf("%d\n", ans);

  return 0;
}
