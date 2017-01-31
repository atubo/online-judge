// https://www.luogu.org/problem/show?pid=1064
// 金明的预算方案

#include <bits/stdc++.h>
using namespace std;

const int MAXW = 32010;
const int MAXN = 62;
const int MINF = -1234567890;

int dp[2][MAXW];
int wt[MAXN];
int value[MAXN];

int main() {
    vector<int> primary;
    vector<vector<int> > secondary;

    int N, M;
    scanf("%d %d", &N, &M);
    secondary.resize(M);
    for (int i = 0; i < M; i++) {
        int v, p, q;
        scanf("%d %d %d", &v, &p, &q);
        wt[i] = v;
        value[i] = p;
        if (q == 0) {
            primary.push_back(i);
        } else {
            secondary[q-1].push_back(i);
        }
    }

    for (int i = 0; i < (int)primary.size(); i++) {
        int p = primary[i];

        int curr = (i % 2);
        int prev = ((i + 1) % 2);
        for (int w = N; w >= wt[p]; w--) {
            dp[curr][w] = dp[prev][w-wt[p]] + value[p] * wt[p];
        }
        for (int w = 0; w < wt[p]; w++) {
            dp[curr][w] = MINF;
        }
        for (int j = 0; j < (int)secondary[p].size(); j++) {
            int s = secondary[p][j];
            for (int w = N; w >= wt[s]; w--) {
                dp[curr][w] = max(dp[curr][w], dp[curr][w-wt[s]] + value[s] * wt[s]);
            }
        }
        for (int w = 0; w <= N; w++) {
            dp[curr][w] = max(dp[curr][w], dp[prev][w]);
        }
    }

    int curr = (primary.size()-1) % 2;
    printf("%d\n", dp[curr][N]);
    return 0;
}
