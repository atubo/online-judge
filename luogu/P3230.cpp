// https://www.luogu.org/problemnew/show/P3230
// [HNOI2013]比赛

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 12;
int N;
int S[MAXN], A[MAXN];
int cnt_win, cnt_draw;

map<int64_t, int64_t> mp;

bool cmp(int x, int  y) {
    return x > y;
}

int64_t hashScore(int l, int r) {
    int tmp[MAXN];
    for (int i = l; i <= r; i++) {
        tmp[i] = S[i]-A[i];
    }
    sort(tmp+l, tmp+r+1, cmp);
    int64_t ret = 0;
    for (int i = l; i <= r; i++) {
        ret = ret*27 + tmp[i];
    }
    return ret;
}

int64_t dfs(int u, int v) {
    int64_t ret = 0;
    if (u == N) return 1;
    if (A[u]+3*(N-v+1) < S[u]) return 0;
    if (v == N+1) {
        int64_t h = hashScore(u+1, N);
        if (mp.count(h) > 0) return mp.at(h);
        else return mp[h] = dfs(u+1, u+2);
    }
    if (A[u] > S[u]) return 0;
    if (A[u]+3 <= S[u] && cnt_win > 0) {
        cnt_win--;
        A[u] += 3;
        (ret += dfs(u, v+1)) %= MOD;
        A[u] -= 3;
        cnt_win++;
    }
    if (A[u]+1 <= S[u] && A[v]+1 <= S[v] && cnt_draw > 0) {
        cnt_draw--;
        A[u]++;
        A[v]++;
        (ret += dfs(u, v+1)) %= MOD;
        A[v]--;
        A[u]--;
        cnt_draw++;
    }
    if (A[v]+3 <= S[v] && cnt_win > 0) {
        cnt_win--;
        A[v] += 3;
        (ret += dfs(u, v+1)) %= MOD;
        A[v] -= 3;
        cnt_win++;
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    int tot = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &S[i]);
        tot += S[i];
    }
    sort(S+1, S+N+1, cmp);
    int np = N*(N-1);
    cnt_win = (tot-np);
    cnt_draw = np/2 - cnt_win;
    int64_t ans = dfs(1, 2);
    printf("%ld\n", ans);
    return 0;
}
