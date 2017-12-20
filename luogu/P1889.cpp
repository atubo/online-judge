// https://www.luogu.org/problemnew/show/P1889
// 士兵站队

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    scanf("%d", &N);
    vector<int> X(N), Y(N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &X[i], &Y[i]);
    }
    sort(Y.begin(), Y.end());
    int ret = 0;
    for (int y: Y) {
        ret += abs(Y[N/2] - y);
    }

    sort(X.begin(), X.end());
    for (int i = 0; i < N; i++) {
        X[i] = X[i] - i;
    }
    sort(X.begin(), X.end());
    for (int x: X) {
        ret += abs(X[N/2] - x);
    }
    printf("%d\n", ret);
    return 0;
}
