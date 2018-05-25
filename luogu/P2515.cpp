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


void collapse(int n) {
    vector<int> w(n+1), v(n+1), d(n+1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);
    }

    vector<bool> vis(n+1, false), instack(n+1, false);
    vector<int> root(n+1);
    stack<int> st;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            int u = i;
            while (u != 0 && !vis[u]) {
                vis[u] = true;
                st.push(u);
                instack[u] = true;
                u = d[u];
            }
            if (u == 0 || !instack[u]) {
                while (!st.empty()) {
                    int up = st.top();
                    st.pop();
                    instack[up] = false;
                    root[up] = up;
                    d[up] = root[u];
                    u = up;
                }
            } else {
                int r = u;
                d[r] = 0;
                int tw = 0, tv = 0;
                while (!st.empty()) {
                    u = st.top();
                    st.pop();
                    instack[u] = false;
                    root[u] = r;
                    tw += w[u];
                    tv += v[u];
                    if (u == r) break;
                }
                w[r] = tw;
                v[r] = tv;
                while (!st.empty()) {
                    int up = st.top();
                    st.pop();
                    instack[up] = false;
                    root[up] = up;
                    d[up] = root[u];
                    u = up;
                }
            }
        }
    }

    int cnt = 1;
    vector<int> id(n+1, -1);
    for (int i = 1; i <= n; i++) {
        if (root[i] == i) {
            if (id[i] == -1) id[i] = cnt++;
            int x = id[i];
            W[x] = w[i];
            V[x] = v[i];
        }
    }
    N = cnt - 1;
    vector<vector<int>> children(N+1);
    for (int i = 1; i <= n; i++) {
        if (root[i] == i) {
            int fa = (d[i] == 0 ? 0 : id[d[i]]);
            children[fa].push_back(id[i]);
        }
    }

    MultiTreeToBinaryTree bt(children, 0);
    int ans = solve(bt.nodes, 0, M);
    printf("%d", ans);
}

int main() {
    memset(dp, -1, sizeof(dp));
    int n;
    scanf("%d%d", &n, &M);
    collapse(n);

    return 0;
}
