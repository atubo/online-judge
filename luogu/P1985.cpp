// https://www.luogu.org/problemnew/show/P1985
// [USACO07OPEN]翻转棋

#include <bits/stdc++.h>
using namespace std;

int M, N;
int orig[16], curr[16], turn[16], bestturn[16];

void apply(int i, int op) {
    curr[i] ^= ((op ^ (op>>1) ^ (op<<1)) & ((1<<N)-1));
    if (i > 0) curr[i-1] ^= op;
    if (i < M-1) curr[i+1] ^= op;
}

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; i++) {
        orig[i] = 0;
        for (int j = 0; j < N; j++) {
            int c;
            scanf("%d", &c);
            orig[i] |= (c << (N-j-1));
        }
    }

    int mincnt = INT_MAX;
    for (int op = 0; op < (1<<N); op++) {
        int cnt = __builtin_popcount(op);
        memcpy(curr, orig, sizeof(curr));
        turn[0] = op;
        apply(0, op);
        for (int row = 1; row < M; row++) {
            int currOp = curr[row-1];
            cnt += __builtin_popcount(currOp);
            turn[row] = currOp;
            apply(row, currOp);
        }
        if (curr[M-1] == 0 && cnt < mincnt) {
            mincnt = cnt;
            memcpy(bestturn, turn, sizeof(bestturn));
        }
    }

    if (mincnt < INT_MAX) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", (bestturn[i]>>(N-j-1)) & 1);
            }
            printf("\n");
        }
    } else {
        printf("IMPOSSIBLE");
    }

    return 0;
}
