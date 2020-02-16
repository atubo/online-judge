// https://www.luogu.com.cn/problem/P1912
// [NOI2009]诗人小G

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int T;
int N, L, P;
char Q[MAXN][32];
int S[MAXN];
long double dp[MAXN];
int prev[MAXN];

struct Data {
  Data(int xx, int ll): x(xx), l(ll) {}
  int x, l;
};

long double qpow(long double x, int n) {
  long double ret = 1;
  while (n) {
    if (n & 1) ret *= x;
    x *= x;
    n >>= 1;
  }
  assert(ret >= 0);
  return ret;
}

long double eval(int from, int to) {
  return dp[from] + qpow(abs(S[to]-S[from]+(to-from-1)-L), P);
}

void solve() {
  scanf("%d%d%d", &N, &L, &P);
  for (int i = 1; i <= N; i++) {
    scanf("%s", Q[i]);
    S[i] = S[i-1] + strlen(Q[i]);
  }
  deque<Data> q;
  q.emplace_front(0, 1);
  dp[0] = 0;
  for (int i = 1; i <= N; i++) {
    while (q.size() > 1 && q[1].l <= i) q.pop_front();
    int j = q.front().x;
    dp[i] = eval(j, i);
    ::prev[i] = j;
    if (eval(q.back().x, N) <= eval(i, N)) continue;
    int l2 = N;
    for (j = q.size()-1; j >= 0; j--) {
      int x = q[j].x;
      int l = q[j].l;
      if (eval(i, l) <= eval(x, l)) {
        q.pop_back();
        l2 = l;
      }
      else {
        break;
      }
    }
    q.emplace_back(i, l2);
    if (q.size() > 1) {
      int lo = q[q.size()-2].l;
      int x = q[q.size()-2].x;
      int hi = l2;
      while (lo < hi-1) {
        int mid = (lo + hi) / 2;
        if (eval(x, mid) < eval(i, mid)) lo = mid;
        else hi = mid;
      }
      q.back().l = hi;
    }
  }
  if (dp[N] <= 1e18) {
    printf("%ld\n", (int64_t)dp[N]);
    stack<string> ans;
    int end = N;
    while (end != 0) {
      int start = ::prev[end];
      string line;
      for (int i = start+1; i <= end; i++) {
        line += Q[i];
        line.push_back(' ');
      }
      line.pop_back();
      ans.push(line);
      end = start;
    }
    while (!ans.empty()) {
      printf("%s\n", ans.top().c_str());
      ans.pop();
    }
  } else {
    printf("Too hard to arrange\n");
  }
  printf("--------------------\n");
}

int main() {
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
