// https://www.luogu.org/problemnew/show/P2489
// [SDOI2011]迷宫探险

#include <bits/stdc++.h>
using namespace std;

const int DX[4] = {0, 1, 0, -1};
const int DY[4] = {1, 0, -1, 0};
const int MAXN = 30;
int M, N, K, H;
char MAZE[MAXN][MAXN];
bool vis[MAXN][MAXN], added[MAXN][MAXN];
double dp[MAXN][MAXN][6][1024];
int P[32];

struct Point {
    int x, y, id, type;
};

struct Coord {
    int x, y;
};

void init() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int h = 0; h < 6; h++) {
                for (int s = 0; s < 1024; s++) {
                    dp[i][j][h][s] = -1;
                }
            }
        }
    }
}

int decode(int s, int k) {
    return (s >> (2*k)) & 3;
}

bool inRange(int x, int y) {
    return 0 <= x && x < M && 0 <= y && y < N;
}

vector<Point> bfs(int x, int y, int s, bool &found) {
    memset(vis, 0, sizeof(vis));
    memset(added, 0, sizeof(added));
    vector<Point> ret;
    queue<Coord> q;
    q.push({x, y});
    vis[x][y] = true;
    added[x][y] = true;
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        x = curr.x; y = curr.y;
        if (MAZE[x][y] == '@') {
            found = true;
            return ret;
        }
        for (int d = 0; d < 4; d++) {
            int x2 = x + DX[d];
            int y2 = y + DY[d];
            char c2 = MAZE[x2][y2];
            if (!inRange(x2, y2) || c2 == '#') continue;
            if ('A' <= c2 && c2 <= 'E') {
                int k = c2 - 'A';
                int t = decode(s, k);
                if (t > 0) {
                    if (!added[x2][y2]) {
                        added[x2][y2] = true;
                        ret.push_back({x2, y2, k, t});
                    }
                    continue;
                }
            }
            if (!vis[x2][y2]) {
                vis[x2][y2] = true;
                q.push({x2, y2});
            }
        }
    }
    return ret;
}

double calcProb(int s, int id) {
    assert(decode(s, id) == 3);
    int maskzero = 0, maskone = 0;
    for (int k = 0; k < K; k++) {
        int t = decode(s, k);
        if (t == 0) maskzero |= (1<<k);
        if (t == 1) maskone |=  (1<<k);
    }
    int tt = 0, t0 = 0;
    for (int k = 0; k < (1<<K); k++) {
        if ((k & maskone) != maskone) continue;
        if (((~k) & maskzero) != maskzero) continue;
        tt += P[k];
        if (((k >> id) & 1) == 0) {
            t0 += P[k];
        }
    }
    return 1.0*t0 / tt;
}

int calcState(int s, int id, int t) {
    return (s & (~(0x3<<(2*id)))) | (t<<(2*id));
}

double dfs(int x0, int y0, int h, int s) {
    if (dp[x0][y0][h][s] >= 0) return dp[x0][y0][h][s];
    double &ret = dp[x0][y0][h][s];
    ret = 0;
    if (h == 0) return ret;
    bool found = false;
    auto nxt = bfs(x0, y0, s, found);
    if (found) {
        ret = 1;
    }
    else {
        for (const auto &p: nxt) {
            if (p.type == 1) {
                ret = max(ret, dfs(p.x, p.y, h-1, s));
            } else {
                assert(p.type == 3);
                double p0 = calcProb(s, p.id);
                int s0 = calcState(s, p.id, 0);
                double p1 = 1 - p0;
                int s1 = calcState(s, p.id, 1);
                double prob = p0 * dfs(p.x, p.y, h, s0) +
                    p1 * dfs(p.x, p.y, h-1, s1);
                ret = max(ret, prob);
            }
        }
    }
    return ret;
}

int main() {
    scanf("%d%d%d%d", &M, &N, &K, &H);
    init();
    int x0 = -1, y0 = -1;
    for (int i = 0; i < M; i++) {
        scanf("%s", MAZE[i]);
        for (int j = 0; j < N; j++) {
            if (MAZE[i][j] == '$') {
                x0 = i;
                y0 = j;
            }
        }
    }
    for (int i = 0; i < (1<<K); i++) {
        scanf("%d", &P[i]);
    }
    double ans = dfs(x0, y0, H, (1<<(2*K))-1);
    printf("%.3f\n", ans);
    return 0;
}
