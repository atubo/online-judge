// https://codeforces.com/problemset/problem/18/E
// E. Flag 2

#include <bits/stdc++.h>
using namespace std;

struct Data {
  int c, x, y;
  bool operator < (const Data& other) const {
    if (c != other.c) return c < other.c;
    if (x != other.x) return x < other.x;
    return y < other.y;
  }
};

const int INF = 0x3F3F3F3F;
int N, M;
int A[510][510];
char B[510][510];
int C[26][2][510];
int dp[26][26][510];
int P[26][26][510];
Data D1[26][26], D2[26][26], D3[26][26], D4[26][26];

void build(int r) {
  D1[0][0] = Data{dp[0][0][r], 0, 0};
  for (int j = 1; j < 26; j++) {
    D1[0][j] = min(D1[0][j-1], Data{dp[0][j][r], 0, j});
  }
  for (int i = 1; i < 26; i++) {
    D1[i][0] = min(D1[i-1][0], Data{dp[i][0][r], i, 0});
  }
  for (int i = 1; i < 26; i++) {
    for (int j = 1; j < 26; j++) {
      D1[i][j] = min(min(D1[i-1][j], D1[i][j-1]), Data{dp[i][j][r], i, j});
    }
  }

  D2[0][25] = Data{dp[0][25][r], 0, 25};
  for (int j = 24; j >= 0; j--) {
    D2[0][j] = min(D2[0][j+1], Data{dp[0][j][r], 0, j});
  }
  for (int i = 1; i < 26; i++) {
    D2[i][25] = min(D2[i-1][25], Data{dp[i][25][r], i, 25});
  }
  for (int i = 1; i < 26; i++) {
    for (int j = 24; j >= 0; j--) {
      D2[i][j] = min(min(D2[i-1][j], D2[i][j+1]), Data{dp[i][j][r], i, j});
    }
  }

  D3[25][0] = Data{dp[25][0][r], 25, 0};
  for (int j = 1; j < 26; j++) {
    D3[25][j] = min(D3[25][j-1], Data{dp[25][j][r], 25, j});
  }
  for (int i = 24; i >= 0; i--) {
    D3[i][0] = min(D3[i+1][0], Data{dp[i][0][r], i, 0});
  }
  for (int i = 24; i >= 0; i--) {
    for (int j = 1; j < 26; j++) {
      D3[i][j] = min(min(D3[i+1][j], D3[i][j-1]), Data{dp[i][j][r], i, j});
    }
  }

  D4[25][25] = Data{dp[25][25][r], 25, 25};
  for (int j = 24; j >= 0; j--) {
    D4[25][j] = min(D4[25][j+1], Data{dp[25][j][r], 25, j});
  }
  for (int i = 24; i >= 0; i--) {
    D4[i][25] = min(D4[i+1][25], Data{dp[i][25][r], i, 25});
  }
  for (int i = 24; i >= 0; i--) {
    for (int j = 24; j >= 0; j--) {
      D4[i][j] = min(min(D4[i+1][j], D4[i][j+1]), Data{dp[i][j][r], i, j});
    }
  }
}

int main() {
  scanf("%d%d", &N, &M);
  memset(dp, 0x3F, sizeof(dp));
  char s[510];
  for (int i = 0; i < N; i++) {
    scanf("%s", s);
    for (int j = 0; j < M; j++) {
      A[i][j] = s[j] - 'a';
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int c = A[i][j];
      int p = (j & 1);
      C[c][p][i]++;
    }
  }

  for (int a = 0; a < 26; a++) {
    for (int b = 0; b < 26; b++) {
      if (a == b) continue;
      dp[a][b][0] = M - C[a][0][0] - C[b][1][0];
      P[a][b][0] = -1;
    }
  }

  for (int i = 1; i < N; i++) {
    build(i-1);
    for (int a = 0; a < 26; a++) {
      for (int b = 0; b < 26; b++) {
        if (a == b) continue;
        Data t{INF, -1, -1};
        if (a > 0 && b > 0) t = min(t, D1[a-1][b-1]);
        if (a > 0 && b < 25) t = min(t, D2[a-1][b+1]);
        if (a < 25 && b > 0) t = min(t, D3[a+1][b-1]);
        if (a < 25 && b < 25) t = min(t, D4[a+1][b+1]);
        dp[a][b][i] = M - C[a][0][i] - C[b][1][i] + t.c;
        P[a][b][i] = t.x * 26 + t.y;
      }
    }
  }

  int ans = INF;
  int x = -1, y = -1;
  for (int a = 0; a < 26; a++) {
    for (int b = 0; b < 26; b++) {
      if (a == b) continue;
      if (dp[a][b][N-1] < ans) {
        ans = dp[a][b][N-1];
        x = a;
        y = b;
      }
    }
  }
  printf("%d\n", ans);
  for (int j = 0; j < M; j++) {
    B[N-1][j] = (j & 1 ? y + 'a' : x + 'a');
  }
  for (int i = N-2; i >= 0; i--) {
    int p = P[x][y][i+1];
    y = p % 26;
    x = p / 26;
    for (int j = 0; j < M; j++) {
      B[i][j] = (j & 1 ? y + 'a' : x + 'a');
    }
  }
  for (int i = 0; i < N; i++) {
    printf("%s\n", B[i]);
  }

  return 0;
}
