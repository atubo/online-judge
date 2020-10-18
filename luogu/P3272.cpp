// https://www.luogu.com.cn/problem/P3272
// [SCOI2011]地板

#include <bits/stdc++.h>
using namespace std;

const int MOD = 20110520;
const int MAXN = 110;
char A[MAXN][MAXN];
int N, M;
int dp[2][1<<20];

#define GET(x, i) ((x>>(2*i)) & 3)
#define SET(x, i, v) (x |= (v << (2*i)))
#define UNSET(x, i) (x &= ~(3 << (2*i)))

void search(int row, int col, int prev, int curr) {
  if (col == M) {
    (dp[row&1][curr] += dp[(row-1)&1][prev]) %= MOD;
    return;
  }
  if (A[row][col] == '*') {
    search(row, col+1, prev, curr);
    return;
  }
  if (GET(prev, col) == 0) {
    if (A[row+1][col] != '*') {
      SET(curr, col, 2);
      search(row, col+1, prev, curr);
      UNSET(curr, col);
    }
    int i = col+1;
    for (; i < M; i++) {
      if (GET(prev, i) != 0 || A[row][i] == '*') break;
      if (A[row+1][i] != '*') {
        SET(curr, i, 1);
        search(row, i+1, prev, curr);
        UNSET(curr, i);
      }
      if (A[row+1][col] != '*') {
        SET(curr, col, 1);
        search(row, i+1, prev, curr);
        UNSET(curr, col);
      }
    }
    if (i < M && A[row][i] != '*' && GET(prev, i) == 2) {
      search(row, i+1, prev, curr);
    }
  } else if (GET(prev, col) == 1) {
    search(row, col+1, prev, curr);
    if (A[row+1][col] != '*') {
      SET(curr, col, 1);
      search(row, col+1, prev, curr);
      UNSET(curr, col);
    }
  } else {
    assert(GET(prev, col) == 2);
    if (A[row+1][col] != '*') {
      SET(curr, col, 2);
      search(row, col+1, prev, curr);
      UNSET(curr, col);
    }
    int i = col+1;
    for (; i < M; i++) {
      if (GET(prev, i) != 0 || A[row][i] == '*') break;
      search(row, i+1, prev, curr);
    }
  }
}

int P3[12];

int encode(int s) {
  int e = 0;
  for (int i = 0; i < 12; i++) {
    if (s == 0) break;
    int r = s % 3;
    e |= (r << (2*i));
    s /= 3;
  }
  return e;
}

int main() {
  P3[0] = 1;
  for (int i = 1; i < 12; i++) {
    P3[i] = 3*P3[i-1];
  }
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    scanf("%s", A[i]);
  }
  bool hasSpace = false;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (A[i][j] == '_') {
        hasSpace = true;
        break;
      }
    }
    if (hasSpace) break;
  }
  if (!hasSpace) {
    printf("0");
    return 0;
  }
  if (N < M) {
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < M; j++) {
        swap(A[i][j], A[j][i]);
      }
    }
    swap(N, M);
  }
  for (int i = 0; i < M; i++) {
    A[N][i] = '*';
  }
  dp[1][0] = 1;
  for (int i = 0; i < N; i++) {
    memset(dp[i&1], 0, sizeof(dp[i&1]));
    for (int s = 0; s < P3[M]; s++) {
      int prev = encode(s);
      if (dp[(i-1)&1][prev] > 0) {
        search(i, 0, prev, 0);
      }
    }
  }
  printf("%d", dp[(N-1)&1][0]);
  return 0;
}
