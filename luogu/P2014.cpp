// https://www.luogu.org/problemnew/show/P2014
// 选课

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310, MAXM = 310;
const int MINF = -1e8;
int N, M;
int S[MAXN];
vector<int> order;

struct Node {
    int left, right, credit;
} nodes[MAXN];

vector<vector<int>> children(MAXN);

int dp[MAXN][MAXM];

void build(int r) {
    nodes[r].credit = S[r];
    if (children[r].empty()) return;
    int u = children[r][0];
    build(u);
    nodes[r].left = u;
    for (int i = 1; i < (int)children[r].size(); i++) {
        int v = children[r][i];
        build(v);
        nodes[v].right = nodes[u].right;
        nodes[u].right = v;
    }
}

void dfs(int u) {
    order.push_back(u);
    if (nodes[u].left) dfs(nodes[u].left);
    if (nodes[u].right) dfs(nodes[u].right);
}

void print(int r) {
    if (r == 0) return;
    printf("%d %d ", r, nodes[r].credit);
    printf("(");
    print(nodes[r].left);
    printf(")");
    printf("(");
    print(nodes[r].right);
    printf(")");
}

void solve(int r) {
    if (r == 0) return;
    //printf("r=%d ", r);
    for (int m = 1; m <= M; m++) {
        int left = nodes[r].left;
        int right = nodes[r].right;

        int &entry = dp[r][m];
        // not take this one
        entry = dp[right][m];

        // take this one
        for (int k = 0; k <= m-1; k++) {
            entry = max(entry, S[r] + dp[left][k] + dp[right][m-1-k]);
        }
        //printf("%d ", entry);
    }
    //printf("\n");
}

int main() {
    for (int i = 1; i < MAXM; i++) dp[0][i] = MINF;
    scanf("%d%d", &N, &M);
    vector<int> rts;
    for (int i = 1; i <= N; i++) {
        int k, s;
        scanf("%d%d", &k, &s);
        if (k > 0) children[k].push_back(i);
        else rts.push_back(i);
        S[i] = s;
    }
    int root = rts[0];
    build(root);
    for (int i = 1; i < (int)rts.size(); i++) {
        int u = rts[i];
        build(u);
        nodes[u].right = nodes[root].right;
        nodes[root].right = u;
    }
    //print(root);
    dfs(root);
    //for (int x: order) printf("%d ", x);
    //printf("\n");
    for (int i = order.size()-1; i >= 0; i--) {
        solve(order[i]);
    }
    printf("%d\n", dp[root][M]);
    return 0;
}
