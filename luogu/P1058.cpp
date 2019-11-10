// https://www.luogu.org/problem/P1058
// 立体图

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1024;
char P[MAXN][MAXN];

void printLine(int x1, int x2, int y, char c) {
  for (int x = x1; x <= x2; x++) {
    P[x][y] = c;
  }
}

class Plotter {
 public:
  Plotter(int x, int y): x0(x), y0(y) {}
  char& operator()(int dx, int dy) const {
    return P[x0+dx][y0+dy];
  }
 private:
  int x0, y0;
};


void plot(int x0, int y0) {
  Plotter p(x0, y0);
  p(0, 0) = p(4, 0) = '+';
  for (int x = 1; x <= 3; x++) p(x, 0) = '-';

  p(0, 1) = p(4, 1) = '|';
  for (int x = 1; x <= 3; x++) p(x, 1) = ' ';
  p(5, 1) = '/';

  p(0, 2) = p(4, 2) = '|';
  for (int x = 1; x <= 3; x++) p(x, 2) = ' ';
  p(5, 2) = ' '; p(6, 2) = '+';

  p(0, 3) = p(4, 3) = '+';
  for (int x = 1; x <= 3; x++) p(x, 3) = '-';
  p(5, 3) = ' '; p(6, 3) = '|';

  p(1, 4) = p(5, 4) = '/';
  for (int x = 2; x <= 4; x++) p(x, 4) = ' ';
  p(6, 4) = '|';

  p(2, 5) = p(6, 5) = '+';
  for (int x = 3; x <= 5; x++) p(x, 5) = '-';
}

int H[52][52];
int M, N;

int main() {
  scanf("%d%d", &M, &N);
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &H[M-1-i][j]);
    }
  }
  memset(P, '.', sizeof(P));
  int maxx = 0, maxy = 0;
  for (int i = M-1; i >= 0; i--) {
    for (int j = 0; j < N; j++) {
      for (int h = 0; h < H[i][j]; h++) {
        int x0 = 4*j + 2*i;
        int y0 = 2*i + 3*h;
        plot(x0, y0);
        maxx = max(maxx, x0+6);
        maxy = max(maxy, y0+5);
      }
    }
  }

  for (int y = maxy; y >= 0; y--) {
    for (int x = 0; x <= maxx; x++) {
      printf("%c", P[x][y]);
    }
    printf("\n");
  }

  return 0;
}
