// https://www.luogu.org/problemnew/show/P2661
// 信息传递

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200010;
int N, ans = INT_MAX;
int T[MAXN];
bool vis[MAXN], inStack[MAXN];
int curr;
int id[MAXN];

void dfs(int u) {
    vis[u] = true;
    inStack[u] = true;
    id[u] = curr++;

    int v = T[u];
    if (!vis[v]) {
        dfs(v);
    } else {
        if (inStack[v]) {
            ans = min(ans, curr-id[v]);
        }
    }
    inStack[u] = false;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &T[i]);
        T[i]--;
    }

    for (int i = 0; i < N; i++) {
        if (!vis[i]) dfs(i);
    }
    printf("%d\n", ans);
    return 0;
}
