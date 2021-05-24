// https://codeforces.com/problemset/problem/28/C
// Bath Queue

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 52;
double C[MAXN][MAXN], P[MAXN][MAXN][MAXN];
double F[MAXN][MAXN][MAXN], G[MAXN][MAXN][MAXN];
double fac[MAXN];
int A[MAXN];

int N, M;

void build() {
  C[0][0] = 1;
  for (int n = 1; n <= N; n++) {
    C[n][0] = 1;
    for (int k = 1; k <= n; k++) {
      C[n][k] = C[n-1][k-1] + C[n-1][k];
    }
  }
}

double pwr(double x, int n) {
  double ret = 1;
  for (int i = 1; i <= n; i++) {
    ret *= x;
  }
  return ret;
}

int main() {
  scanf("%d%d", &N, &M);
  build();
  for (int i = 0; i < M; i++) {
    scanf("%d", &A[i]);
  }
  for (int n = 0; n <= N; n++) {
    for (int k = 0; k <= N; k++) {
      if (A[0]*(k-1) < n && n <= A[0]*k) F[0][n][k] = 1;
      else F[0][n][k] = 0;
    }
  }
  for (int n = 0; n <= N; n++) {
    for (int k = 0; k <= N; k++) {
      if (n <= A[0]*k) G[0][n][k] = 1;
      else G[0][n][k] = 0;
    }
  }
  for (int i = 1; i < M; i++) {
    for (int n = 0; n <= N; n++) {
      for (int k = 0; k <= N; k++) {
        for (int np = 0; np <= n; np++) {
          double f = C[n][np] * pwr(1.0/(i+1), np) * pwr(1-1.0/(i+1), n-np);
          if (np <= A[i]*(k-1)) F[i][n][k] += f * F[i-1][n-np][k];
          else if (np <= A[i]*k) F[i][n][k] += f * G[i-1][n-np][k];
          else break;
        }
      }
    }
    for (int n = 0; n <= N; n++) {
      G[i][n][0] = F[i][n][0];
      for (int k = 1; k <= N; k++) {
        G[i][n][k] = G[i][n][k-1] + F[i][n][k];
      }
    }
  }

  double ret = 0;
  for (int k = 1; k <= N; k++) {
    ret += F[M-1][N][k] * k;
  }
  printf("%.10f\n", ret);
  return 0;
}
