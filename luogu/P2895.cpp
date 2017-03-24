// https://www.luogu.org/problem/show?pid=2895
// [USACO08FEB]流星雨Meteor Shower

#include <bits/stdc++.h>
using namespace std;
using TI = tuple<int, int, int>;

const int MAXN = 310;
int hit[MAXN][MAXN];
bool visited[MAXN][MAXN];
int M;
int DX[4] = {0, 1, 0, -1};
int DY[4] = {1, 0, -1, 0};

bool inRange(int x, int y) {
    return x >= 0 && y >= 0;
}

void mark(int x, int y, int t) {
    if (inRange(x, y)) {
        if (hit[x][y] == -1 || hit[x][y] > t) hit[x][y] = t;
    }
}

int bfs() {
    queue<TI> q;
    q.push(make_tuple(0, 0, 0));
    visited[0][0] = true;
    while (!q.empty()) {
        int x, y, t;
        tie(x, y, t) = q.front();
        q.pop();
        if (!(x == 0 && y == 0) && hit[x][y] == -1) return t;
        t++;
        for (int d = 0; d < 4; d++) {
            int nx = x + DX[d];
            int ny = y + DY[d];
            if (inRange(nx, ny) && !visited[nx][ny] &&
                (hit[nx][ny] == -1 || hit[nx][ny] > t)) {
                q.push(make_tuple(nx, ny, t));
                visited[nx][ny] = true;
            }
        }
    }
    return -1;
}

int main() {
    memset(hit, -1, sizeof(hit));
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int x, y, t;
        scanf("%d %d %d", &x, &y, &t);
        mark(x, y, t);
        for (int d = 0; d < 4; d++) {
            mark(x + DX[d], y + DY[d], t);
        }
    }

    printf("%d\n", bfs());
    return 0;
}
