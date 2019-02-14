// https://www.luogu.org/problemnew/show/P1300
// 城市街道交通费系统

#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {-1, 0, 1, 0};
const int DY[4] = {0, -1, 0, 1};

const int MAXN = 32;
int D[MAXN][MAXN][4];
bool inq[MAXN][MAXN][4];
int A[MAXN][MAXN];
int H, W;
int X0, Y0, X1, Y1, D0;

struct Data {
    int x, y, dir, dist;
};

bool inRange(int x, int y) {
    return 0 <= x && x < H && 0 <= y && y < W;
}

bool cannotGo(int x, int y, int dir) {
    int x2 = x + DX[dir];
    int y2 = y + DY[dir];
    return !(inRange(x2, y2) && A[x2][y2]);
}

int spfa() {
    queue<Data> q;
    q.push({X0, Y0, D0, 0});
    inq[X0][Y0][D0] = true;
    while (!q.empty()) {
        Data curr = q.front();
        q.pop();
        int x0 = curr.x, y0 = curr.y, dir0 = curr.dir, dist0 = curr.dist;
        inq[x0][y0][dir0] = false;
        int dir1 = dir0;
        int x1 = x0 + DX[dir1];
        int y1 = y0 + DY[dir1];
        if (inRange(x1, y1) && A[x1][y1]) {
            int dist1 = dist0;
            if (D[x1][y1][dir1] > dist1) {
                D[x1][y1][dir1] = dist1;
                if (!inq[x1][y1][dir1]) {
                    q.push({x1, y1, dir1, dist1});
                    inq[x1][y1][dir1] = true;
                }
            }
        }
        dir1 = (dir0 + 1) % 4;
        x1 = x0 + DX[dir1];
        y1 = y0 + DY[dir1];
        if (inRange(x1, y1) && A[x1][y1]) {
            int dist1 = dist0 + 1;
            if (D[x1][y1][dir1] > dist1) {
                D[x1][y1][dir1] = dist1;
                if (!inq[x1][y1][dir1]) {
                    q.push({x1, y1, dir1, dist1});
                    inq[x1][y1][dir1] = true;
                }
            }
        }

        dir1 = (dir0 + 3) % 4;
        x1 = x0 + DX[dir1];
        y1 = y0 + DY[dir1];
        if (inRange(x1, y1) && A[x1][y1]) {
            int dist1 = dist0 + 5;
            if (D[x1][y1][dir1] > dist1) {
                D[x1][y1][dir1] = dist1;
                if (!inq[x1][y1][dir1]) {
                    q.push({x1, y1, dir1, dist1});
                    inq[x1][y1][dir1] = true;
                }
            }
        }

        if (cannotGo(x0, y0, dir0) && cannotGo(x0, y0, (dir0+1)%4)
            && cannotGo(x0, y0, (dir0+3)%4)) {
            dir1 = (dir0 + 2) % 4;
            x1 = x0 + DX[dir1];
            y1 = y0 + DY[dir1];
            if (inRange(x1, y1) && A[x1][y1]) {
                int dist1 = dist0 + 10;
                if (D[x1][y1][dir1] > dist1) {
                    D[x1][y1][dir1] = dist1;
                    if (!inq[x1][y1][dir1]) {
                        q.push({x1, y1, dir1, dist1});
                        inq[x1][y1][dir1] = true;
                    }
                }
            }
        }
    }

    int ans = INT_MAX;
    for (int d = 0; d < 4; d++) {
        ans = min(ans, D[X1][Y1][d]);
    }
    return ans;
}

int main() {

    memset(D, 0x3F, sizeof(D));
    scanf("%d%d", &H, &W);
    for (int i = 0; i < H; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < W; j++) {
            A[i][j] = (s[j] != '.');
            if (s[j] == 'E' || s[j] == 'W' || s[j] == 'N' || s[j] == 'S') {
                X0 = i;
                Y0 = j;
                if (s[j] == 'N') D0 = 0;
                else if (s[j] == 'W') D0 = 1;
                else if (s[j] == 'S') D0 = 2;
                else D0 = 3;
            } else if (s[j] == 'F') {
                X1 = i;
                Y1 = j;
            }
        }
    }
    int ans = spfa();
    printf("%d\n", ans);
    return 0;
}
