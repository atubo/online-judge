// https://www.luogu.org/problemnew/show/P1272
// 重建道路

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

using Node = MultiTreeToBinaryTree::Node;

const int MAXN = 155;
const int INF = 1e6;
int N, P;

int dp1[MAXN][MAXN], dp2[MAXN][MAXN];

int solve2(const Node *nodes, int u, int n);

int solve1(const Node *nodes, int u, int n) {
    if (u == -1) {
        return n == 0 ? 0 : INF;
    }
    if (dp1[u][n] != -1) return dp1[u][n];
    int &ret = dp1[u][n];
    if (n == 0) return ret = 1;

    return ret = solve2(nodes, nodes[u].left, n-1);
}

int solve2(const Node *nodes, int u, int n) {
    if (u == -1) {
        return n == 0 ? 0 : INF;
    }
    if (dp2[u][n] != -1) return dp2[u][n];
    int &ret = dp2[u][n];
    ret = INF;
    for (int i = 0; i <= n; i++) {
        int t = solve1(nodes, u, i) +
            solve2(nodes, nodes[u].right, n-i);
        ret = min(ret, t);
    }
    return ret;
}

int main() {
    memset(dp1, -1, sizeof(dp1));
    memset(dp2, -1, sizeof(dp2));
    scanf("%d%d", &N, &P);
    vector<vector<int>> children(N);
    for (int i = 0; i < N-1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        children[x].push_back(y);
    }

    MultiTreeToBinaryTree bt(children, 0);
    for (int u = 0; u < N; u++) {
        for (int i = 0; i <= P; i++) {
            solve1(bt.nodes, u, i);
        }
    }
    int ans = INF;
    for (int u = 0; u < N; u++) {
        ans = min(ans, dp1[u][P] + (u != 0));
    }
    printf("%d\n", ans);
    return 0;
}
