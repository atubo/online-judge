// https://daniu.luogu.org/problem/show?pid=2937
// [USACO09JAN]激光电话Laserphones

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;
using TI = tuple<int, int, int, int>;

const int MAXN = 110;
bool vis[MAXN][MAXN], block[MAXN][MAXN];
vector<PII> C;
int W, H;
const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

bool inRange(int r, int c) {
    return 0 <= r && r < H && 0 <= c && c < W;
}

int bfs() {
    queue<TI> q;
    vis[C[0].first][C[0].second] = true;
    for (int d = 0; d < 4; d++) {
        for (int s = 1; true; s++) {
            int r = C[0].first + DX[d] * s;
            int c = C[0].second + DY[d] * s;
            if (!inRange(r, c) || block[r][c]) break;
            q.push(make_tuple(r, c, d&1, 0));
            vis[r][c] = true;
        }
    }
    while (!q.empty()) {
        int r, c, pd, s;
        tie(r, c, pd, s) = q.front();
        q.pop();
        if (make_pair(r, c) == C[1]) return s;
        for (int d = 0; d < 4; d++) {
            if ((d&1) == pd) continue;
            for (int k = 1; true; k++) {
                int r2 = r + DX[d] * k;
                int c2 = c + DY[d] * k;
                if (!inRange(r2, c2) || block[r2][c2]) break;
                if (!vis[r2][c2]) {
                    q.push(make_tuple(r2, c2, d&1, s+1));
                    vis[r2][c2] = true;
                }
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d%d", &W, &H);
    string line;
    getline(cin, line);
    for (int i = 0; i < H; i++) {
        getline(cin, line);
        for (int j = 0; j < W; j++) {
            if (line[j] == '*') block[i][j] = true;
            if (line[j] == 'C') C.push_back(make_pair(i, j));
        }
    }

    printf("%d\n", bfs());
    return 0;
}
