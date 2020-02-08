// https://www.luogu.com.cn/problem/P3974
// [TJOI2015]组合数学

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int T;
int N, M;
int A[MAXN][MAXN];

class LinkedList {
  struct Data {
    int prev, next;
    int64_t val;
  };
 public:
  void reset() {
    memset(data_, 0, MAXN*sizeof(Data));
    data_[0] = {-1, -1, 0};
  }

  int remove(int curr) {
    int prev = data_[curr].prev;
    int next = data_[curr].next;
    if (prev != -1) {
      data_[prev].next = next;
    }
    if (next != -1) {
      data_[next].prev = prev;
    }
    data_[curr].val = 0;
    data_[curr].prev = data_[curr].next = -1;
    return prev;
  }

  int insert(int curr, int val, int pos) {
    assert(curr != -1);
    assert(curr <= pos);
    if (curr == pos) {
      data_[curr].val += val;
    } else {
      int next = data_[curr].next;
      data_[pos] = {curr, next, val};
      data_[curr].next = pos;
      if (next != -1) {
        data_[next].prev = pos;
      }
    }
    return pos;
  }

  int next(int curr) const {
    return data_[curr].next;
  }

  int prev(int curr) const {
    return data_[curr].prev;
  }

  int64_t& val(int curr) {
    return data_[curr].val;
  }

 private:
  Data data_[MAXN];
} L;

int64_t backtrack(int needed, int& curr) {
  int64_t ans = 0;
  while (curr != 0 && L.val(curr) <= needed) {
    needed -= L.val(curr);
    curr = L.remove(curr);
  }
  if (curr != 0) {
    assert(L.val(curr) > needed);
    L.val(curr) -= needed;
  } else {
    ans = needed;
  }
  return ans;
}

void solve() {
  L.reset();
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      scanf("%d", &A[i][j]);
    }
  }
  int64_t ans = 0;
  for (int i = 1; i <= N; i++) {
    int curr = 0;
    for (int j = 1; j <= M; j++) {
      if (L.next(curr) != -1 && L.next(curr) <= j) curr = L.next(curr);
      ans += backtrack(A[i][j], curr);
      curr = L.insert(curr, A[i][j], j);
    }
  }
  printf("%ld\n", ans);
}

int main() {
  scanf("%d", &T);
  while (T--) {
    solve();
  }
  return 0;
}
