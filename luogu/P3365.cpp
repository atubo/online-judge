// https://www.luogu.org/problemnew/show/P3365
// 改造二叉树

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+10;
struct Node {
    int l, r;
} nodes[MAXN];
int A[MAXN], B[MAXN];

int N;
int curr;

void dfs(int u) {
    int l = nodes[u].l, r = nodes[u].r;
    if (l) dfs(l);
    B[curr++] = A[u];
    //in.push_back(A[u]);
    if (r) dfs(r);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 1; i <= N; i++) nodes[i].l = nodes[i].r = 0;
    for (int i = 2; i <= N; i++) {
        int fa, ch;
        scanf("%d%d", &fa, &ch);
        if (!ch) nodes[fa].l = i;
        else nodes[fa].r = i;
    }
    dfs(1);
    for (int i = 0; i < N; i++) {
        B[i] -= i;
    }
    //assert(curr == N);
#if 0
    for (int x: in) {
        printf("%d ", x);
    }
    printf("\n");
#endif

    vector<int> dp(N+1, INT_MAX);
    dp[0] = INT_MIN;
    for (int i = 0; i < curr; i++) {
        int x = B[i];
        int p = upper_bound(dp.begin(), dp.end(), x) - dp.begin();
        dp[p] = x;
    }
    int ret = 0;
    for (int i = N; i >= 0; i--) {
        if (dp[i] != INT_MAX) {
            ret = i;
            break;
        }
    }
    printf("%d\n", N-ret);
    return 0;
}
