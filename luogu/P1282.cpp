// https://www.luogu.org/problem/show?pid=1282
// 多米诺骨牌

#include <bits/stdc++.h>
using namespace std;

int A[1010];
int f[10010];
int N;

int g(int x) {
    return x + 5*N;
}

void pr() {
    for (int i = -5*N; i <= 5*N; i++) {
        if (f[g(i)] < INT_MAX) {
            printf("(%d %d) ", i, f[g(i)]);
        }
    }
    printf("\n");
}

int main() {
    scanf("%d", &N);
    int total = 0;
    for (int i = 1; i <= N; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        A[i] = a - b;
        total += A[i];
    }
    for (int j = -5*N; j <= 5*N; j++) {
        f[g(j)] = INT_MAX;
    }
    f[g(total)] = 0;
    for (int i = 1; i <= N; i++) {
        if (A[i] > 0) {
            for (int j = -5*N; j+2*A[i] <= 5*N; j++) {
                if (f[g(j+2*A[i])] < INT_MAX) {
                    f[g(j)] = min(f[g(j+2*A[i])] + 1, f[g(j)]);
                }
            }
        } else if (A[i] < 0) {
            for (int j = 5*N; j+2*A[i] >= -5*N; j--) {
                if (f[g(j+2*A[i])] < INT_MAX) {
                    f[g(j)] = min(f[g(j+2*A[i])] + 1, f[g(j)]);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= 5*N; i++) {
        if (f[g(i)] < INT_MAX || f[g(-i)] < INT_MAX) {
            ans = min(f[g(i)], f[g(-i)]);
            break;
        }
    }
    printf("%d\n", ans);
    return 0;
}
