// https://www.luogu.org/problemnew/show/P3943
// 星空

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40010;
int N, K, M;
int A[MAXN], B[MAXN], idx[MAXN];
vector<int> pos;
int D[65];

int dist[20][20];
bool vis[20][MAXN];
int dp[1<<20];

struct Item {
    int s, t, d;
};

void bfs() {
    queue<Item> q;
    for (int x: pos) {
        q.push({x, x, 0});
        vis[idx[x]][x] = true;
    }
    while (!q.empty()) {
        Item item = q.front();
        q.pop();
        int sidx = idx[item.s];
        int tidx = idx[item.t];
        if (tidx >= 0) {
            dist[sidx][tidx] = item.d;
        }
        for (int i = 0; i < M; i++) {
            int next = item.t + D[i];
            if (next >= 1 && next <= N+1 && !vis[sidx][next]) {
                q.push({item.s, next, item.d+1});
                vis[sidx][next] = true;
            }
            next = item.t - D[i];
            if (next >= 1 && next <= N+1 && !vis[sidx][next]) {
                q.push({item.s, next, item.d+1});
                vis[sidx][next] = true;
            }
        }
    }
}

int solve(int k) {
    if (dp[k] >= 0) return dp[k];
    int &ret = dp[k];
    if (k == 0) return ret = 0;

    ret = 1e9;
    const int n = pos.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (dist[i][j] >= 0 && ((k >> i) & 1) && ((k >> j) & 1)) {
                int knext = k & (~(1<<i)) & (~(1<<j));
                ret = min(ret, dist[i][j] + solve(knext));
            }
        }
    }
    return ret;
}


int main() {
    memset(idx, -1, sizeof(idx));
    memset(dist, -1, sizeof(dist));
    memset(dp, -1, sizeof(dp));
    scanf("%d%d%d", &N, &K, &M);
    for (int i = 0; i < K; i++) {
        int a;
        scanf("%d", &a);
        A[a] = 1;
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &D[i]);
    }
    for (int i = 1; i <= N+1; i++) {
        B[i] = A[i] ^ A[i-1];
        if (B[i]) {
            idx[i] = pos.size();
            pos.push_back(i);
        }
    }

    bfs();
    int ans = solve((1<<pos.size())-1);
    printf("%d\n", ans);
    return 0;
}
