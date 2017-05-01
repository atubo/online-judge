// https://www.luogu.org/problem/show?pid=2780
// [AHOI2016初中组]游戏

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 75000;
bool dp[260][MAXM+1];
int N, K, A, B;
int X[260];

int minDist(const vector<int> &pos, int x) {
    auto it = lower_bound(pos.begin(), pos.end(), x);
    if (it == pos.end()) {
        return x - pos.back();
    }
    if (it == pos.begin()) {
        return pos.front() - x;
    }

    if (*it == x) return 0;
    auto it2 = it - 1;
    return min(*it - x, x - *it2);
}


int main() {
    scanf("%d%d%d%d", &N, &K, &A, &B);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &X[i]);
    }

    dp[0][0] = true;
    for (int i = 1; i <= N; i++) {
        for (int m = MAXM; m >= 0; m--) {
            for (int k = 0; k <= K; k++) {
                if (k > 0 && X[i] <= m) {
                    dp[k][m] = dp[k][m] || dp[k-1][m-X[i]];
                }
            }
        }
    }

    vector<int> pos;
    for (int m = 0; m <= MAXM; m++) {
        if (dp[K][m]) pos.push_back(m);
    }

    int ret = 0;
    for (int i = A; i <= B; i++) {
        ret = max(ret, minDist(pos, i));
    }
    printf("%d\n", ret);
    return 0;
}
