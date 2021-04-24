// https://codeforces.com/problemset/problem/115/B
// Lawnmower

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 155;
const int INF = 0x3F3F3F3F;
int N, M;
int A[MAXN][MAXN];
int L[MAXN], R[MAXN];
int dp[MAXN][MAXN];
int last;

int min3(int a, int b, int c) {
  return min(a, min(b, c));
}

void process0(int row) {
  memset(dp[row], 0x3F, sizeof(dp[row]));
  int prev = row - 1;
  for (int i = M; i >= R[row]; i--) {
    dp[row][i] = min3(dp[row][i], dp[row][i+1]+1, dp[prev][i]+1);
  }
  for (int i = R[row]-1; i >= 1; i--) {
    dp[row][i] = min(dp[row][i], dp[row][i+1] + 1);
  }
  for (int i = L[row]+1; i <= M; i++) {
    dp[row][i] = INF;
  }
}

void process1(int row) {
  memset(dp[row], 0x3F, sizeof(dp[row]));
  int prev = row - 1;
  for (int i = 1; i <= L[row]; i++) {
    dp[row][i] = min3(dp[row][i], dp[row][i-1]+1, dp[prev][i]+1);
  }
  for (int i = L[row]+1; i <= M; i++) {
    dp[row][i] = min(dp[row][i], dp[row][i-1] + 1);
  }
  for (int i = R[row]-1; i >= 1; i--) {
    dp[row][i] = INF;
  }
}

int main() {
  memset(dp, 0x3F, sizeof(dp));
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; i++) {
    char s[MAXN];
    scanf("%s", s+1);
    for (int j = 1; j <= M; j++) {
      A[i][j] = (s[j] != 'G');
    }
  }
  for (int i = 1; i <= N; i++) {
    L[i] = M+1;
    R[i] = 0;
  }
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      if (A[i][j]) {
        if (L[i] == M+1) L[i] = j;
        R[i] = j;
      }
    }
    if (L[i] != M+1) last = i;
  }
  if (last == 0) {
    printf("0\n");
    return 0;
  }

  dp[0][1] = -1;
  for (int i = 1; i <= last; i++) {
    if (i & 1) process1(i);
    else process0(i);
  }

  printf("%d\n", dp[last][last&1 ? R[last] : L[last]]);
  return 0;
}
