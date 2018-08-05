// https://www.lintcode.com/problem/friends-within-three-jumps/description
// 932. Friends Within Three Jumps


#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
private:
    int id(int x, const vector<int> &nodes) {
        return lower_bound(nodes.begin(), nodes.end(), x) -
            nodes.begin();
    }

    bool bfs(int x, int y, const vector<vector<int>> &adj) {
        const int n = adj.size();
        vector<bool> vis(n, false);
        queue<pair<int, int>> q;
        q.push(make_pair(x, 0));
        vis[x] = true;
        while (!q.empty()) {
            x = q.front().first;
            int d = q.front().second;
            q.pop();
            if (x == y) return true;
            if (d < 3) {
                for (int z: adj[x]) {
                    if (!vis[z]) {
                        q.push(make_pair(z, d+1));
                        vis[z] = true;
                    }
                }
            }
        }
        return false;
    }

public:
    vector<int> withinThreeJumps(
        vector<int> &a, vector<int> &b,
        vector<int> &c, vector<int> &d) {
        vector<int> nodes;
        copy(a.begin(), a.end(), back_inserter(nodes));
        copy(b.begin(), b.end(), back_inserter(nodes));
        copy(c.begin(), c.end(), back_inserter(nodes));
        copy(d.begin(), d.end(), back_inserter(nodes));
        sort(nodes.begin(), nodes.end());
        nodes.erase(unique(nodes.begin(), nodes.end()),
                    nodes.end());

        const int n = nodes.size();
        vector<vector<int>> adj(n);
        for (int i = 0; i < (int)a.size(); i++) {
            int x = id(a[i], nodes), y = id(b[i], nodes);
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        const int m = c.size();
        vector<int> res(m);
        for (int i = 0; i < m; i++) {
            int x = id(c[i], nodes), y = id(d[i], nodes);
            res[i] = bfs(x, y, adj);
        }
        return res;
    }
};

int main() {
    Solution solution;
    auto a = getVector();
    auto b = getVector();
    auto c = getVector();
    auto d = getVector();
    auto res = solution.withinThreeJumps(a, b, c, d);
    printVector(res);
    return 0;
}
