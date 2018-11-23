// https://www.luogu.org/problemnew/show/P2737
// [USACO4.1]麦香牛块Beef McNuggets

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

const int MAXC = 1e6+10;
int N;
int A[12];
bool dp[MAXC];

int solve() {
    int g = 0;
    for (int i = 0; i < N; i++) {
        g = gcd(g, A[i]);
    }
    if (g != 1) return 0;
    dp[0] = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < MAXC - A[i]; j++) {
            dp[j+A[i]] |= dp[j];
        }
    }
    for (int i = MAXC-1; i > 0; i--) {
        if (!dp[i]) return i;
    }
    return 0;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    printf("%d", solve());
    return 0;
}
