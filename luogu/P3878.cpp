// https://www.luogu.org/problemnew/show/P3878
// [TJOI2010]分金币

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 32;
int T;
int N;
int A[MAXN];
int B1[MAXN], B2[MAXN];
int K1, K2;
int64_t s1, s2;
int64_t ans;

void anneal() {
    int64_t nowans = ans;
    double temp = 1000000;
    while (temp > 1e-14) {
        int x = rand() % K1;
        int y = rand() % K2;
        s1 += B2[y] - B1[x];
        s2 += B1[x] - B2[y];
        swap(B1[x], B2[y]);
        int64_t now = abs(s2-s1);
        double delta = now - ans;
        if (delta < 0) ans = nowans = now;
        else if (exp(-delta/temp)*RAND_MAX > rand()) nowans = now;
        else {
            s1 += B2[y] - B1[x];
            s2 += B1[x] - B2[y];
            swap(B1[x], B2[y]);
        }
        temp *= 0.993;
    }
}

void solve() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    if (N == 1) {
        printf("%d\n", A[0]);
        return;
    }
    K1 = N / 2;
    K2 = N - K1;
    s1 = 0;
    for (int i = 0; i < K1; i++) {
        B1[i] = A[i];
        s1 += B1[i];
    }
    s2 = 0;
    for (int i = 0; i < K2; i++) {
        B2[i] = A[i+K1];
        s2 += B2[i];
    }
    ans = abs(s2-s1);
    for (int i = 0; i < 50; i++) {
        anneal();
    }
    printf("%ld\n", ans);
}

int main() {
    srand(19491001);
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
