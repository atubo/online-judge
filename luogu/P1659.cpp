// https://www.luogu.org/problem/show?pid=1659
// 养猪

#include <bits/stdc++.h>
using namespace std;

struct Pig {
    int a, p;
    bool operator < (const Pig &other) {
        if (p > other.p) return true;
        if (p < other.p) return false;
        return a > other.a;
    }
};

int N, K;

int main() {
    scanf("%d%d", &N, &K);
    vector<Pig> pigs(N+1);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &pigs[i].a);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &pigs[i].p);
    }

    sort(pigs.begin()+1, pigs.begin()+N+1);
    vector<int> dp(K+1, 0);

    int ret = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = min(i, K); j > 0; j--) {
            dp[j] = max(dp[j], dp[j-1] + max(0, pigs[i].a - (j-1)*pigs[i].p));
            ret = max(ret, dp[j]);
        }
    }
    printf("%d\n", ret);

    return 0;
}
