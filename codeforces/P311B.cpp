// https://codeforces.com/problemset/problem/311/B
// Cats Transport

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
const int MAXM = 100010;
int N, M, P;
int D[MAXN];
int H[MAXM], T[MAXM], T2[MAXM];
int64_t S[MAXM];
int64_t dp[MAXM][101];
const int64_t INF = 0x7F7F7F7F7F7F7F7F;
int buf[MAXM];

bool superior(int k, int j, int p, int i) {
  return dp[j][p] - 1LL * j * T2[i] + S[j] <=
         dp[k][p] - 1LL * k * T2[i] + S[k];
}

bool concave(int k, int j, int i, int p) {
  return (dp[i][p] + S[i] - dp[j][p] - S[j]) * (j - k) <=
         (dp[j][p] + S[j] - dp[k][p] - S[k]) * (i - j);
}

int main() {
  scanf("%d%d%d", &N, &M, &P);
  if (P >= M) {
    printf("0\n");
    return 0;
  }
  for (int i = 1; i < N; i++) {
    int d;
    scanf("%d", &d);
    D[i] = D[i-1] + d;
  }
  for (int i = 0; i < M; i++) {
    scanf("%d%d", &H[i], &T[i]);
    H[i]--;
    T2[i] = T[i] - D[H[i]];
  }
  sort(T2, T2+M);
  S[0] = T2[0];
  for (int i = 1; i < M; i++) {
    S[i] = S[i-1] + T2[i];
  }
  for (int i = 0; i <= M-P; i++) {
    dp[i][1] = 1LL*(i+1)*T2[i] - S[i];
  }
  for (int p = 2; p <= P; p++) {
    int head = 0, tail = 0;
    buf[head++] = p-2;
    for (int i = p-1; i <= M-P+p-1; i++) {
      while (head - tail > 1 && superior(buf[tail], buf[tail+1], p-1, i)) {
        tail++;
      }
      int j = buf[tail];
      dp[i][p] = dp[j][p-1] + int64_t(i-j)*T2[i] - S[i] + S[j];
      while (head - tail > 1 && concave(buf[head-2], buf[head-1], i, p-1)) {
        head--;
      }
      buf[head++] = i;
    }
  }
  cout << dp[M-1][P];

  return 0;
}


