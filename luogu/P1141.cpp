// https://www.luogu.org/problemnew/show/P1141
// 01迷宫

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int maze[MAXN][MAXN], visited[MAXN][MAXN];
int N, M;

struct Item {
    int x, y;
};

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

void bfs(int u, int v) {
    int u0 = u, v0 = v;
    queue<Item> q;
    q.push({u, v});
    visited[u][v] = -1;
    int maxd = 0;
    while (!q.empty()) {
        Item item = q.front();
        q.pop();
        u = item.x; v = item.y;
        maxd++;
        for (int dir = 0; dir < 4; dir++) {
            int x = u + DX[dir];
            int y = v + DY[dir];
            if (inRange(x, y) && !visited[x][y] && (maze[x][y]^maze[u][v])) {
                q.push({x, y});
                visited[x][y] = -1;
            }
        }
    }

    u = u0; v = v0;
    q.push({u, v});
    visited[u][v] = maxd;
    while (!q.empty()) {
        Item item = q.front();
        q.pop();
        u = item.x; v = item.y;
        for (int dir = 0; dir < 4; dir++) {
            int x = u + DX[dir];
            int y = v + DY[dir];
            if (inRange(x, y) && visited[x][y] == -1 && (maze[x][y]^maze[u][v])) {
                q.push({x, y});
                visited[x][y] = maxd;
            }
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    char line[MAXN];
    for (int i = 0; i < N; i++) {
        scanf("%s", line);
        for (int j = 0; j < N; j++) {
            maze[i][j] = line[j] - '0';
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j]) bfs(i, j);
        }
    }

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", visited[u-1][v-1]);
    }
    return 0;
}
