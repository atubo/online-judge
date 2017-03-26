// https://www.luogu.org/problem/show?pid=1767
// 家族_NOI导刊2010普及（10）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110, MAXM = 210;
char A[MAXN][MAXM];
bool vis[MAXN][MAXM];
int N, M;

int DX[4] = {0, -1, 0, 1};
int DY[4] = {1, 0, -1, 0};

bool inRange(int i, int j) {
    return 0 <= i && i < N && 0 <= j && j < M;
}

void dfs(int i, int j) {
    vis[i][j] = true;
    for (int d = 0; d < 4; d++) {
        int p = i + DX[d], q = j + DY[d];
        if (inRange(p, q) && islower(A[p][q]) && !vis[p][q]) {
            dfs(p, q);
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        string s;
        getline(std::cin, s);
        M = max(M, (int)s.length());
        for (int j = 0; j < M; j++) {
            A[i][j] = s[j];
        }
    }

    int ret = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!vis[i][j] && islower(A[i][j])) {
                dfs(i, j);
                ret++;
            }
        }
    }
    printf("%d\n", ret);
    return 0;
}
