// https://www.luogu.org/problemnew/show/1443
// 马的遍历

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 410;
int steps[MAXN][MAXN];
int N, M;

struct Item {
    int x, y;
};

const int DX[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int DY[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M;
}

void bfs(int x, int y) {
    deque<Item> dq;
    dq.push_back({x, y});
    steps[x][y] = 0;
    while (!dq.empty()) {
        Item item = dq.front();
        dq.pop_front();
        int x0 = item.x, y0 = item.y;
        for (int d = 0; d < 8; d++) {
            int x1 = x0 + DX[d];
            int y1 = y0 + DY[d];
            if (inRange(x1, y1) && steps[x1][y1] == -1) {
                steps[x1][y1] = steps[x0][y0] + 1;
                dq.push_back({x1, y1});
            }
        }
    }
}


int main() {
    memset(steps, 0xff, sizeof(steps));
    int x, y;
    scanf("%d%d%d%d", &N, &M, &x, &y);
    x--; y--;
    bfs(x, y);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%-5d", steps[i][j]);
        }
        printf("\n");
    }
    return 0;
}
