// https://www.luogu.org/problemnew/show/P2747
// [USACO5.4]周游加拿大Canada Tour

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
bool adj[MAXN][MAXN];
int dp[MAXN][MAXN];
int N, V;

int main() {
    scanf("%d%d", &N, &V);
    map<string, int> lookup;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        lookup[s] = i;
    }
    for (int i = 0; i < V; i++) {
        string s, t;
        cin >> s >> t;
        int u = lookup.at(s);
        int v = lookup.at(t);
        adj[u][v] = adj[v][u] = true;
    }
    dp[0][0] = 1;
    for (int i = 1; i < N; i++) {
        if (adj[0][i]) {
            dp[0][i] = 2;
            break;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            if (dp[i][j] > 0) {
                for (int k = j+1; k < N; k++) {
                    if (adj[j][k]) {
                        dp[i][k] = max(dp[i][k], dp[i][j]+1);
                    }
                    if (adj[i][k]) {
                        dp[j][k] = max(dp[j][k], dp[i][j]+1);
                    }
                }
            }
        }
    }

    int ret = 1;
    for (int i = 0; i < N; i++) {
        if (dp[i][N-1] && adj[i][N-1]) {
            ret = max(ret, dp[i][N-1]);
        }
    }
    printf("%d\n", ret);
    return 0;
}
