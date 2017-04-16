// https://www.luogu.org/problem/show?pid=1247
// 取火柴游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXK = 500010;
int A[MAXK];
int K;

int main() {
    scanf("%d", &K);
    int ret = 0;
    for (int i = 0; i < K; i++) {
        scanf("%d", &A[i]);
        ret ^= A[i];
    }
    if (ret) {
        int a = 0, b = 0;
        for (; b < K; b++) {
            int c = A[b] ^ ret;
            if (c < A[b]) {
                a = A[b] - c;
                A[b] = c;
                break;
            }
        }
        printf("%d %d\n", a, b+1);
        for (int i = 0; i < K; i++) {
            printf("%d ", A[i]);
        }
        printf("\n");
    } else {
        printf("lose\n");
    }
    return 0;
}
