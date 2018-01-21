// https://www.luogu.org/problemnew/show/P1126
// 机器人搬重物

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 53;
int N, M;
int SRCX, SRCY, DSTX, DSTY, STARTDIR;

bool vis[1<<14];
bool room[MAXN][MAXN];

const int DX[4] = {1, 0, -1, 0};
const int DY[4] = {0, 1, 0, -1};

int getdir(char c) {
    if (c == 'S') return 0;
    if (c == 'E') return 1;
    if (c == 'N') return 2;
    return 3;
}

int encode(int dir, int x, int y) {
    int ret = (dir << 12) | (x << 6) | y;
    return ret;
}

void decode(int code, int &dir, int &x, int &y) {
    dir = (code >> 12);
    const int MASK = (1<<6) - 1;
    x = (code >> 6) & MASK;
    y = code & MASK;
}

struct Item {
    int c, d;
};

queue<Item> q;

bool inRange(int x, int y) {
    return 0 < x && x < N && 0 < y && y < M;
}

void add(int dir, int x, int y, int d) {
    int code = encode(dir, x, y);
    if (!vis[code]) {
        q.push({code, d});
        vis[code] = true;
    }
}

void creep(int dir, int x, int y, int d) {
    int nx = x + DX[dir];
    int ny = y + DY[dir];
    if (inRange(nx, ny) && !room[nx][ny]) {
        add(dir, nx, ny, d+1);
    }
}

void walk(int dir, int x, int y, int d) {
    int x1 = x + DX[dir], x2 = x1 + DX[dir];
    int y1 = y + DY[dir], y2 = y1 + DY[dir];
    if (inRange(x2, y2) && !room[x1][y1] && !room[x2][y2]) {
        add(dir, x2, y2, d+1);
    }
}

void run(int dir, int x, int y, int d) {
    int x1 = x + DX[dir], x2 = x1 + DX[dir], x3 = x2 + DX[dir];
    int y1 = y + DY[dir], y2 = y1 + DY[dir], y3 = y2 + DY[dir];
    if (inRange(x3, y3) && !room[x1][y1] && !room[x2][y2] &&
        !room[x3][y3]) {
        add(dir, x3, y3, d+1);
    }
}

void left(int dir, int x, int y, int d) {
    dir = (dir + 1) % 4;
    add(dir, x, y, d+1);
}

void right(int dir, int x, int y, int d) {
    dir = (dir + 3) % 4;
    add(dir, x, y, d+1);
}

int bfs() {
    int code = encode(STARTDIR, SRCX, SRCY);
    q.push({code, 0});
    vis[code] = true;
    while (!q.empty()) {
        Item item = q.front();
        q.pop();
        code = item.c;
        int d = item.d;
        int dir, x, y;
        decode(code, dir, x, y);
        //printf("d=%d %d %d %d\n", d, dir, x, y);
        if (x == DSTX && y == DSTY) return d;

        creep(dir, x, y, d);
        walk(dir, x, y, d);
        run(dir, x, y, d);
        left(dir, x, y, d);
        right(dir, x, y, d);
    }
    return -1;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int c;
            scanf("%d", &c);
            if (c) {
                room[i][j] = room[i+1][j] =
                    room[i][j+1] = room[i+1][j+1] = true;
            }
        }
    }

    scanf("%d%d%d%d", &SRCX, &SRCY, &DSTX, &DSTY);
    char s[10];
    scanf("%s", s);
    STARTDIR = getdir(s[0]);
    printf("%d", bfs());
    return 0;
}
