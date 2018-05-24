// https://www.luogu.org/problemnew/show/P2515
// [HAOI2010]软件安装

#include <bits/stdc++.h>
using namespace std;

class MultiTreeToBinaryTree {
    // nodes are 0-indexed
public:
    struct Node {
        Node(int l = -1, int r = -1): left(l), right(r) {}
        int left, right;

        bool operator == (const Node &other) const {
            return left == other.left && right == other.right;
        }
    };

    MultiTreeToBinaryTree(const vector<vector<int>> &children, int root)
        :children_(children) {
        n_ = children.size();
        alloc();
        build(root);
    }

    ~MultiTreeToBinaryTree() {
        dealloc();
    }

private:
    int n_;
    const vector<vector<int>> &children_;
public:
    Node *nodes;

private:
    void alloc() {
        nodes = new Node[n_]{};
    }

    void dealloc() {
        delete[] nodes;
    }

    void build(int r) {
        if (children_[r].empty()) return;
        int u = children_[r][0];
        build(u);
        nodes[r].left = u;
        for (int i = 1; i < (int)children_[r].size(); i++) {
            int v = children_[r][i];
            build(v);
            nodes[v].right = nodes[u].right;
            nodes[u].right = v;
        }
    }
};

const int MAXN = 110;;
int N, M;
int W[MAXN], V[MAXN];
int dp[MAXN][501];

using Node = MultiTreeToBinaryTree::Node;

int solve(Node *nodes, int u, int m) {
    if (u == -1) return 0;
    if (dp[u][m] != -1) return dp[u][m];
    int &ret = dp[u][m];
    ret = solve(nodes, nodes[u].right, m);
    if (m >= W[u]) {
        for (int k = 0; k <= m - W[u]; k++) {
            int t = V[u] + solve(nodes, nodes[u].left, k) +
                solve(nodes, nodes[u].right, m - W[u] - k);
            ret = max(ret, t);
        }
    }
    return ret;
}

int main() {
    memset(dp, -1, sizeof(dp));
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &W[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &V[i]);
    }
    vector<vector<int>> children(N+1);
    for (int i = 1; i <= N; i++) {
        int d;
        scanf("%d", &d);
        children[d].push_back(i);
    }

    MultiTreeToBinaryTree bt(children, 0);
    int ans = solve(bt.nodes, 0, M);
    printf("%d", ans);

    return 0;
}
