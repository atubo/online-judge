// https://www.luogu.org/problem/show?pid=1549
// 棋盘问题（2）

#include <bits/stdc++.h>
using namespace std;

bool isP[201];
int N;
int board[11][11];
bool vis[110];

pair<int, int> next(int i, int j) {
    if (i == N-1) return make_pair(j+1, j+1);
    if (j == N-1) return make_pair(i+1, i);
    if (i == j) return make_pair(i, j+1);
    if (j > i) return make_pair(i, j+1);
    return make_pair(i+1, j);
}

bool dfs(int i, int j) {
    if (i == N) return true;
    for (int x = 1; x <= N*N; x++) {
        if (!vis[x]) {
            if (j > 0 && !isP[board[i][j-1] + x]) continue;
            if (i > 0 && !isP[board[i-1][j] + x]) continue;
            board[i][j] = x;
            int nexti, nextj;
            tie(nexti, nextj) = next(i, j);
            vis[x] = true;
            bool ret = dfs(nexti, nextj);
            if (ret) return true;
            vis[x] = false;
        }
    }
    return false;
}

bool isPrime(int n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int x = 3; x * x <= n; x += 2) {
        if (n % x == 0) return false;
    }
    return true;
}

int main() {
    for (int i = 2; i <= 200; i++) {
        isP[i] = isPrime(i);
    }
    scanf("%d", &N);
    board[0][0] = 1; vis[1] = true;
    bool ret = dfs(0, 1);
    if (ret) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("NO\n");
    }
    return 0;
}
