// https://www.luogu.org/problemnew/show/P2219
// [HAOI2007]修筑绿化带

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int M, N, A, B, C, D;
int G[MAXN][MAXN];

int g(int x, int y) {
    if (x < 0 || y < 0) return 0;
    return G[x][y];
}

int outer(int x, int y) {
    return g(x, y) - g(x-A, y) - g(x, y-B) + g(x-A, y-B);
}

int inner(int x, int y) {
    return g(x, y) - g(x-C, y) - g(x, y-D) + g(x-C, y-D);
}

void push(deque<int> &rowq,
          vector<deque<int>> &colq,
          int row, int col) {
    if (row < 0) return;
    while (!colq[col].empty() &&
           colq[col].front() <= row-A+C+1) colq[col].pop_front();
    while (!colq[col].empty() &&
           inner(row, col) <= inner(colq[col].back(), col)) {
        colq[col].pop_back();
    }
    colq[col].push_back(row);
    while (!rowq.empty() && rowq.front() <= col-B+D+1) rowq.pop_front();
    while (!rowq.empty() &&
           inner(colq[col].front(), col) <=
           inner(colq[rowq.back()].front(), rowq.back())) {
        rowq.pop_back();
    }
    rowq.push_back(col);
}


int main() {
    scanf("%d%d%d%d%d%d", &M, &N, &A, &B, &C, &D);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &G[i][j]);
        }
    }
    for (int i = 1; i < N; i++) G[0][i] += G[0][i-1];
    for (int i = 1; i < M; i++) G[i][0] += G[i-1][0];
    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N; j++) {
            G[i][j] = G[i][j-1] + G[i-1][j] + G[i][j] - G[i-1][j-1];
        }
    }

    int ans = 0;
    vector<deque<int>> colq(N);
    for (int row = 0; row < M; row++) {
        deque<int> rowq;
        for (int col = 0; col < N; col++) {
            if (row >= A-1 && col >= B-1) {
                int c = rowq.front();
                int r = colq[c].front();
                ans = max(ans, outer(row, col)-inner(r, c));
            }
            push(rowq, colq, row-1, col);
        }
    }

    printf("%d", ans);
    return 0;
}
