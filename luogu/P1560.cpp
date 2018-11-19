// https://www.luogu.org/problemnew/show/P1560
// [USACO5.2]蜗牛的旅行Snail Trails

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 122;
const int DX[4] = {1, 0, -1, 0};
const int DY[4] = {0, 1, 0, -1};
int N, M;
int B[MAXN][MAXN];
int steps;
int ans;

bool inRange(int x, int  y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

bool proceed(int x, int y, int d, int &x2, int &y2) {
    x2 = x;
    y2 = y;
    while (inRange(x2+DX[d], y2+DY[d]) && B[x2+DX[d]][y2+DY[d]] == 0) {
        x2 += DX[d];
        y2 += DY[d];
        B[x2][y2] = 1;
        steps++;
        ans = max(ans, steps);
    }
    return !(inRange(x2+DX[d], y2+DY[d]) && B[x2+DX[d]][y2+DY[d]] == 1);
}

void backtrack(int x, int y, int d, int x2, int y2) {
    while (x2 != x || y2 != y) {
        B[x2][y2] = 0;
        steps--;
        x2 -= DX[d];
        y2 -= DY[d];
    }
}

void dfs(int x, int y, int pd) {
    vector<int> next;
    if (pd == -1) next = {0, 1};
    else next = {(pd+1) % 4, (pd+3) % 4};

    for (int d: next) {
        int x2 = x + DX[d];
        int y2 = y + DY[d];
        if (inRange(x2, y2) && !B[x2][y2]) {
            if (proceed(x, y, d, x2, y2)) {
                dfs(x2, y2, d);
            }
            backtrack(x, y, d, x2, y2);
        }
    }
}


int main() {
    scanf("%d%d", &N, &M);
    unsigned char line[10];
    for (int i = 0; i < M; i++) {
        cin >> line;
        int x = line[0] - 'A';
        int y = stoi((char*)line+1) - 1;
        B[x][y] = 2;
    }

    B[0][0] = 1;
    dfs(0, 0, -1);
    printf("%d\n", ans+1);

    return 0;
}
