// https://www.luogu.org/problem/show?pid=2893
// [USACO08FEB]修路Making the Grade

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

const int MAXN = 2010;
int N;
int A[MAXN], C[MAXN], D[MAXN];
int64_t dp[MAXN], dpmin[MAXN];

int64_t solve1() {
    memset(dpmin, 0, sizeof(dpmin));

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < N; j++) {
            if (C[i] >= j) dp[j] = A[i] - A[D[j]] + dpmin[j];
            else dp[j] = A[D[j]] - A[i] + dpmin[j];
            dpmin[j] = dp[j];
            if (j > 0) dpmin[j] = min(dpmin[j], dpmin[j-1]);
        }
    }

    return dpmin[N-1];
}

int64_t solve2() {
    memset(dpmin, 0, sizeof(dpmin));

    for (int i = 1; i <= N; i++) {
        for (int j = N-1; j >= 0; j--) {
            if (C[i] >= j) dp[j] = A[i] - A[D[j]] + dpmin[j];
            else dp[j] = A[D[j]] - A[i] + dpmin[j];
            dpmin[j] = dp[j];
            if (j < N-1) dpmin[j] = min(dpmin[j], dpmin[j+1]);
        }
    }

    return dpmin[0];
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }

    vector<PII> valIdx;
    for (int i = 1; i <= N; i++) {
        valIdx.push_back(make_pair(A[i], i));
    }
    sort(valIdx.begin(), valIdx.end());
    for (int i = 0; i < N; i++) {
        C[valIdx[i].second] = i;
        D[i] = valIdx[i].second;
    }

    printf("%lld\n", min(solve1(), solve2()));

    return 0;
}
