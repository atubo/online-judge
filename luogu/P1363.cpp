// https://www.luogu.org/problem/show?pid=1363
// 幻想迷宫

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;
using TI = tuple<int, int, int, int>;

const int MAXN = 1510;
bool maze[MAXN][MAXN], vis[MAXN][MAXN];
PII last[MAXN][MAXN];
int N, M;

const int DX[4] = {1, 0, -1, 0};
const int DY[4] = {0, 1, 0, -1};

bool bfs(int p, int q) {
    memset(vis, 0, sizeof(vis));
    queue<TI> que;
    que.push(make_tuple(p, q, 0, 0));
    vis[p][q] = true;
    last[p][q] = make_pair(0, 0);
    while (!que.empty()) {
        int x, y, r, c;
        tie(x, y, r, c) = que.front();
        que.pop();
        for (int d = 0; d < 4; d++) {
            int u = x + DX[d];
            int v = y + DY[d];
            int r2 = r, c2 = c;
            if (u >= N) {
                u -= N;
                r2++;
            }
            if (u < 0) {
                u += N;
                r2--;
            }
            if (v >= M) {
                v -= M;
                c2++;
            }
            if (v < 0) {
                v += M;
                c2--;
            }
            if (maze[u][v]) {
                if (vis[u][v] && last[u][v] != make_pair(r2, c2)) return true;
                if (!vis[u][v]) {
                    que.push(make_tuple(u, v, r2, c2));
                    vis[u][v] = true;
                    last[u][v] = make_pair(r2, c2);
                }
            }
        }
    }

    return false;
}

int main() {
    while (scanf("%d%d", &N, &M) == 2) {
        string line;
        getline(cin, line);
        int p, q;
        for (int i = 0; i < N; i++) {
            getline(cin, line);
            for (int j = 0; j < M; j++) {
                switch(line[j]) {
                    case 'S':
                        p = i;
                        q = j;
                    case '.':
                        maze[i][j] = true;
                        break;
                    default:
                        maze[i][j] = false;
                        break;
                }
            }
        }
        bool ok = bfs(p, q);
        printf(ok ? "Yes\n" : "No\n");
    }
    return 0;
}
