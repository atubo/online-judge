// https://www.luogu.org/problem/show?pid=1331
// 海战

#include <bits/stdc++.h>
using namespace std;

using PII = pair<int, int>;

const int MAXN = 1010;
bool sea[MAXN][MAXN], vis[MAXN][MAXN];
int R, C;

int DX[4] = {1, 0, -1, 0};
int DY[4] = {0, 1, 0, -1};

bool inRange(int i, int j) {
    return 0 <= i && i < R && 0 <= j && j < C;
}

bool bfs(int i, int j) {
    queue<PII> que;
    que.push(make_pair(i, j));
    vis[i][j] = true;
    int area = 0, maxi = -1, mini = 2000, maxj = -1, minj = 2000;
    while (!que.empty()) {
        tie(i, j) = que.front();
        que.pop();
        area++;
        maxi = max(maxi, i);
        mini = min(mini, i);
        maxj = max(maxj, j);
        minj = min(minj, j);
        for (int d = 0; d < 4; d++) {
            int p = i + DX[d];
            int q = j + DY[d];
            if (inRange(p, q) && !vis[p][q] && sea[p][q]) {
                que.push(make_pair(p, q));
                vis[p][q] = true;
            }
        }
    }

    return area == (maxi - mini + 1) * (maxj - minj + 1);
}

int main() {
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < C; j++) {
            sea[i][j] = (s[j] == '#');
        }
    }

    int ret = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (sea[i][j] && !vis[i][j]) {
                if (!bfs(i, j)) {
                    ret = -1;
                    break;
                } else {
                    ret++;
                }
            }
        }
        if (ret == -1) break;
    }

    if (ret == -1) {
        cout << "Bad placement." << endl;
    } else {
        cout << "There are " << ret << " ships." << endl;
    }
    return 0;
}
