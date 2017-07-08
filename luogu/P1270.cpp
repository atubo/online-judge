// https://www.luogu.org/problem/show?pid=1270
// “访问”美术馆

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

int T;

struct Node {
    Node(int w_, int p_): wt(w_), p(p_) {
        if (p > 0) {
            sons[0] = sons[1] = -1;
        }
    }
    int wt;
    int p;
    int sons[2];
};

vector<Node> nodes;

int build() {
    int w, p;
    scanf("%d%d", &w, &p);
    int curr = nodes.size();
    nodes.push_back(Node(w, p));
    if (p == 0) {
        int left = build();
        int right = build();
        nodes[curr].sons[0] = left;
        nodes[curr].sons[1] = right;
    }
    return curr;
}


int dp[101][601];

int solve(int i, int tmax) {
    if (dp[i][tmax] >= 0) return dp[i][tmax];
    const Node& node = nodes[i];
    int cost = 2 * node.wt;
    if (tmax < cost) return 0;
    int& ret = dp[i][tmax] = 0;
    if (node.p > 0) {
        ret = min(node.p, (tmax - cost) / 5);
    } else {
        for (int tleft = 0; tleft <= tmax-cost; tleft++) {
            ret = max(ret,
                      solve(node.sons[0], tleft) +
                      solve(node.sons[1], tmax-cost-tleft));
        }
    }
    return ret;
}

int main() {
    scanf("%d", &T);
    build();

    memset(dp, -1, sizeof(dp));

    cout << solve(0, T-1) << endl;

    return 0;
}
