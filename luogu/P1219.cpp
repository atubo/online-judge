// https://www.luogu.org/problemnew/show/P1219
// 八皇后

#include <bits/stdc++.h>
using namespace std;

int curr;
int N;
int A[15], C0[30], C1[30], C2[30];
int result[3][15];

void dfs(int row) {
    if (row == N) {
        if (curr < 3) {
            memcpy(result[curr], A, 15*sizeof(int));
        }
        curr++;
        return;
    }
    for (int col = 0; col < N; col++) {
        if (!C1[row-col+(N-1)] && !C2[row+col] && !C0[col]) {
            C0[col] = 1;
            C1[row-col+(N-1)] = 1;
            C2[row+col] = 1;
            A[row] = col;
            dfs(row+1);
            C0[col] = 0;
            C1[row-col+(N-1)] = 0;
            C2[row+col] = 0;
        }
    }
}

int main() {
    scanf("%d", &N);
    dfs(0);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]+1);
        }
        printf("\n");
    }
    printf("%d\n", curr);
    return 0;
}
