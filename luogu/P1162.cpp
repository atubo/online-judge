// https://www.luogu.org/problemnew/show/1162
// 填涂颜色

#include <bits/stdc++.h>
using namespace std;

int N;
int M[32][32];

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

bool inRange(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

void bfs(int i, int j) {
    using PII = pair<int, int>;
    queue<PII> q;
    q.push(make_pair(i, j));
    M[i][j] = -2;
    while (!q.empty()) {
        i = q.front().first; j = q.front().second;
        q.pop();
        for (int d = 0; d < 4; d++) {
            int u = i + DX[d];
            int v = j + DY[d];
            if (inRange(u, v) && !M[u][v]) {
                q.push(make_pair(u, v));
                M[u][v] = -2;
            }
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &M[i][j]);
        }
    }
    for (int i = 0; i < N; i++) {
        if (!M[0][i]) bfs(0, i);
        if (!M[i][0]) bfs(i, 0);
        if (!M[N-1][i]) bfs(N-1, i);
        if (!M[i][N-1]) bfs(i, N-1);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (M[i][j] != 1) M[i][j] += 2;
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
    return 0;
}
