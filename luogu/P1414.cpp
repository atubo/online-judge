// https://www.luogu.org/problem/show?pid=1414
// P1414 又是毕业季II

#include <cstdio>

const int MAXN = 1000000;
int cnt[MAXN+1];
int gcd[MAXN+1];

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        cnt[x]++;
        gcd[1]++;
    }

    for (int d = 2; d <= MAXN; d++) {
        for (int m = d; m <= MAXN; m += d) {
            gcd[d] += cnt[m];
        }
    }

    int curr = 0;
    for (int i = MAXN; i >= 1; i--) {
        if (gcd[i] > curr) {
            for (int j = 0; j < gcd[i] - curr; j++) {
                printf("%d\n", i);
            }
            curr = gcd[i];
        }
    }
    return 0;
}
