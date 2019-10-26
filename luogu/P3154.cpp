// https://www.luogu.org/problem/P3154
// [CQOI2009]循环赛

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
int N;
int A[MAXN];
int pow3[MAXN];
unordered_map<int64_t, int> dp;
int PT[3] = {0, 1, 3};

struct Data {
    int n;
    int a[8];
    explicit Data(int64_t code) {
        n = (code >> 40) & 15;
        for (int i = 0; i < n; i++) {
            a[i] = (code >> (i*5)) & 31;
        }
    }
};

int64_t encode(int64_t n, int* a) {
    int64_t ret = 0;
    for (int i = 0; i < n; i++) {
        ret |= ((1LL*a[i]) << (i*5));
    }
    ret |= (n << 40);
    return ret;
}

bool feasible(int m, int n, const int* a) {
    int x = a[n];
    for (int i = 0; i < n; i++) {
        int z = m % 3;
        x -= PT[z];
        if (x < 0) return false;
        if (a[i]-PT[2-z] < 0) return false;
        m /= 3;
    }
    return x == 0;
}

void update(int m, int n, int* a) {
    for (int i = 0; i < n; i++) {
        int z = m % 3;
        a[i] -= PT[2-z];
        m /= 3;
    }
}

void restore(int m, int n, int* a) {
    for (int i = 0; i < n; i++) {
        int z = m % 3;
        a[i] += PT[2-z];
        m /= 3;
    }
}

int solve(int64_t code) {
    if (code == 0) {
        return 1;
    }
    if (dp.find(code) != dp.end()) return dp.at(code);

    Data d(code);

    int& ret = dp[code];
    for (int m = 0; m < pow3[d.n-1]; m++) {
        if (!feasible(m, d.n-1, d.a)) continue;
        update(m, d.n-1, d.a);
        int64_t code2 = encode(d.n-1, d.a);
        ret += solve(code2);
        restore(m, d.n-1, d.a);
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    pow3[0] = 1;
    for (int i = 1; i <= N; i++) pow3[i] = 3*pow3[i-1];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    int64_t code = encode(N, A);
    printf("%d", solve(code));
    return 0;
}
