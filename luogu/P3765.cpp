// https://www.luogu.com.cn/problem/P3765
// 总统选举

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

const int MAXTRY = 15;
const int MAXN = 500010;
int N, M;
int A[MAXN];

int countVote(const ordered_set& c, int l, int r) {
  return c.order_of_key(r+1) - c.order_of_key(l);
}

int nextpos(int l, int r) {
  const int n = r - l + 1;
  return (rand() % n) + l;
}


int elect(const vector<ordered_set>& candidate, int l, int r) {
  const int n = r - l + 1;
  for (int i = 0; i < MAXTRY; i++) {
    int p = nextpos(l, r);
    int c = A[p];
    int m = countVote(candidate[c], l, r);
    if (m > n/2) {
      return c;
    }
  }
  return -1;
}

void vote(vector<ordered_set>& candidate, int v, int k) {
  int pk = A[v];
  A[v] = k;
  candidate[pk].erase(v);
  candidate[k].insert(v);
}

int main() {
  scanf("%d%d", &N, &M);
  vector<ordered_set> candidate(N+1);
  for (int i = 1; i <= N; i++) {
    int c;
    scanf("%d", &c);
    A[i] = c;
    candidate[c].insert(i);
  }

  for (int i = 0; i < M; i++) {
    int l, r, s, k;
    scanf("%d%d%d%d", &l, &r, &s, &k);
    int e = elect(candidate, l, r);
    printf("%d\n", (e > 0 ? e : s));
    for (int j = 0; j < k; j++) {
      int v;
      scanf("%d", &v);
      vote(candidate, v, e > 0 ? e : s);
    }
  }
  printf("%d\n", elect(candidate, 1, N));

  return 0;
}
