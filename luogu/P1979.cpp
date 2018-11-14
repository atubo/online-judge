// https://www.luogu.org/problemnew/show/P1979
// 华容道

#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

int N, M, Q;
int B[32][32];
int EX, EY, SX, SY, TX, TY;
int dist[905*4], inq[905*4];
bool vis[32][32];
int D[32][32][4][4];

void init() {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            for (int d1 = 0; d1 < 4; d1++) {
                for (int d2 = 0; d2 < 4; d2++) {
                    D[i][j][d1][d2] = -2;
                }
            }
        }
    }
}

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < M;
}

struct Data {
    int x, y, d;
    int id() const {return (x*M + y)*4 + d;}
    void print() const {
        printf("%d %d %d %d\n", x, y, d, dist[id()]);
    }
};

int bfs(int bx, int by, int ex, int ey, int gx, int gy) {
    memset(vis, 0, sizeof(vis));
    queue<Data> q;
    q.push({bx, by, 0});
    while (!q.empty()) {
        auto data = q.front();
        int x = data.x, y = data.y, d = data.d;
        q.pop();
        if (x == ex && y == ey) return d;
        for (int dir = 0; dir < 4; dir++) {
            int x2 = x + DX[dir];
            int y2 = y + DY[dir];
            if (inRange(x2, y2) && !(x2 == gx && y2 == gy) &&
                B[x2][y2] && !vis[x2][y2]) {
                vis[x2][y2] = true;
                q.push({x2, y2, d+1});
            }
        }
    }
    return -1;
}


int solve() {
    if (SX == TX && SY == TY) return 0;
    memset(dist, -1, sizeof(dist));
    memset(inq, 0, sizeof(inq));
    queue<Data> q;
    for (int d = 0; d < 4; d++) {
        int x = SX + DX[d];
        int y = SY + DY[d];
        int ds = bfs(EX, EY, x, y, SX, SY);
        if (ds != -1) {
            Data data = {x, y, d^2};
            q.push(data);
            inq[data.id()]++;
            dist[data.id()] = ds + 1;
        }
    }
    while (!q.empty()) {
        auto data = q.front();
        //data.print();
        q.pop();
        inq[data.id()]--;
        int x0 = data.x, y0 = data.y, d1 = data.d;
        //if (x0 == TX && y0 == TY) return dist[data.id()];
        int x1 = x0 + DX[d1], y1 = y0 + DY[d1];
        for (int d = 0; d < 4; d++) {
            if (d == d1) continue;
            int x2 = x0 + DX[d], y2 = y0 + DY[d];
            if (!inRange(x2, y2) ||!B[x2][y2]) continue;
            int &ds = D[x0][y0][d1][d];
            if (ds == -2) ds = bfs(x1, y1, x2, y2, x0, y0);
            //int ds = bfs(x1, y1, x2, y2, x0, y0);
            if (ds != -1) {
                Data nd = {x2, y2, d^2};
                if (dist[nd.id()] == -1 ||
                    dist[nd.id()] > dist[data.id()] + ds + 1) {
                    dist[nd.id()] = dist[data.id()] + ds + 1;
                    if (!inq[nd.id()]) {
                        q.push(nd);
                        inq[nd.id()]++;
                    }
                }
            }
        }
    }
    int ans = INT_MAX;
    for (int d = 0; d < 4; d++) {
        Data data = {TX, TY, d};
        if (dist[data.id()] != -1) ans = min(ans, dist[data.id()]);
    }
    return ans == INT_MAX ? -1 : ans;
}


int main() {
    init();
    scanf("%d%d%d", &N, &M, &Q);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    for (int i = 0; i < Q; i++) {
        scanf("%d%d%d%d%d%d", &EX, &EY, &SX, &SY, &TX, &TY);
        EX--; EY--; SX--; SY--; TX--; TY--;
        printf("%d\n", solve());
    }

    return 0;
}
