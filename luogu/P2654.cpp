// https://www.luogu.org/problemnew/show/P2654
// 原核生物培养

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
int N, M, K;

int dp[22][22];

int solve(const vector<int> &ps, int p, int q) {
    if (p == q || p == q-1) return 0;
    if (dp[p][q] >= 0) return dp[p][q];
    int &res = dp[p][q];
    int t1 = ps[q-1] - ps[p-1];
    int t2 = INT_MAX;
    for (int r = p+1; r < q; r++) {
        t2 = min(t2, solve(ps, p, r) + solve(ps, r, q));
    }
    return res = (t1 + t2);
}


int solve(const vector<int> &prok) {
    vector<int> ap(2*M+1);
    vector<int> ps(2*M+1);
    for (int i = 1; i <= M; i++) {
        ap[i] = ap[i+M] = prok[i];
    }
    for (int i = 1; i <= 2*M; i++) {
        ps[i] = ps[i-1] + ap[i];
    }

    memset(dp, -1, sizeof(dp));
    int ans = INT_MAX;
    for (int i = 1; i <= M; i++) {
        ans = min(ans, solve(ps, i, i+M));
    }
    return ans;
}


int main() {
    scanf("%d%d%d", &N, &M, &K);
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        q.push(x);
    }
    int ans = 0;
    for (int i = 0; i < K; i++) {
        vector<int> prok(M+1);
        int t = 0;
        for (int j = 1; j <= M; j++) {
            int x = q.top();
            t += x;
            q.pop();
            int pos;
            scanf("%d", &pos);
            prok[pos] = x;
        }
#if 0
        for (int j = 1; j <= M; j++) {
            printf("%d ", prok[j]);
        }
        printf("\n");
#endif
        q.push(t);
        ans += solve(prok);
        //printf("ans=%d\n", ans);
    }
    printf("%d\n", ans);
    return 0;
}
