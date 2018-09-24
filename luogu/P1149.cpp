// https://www.luogu.org/problemnew/show/P1149
// 火柴棒等式

#include <bits/stdc++.h>
using namespace std;

const int M = 1200;
int cnt[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int mcount[2*M+1];

void init() {
    for (int i = 0; i <= 2*M; i++) {
        string s = to_string(i);
        for (char c: s) {
            mcount[i] += cnt[c-'0'];
        }
    }
}

bool check(int a, int b, int n) {
    int c = a + b;
    return n == mcount[a] + mcount[b] + mcount[c] + 4;
}


int main() {
    init();
    int n;
    scanf("%d", &n);
    int ans = 0;
    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= M; j++) {
            ans += check(i, j, n);
        }
    }
    printf("%d\n", ans);
    return 0;
}
