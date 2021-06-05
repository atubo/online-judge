// https://codeforces.com/problemset/problem/44/J
// Triminoes

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int N, M;
char A[MAXN][MAXN];
int B[MAXN][MAXN];
int DX[4] = {0, -1, 0, 1};
int DY[4] = {1, 0, -1, 0};

bool inRange(int x, int y) {
  return 0 <= x && x < N && 0 <= y && y < M;
}

bool isEmpty(int x, int y) {
  return inRange(x, y) && A[x][y] != '.' && B[x][y] == 0;
}

bool dfs(int x, int y);

bool dfsH(int x, int y) {
  return dfs(x, y-2) && dfs(x, y+2) &&
         dfs(x-1, y-1) && dfs(x-1, y+1) &&
         dfs(x+1, y-1) && dfs(x+1, y+1) &&
         dfs(x-1, y) && dfs(x+1, y);
}

bool dfsV(int x, int y) {
  return dfs(x-2, y) &&
         dfs(x-1, y-1) && dfs(x-1, y+1) &&
         dfs(x+1, y-1) && dfs(x+1, y+1) &&
         dfs(x+2, y) &&
         dfs(x, y-1) && dfs(x, y+1);
}

void mark(int x, int y, int& mask) {
  if (inRange(x, y) && B[x][y] != 0) mask |= 1 << (B[x][y]-1);
}

int colorH(int x, int y) {
  int mask = 0;
  mark(x, y-2, mask);
  mark(x, y+2, mask);
  mark(x-1, y-1, mask);
  mark(x-1, y, mask);
  mark(x-1, y+1, mask);
  mark(x+1, y-1, mask);
  mark(x+1, y, mask);
  mark(x+1, y+1, mask);
  assert(mask < 16);
  for (int i = 0; i < 4; i++) {
    if (((mask >> i) & 1) == 0) return i+1;
  }
  assert(0);
  return -1;
}

int colorV(int x, int y) {
  int mask = 0;
  mark(x-2, y, mask);
  mark(x+2, y, mask);
  mark(x-1, y-1, mask);
  mark(x, y-1, mask);
  mark(x+1, y-1, mask);
  mark(x-1, y+1, mask);
  mark(x, y+1, mask);
  mark(x+1, y+1, mask);
  assert(mask < 16);
  for (int i = 0; i < 4; i++) {
    if (((mask >> i) & 1) == 0) return i+1;
  }
  assert(0);
  return -1;
}


bool dfs(int x, int y) {
  if (!isEmpty(x, y)) return true;
  if (A[x][y] == 'b') {
    if (isEmpty(x, y-1) && isEmpty(x, y+1)) {
      B[x][y-1] = B[x][y] = B[x][y+1] = colorH(x, y);
      if (dfsH(x, y)) {
        return true;
      }
      B[x][y-1] = B[x][y] = B[x][y+1] = 0;
      return false;
    }
    if (isEmpty(x-1, y) && isEmpty(x+1, y)) {
      B[x-1][y] = B[x][y] = B[x+1][y] = colorV(x, y);
      if (dfsV(x, y)) {
        return true;
      }
      B[x-1][y] = B[x][y] = B[x+1][y] = 0;
      return false;
    }
    return false;
  } else {
    int x2 = -1, y2 = -1;
    int nd = 0;
    for (int d = 0; d < 4; d++) {
      int xt = x + DX[d];
      int yt = y + DY[d];
      if (isEmpty(xt, yt)) {
        nd++;
        x2 = xt;
        y2 = yt;
      }
    }
    assert(nd <= 1);
    if (nd == 0) return false;
    if (x2 == x) {
      if (isEmpty(x2, y2-1) && isEmpty(x2, y2+1)) {
        B[x2][y2-1] = B[x2][y2] = B[x2][y2+1] = colorH(x2, y2);
        if (dfsH(x2, y2)) {
          return true;
        }
        B[x2][y2-1] = B[x2][y2] = B[x2][y2+1] = 0;
        return false;
      }
      return false;
    } else {
      if (isEmpty(x2-1, y2) && isEmpty(x2+1, y)) {
        B[x2-1][y2] = B[x2][y2] = B[x2+1][y2] = colorV(x2, y2);
        if (dfsV(x2, y2)) {
          return true;
        }
        B[x2-1][y2] = B[x2][y2] = B[x2+1][y2] = 0;
        return false;
      }
      return false;
    }
  }
}

bool putVert(int x, int y) {
  assert(A[x][y] == 'w' && !B[x][y]);
  if (!isEmpty(x, y) || !isEmpty(x+1, y) || !isEmpty(x+2, y)) return false;
  B[x][y] = B[x+1][y] = B[x+2][y] = colorV(x+1, y);
  if (dfsV(x+1, y)) {
    return true;
  }
  B[x][y] = B[x+1][y] = B[x+2][y] = 0;
  return false;
}

bool putHorz(int x, int y) {
  assert(A[x][y] == 'w' && !B[x][y]);
  if (!isEmpty(x, y) || !isEmpty(x, y+1) || !isEmpty(x, y+2)) return false;
  B[x][y] = B[x][y+1] = B[x][y+2] = colorH(x, y+1);
  if (dfsH(x, y+1)) {
    return true;
  }
  B[x][y] = B[x][y+1] = B[x][y+2] = 0;
  return false;
}

int main() {
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; i++) {
    scanf("%s", A[i]);
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (A[i][j] == 'w' && !B[i][j]) {
        bool ok = putVert(i, j);
        if (!ok) ok = putHorz(i, j);
        if (!ok) {
          printf("NO\n");
          return 0;
        }
      }
    }
  }

  printf("YES\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (B[i][j] == 0) printf(".");
      else printf("%c", 'a'-1+B[i][j]);
    }
    printf("\n");
  }

  return 0;
}
