// https://www.luogu.org/problemnew/show/P2566
// [SCOI2009]围豆豆

#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {0, 1, 0, -1};
const int DY[4] = {1, 0, -1, 0};
int N, M, D;
int V[10];
int A[10][10];
int dist[10][10][1024];
bool inq[10][10][1024];
int tot[1024];
const int inf = 0x3f3f3f3f;

struct Bean {
    int x, y, v;
} beans[10];

struct Node {
    int x, y, s;
};

void calcTot() {
    for (int s = 0; s < (1<<D); s++) {
        tot[s] = 0;
        int s1 = s;
        while (s1) {
            int d = __builtin_ctz(s1);
            tot[s] += beans[d].v;
            s1 -= (1<<d);
        }
    }
}

int cross(int x1, int y1, int x2, int y2, int s) {
    for (int i = 0; i < D; i++) {
        int bx = beans[i].x;
        int by = beans[i].y;
        if (((x1 <= bx && x2 > bx) || (x1 > bx && x2 <= bx)) && y1 > by) {
            s ^= (1<<i);
        }
    }
    return s;
}

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M;
}

int spfa(int sx, int sy) {
    memset(dist, 0x3f, sizeof(dist));
    queue<Node> q;
    q.push({sx, sy, 0});
    dist[sx][sy][0] = 0;
    inq[sx][sy][0] = true;
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        int x1 = node.x, y1 = node.y, s1 = node.s;
        inq[x1][y1][s1] = false;
        for (int dir = 0; dir < 4; dir++) {
            int x2 = x1 + DX[dir];
            int y2 = y1 + DY[dir];
            if (!inRange(x2, y2) || A[x2][y2] != 0) continue;
            int s2 = cross(x1, y1, x2, y2, s1);
            if (dist[x2][y2][s2] > dist[x1][y1][s1]+1) {
                dist[x2][y2][s2] = dist[x1][y1][s1]+1;
                if (!inq[x2][y2][s2]) {
                    q.push({x2, y2, s2});
                    inq[x2][y2][s2] = true;
                }
            }
        }
    }

    int ans = 0;
    for (int s = 0; s < (1<<D); s++) {
        if (dist[sx][sy][s] < inf) {
            ans = max(ans, tot[s]-dist[sx][sy][s]);
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &N, &M);
    scanf("%d", &D);
    for (int i = 0; i < D; i++) {
        scanf("%d", &V[i]);
    }
    for (int i = 0; i < N; i++) {
        char line[12];
        scanf("%s", line);
        for (int j = 0; j < M; j++) {
            if (line[j] == '#') A[i][j] = -1;
            else A[i][j] = line[j] - '0';
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] > 0) {
                int b = A[i][j]-1;
                beans[b] = {i, j, V[b]};
            }
        }
    }
    calcTot();
    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (A[i][j] == 0) {
                ans = max(ans, spfa(i, j));
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
