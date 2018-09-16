// https://www.lintcode.com/problem/six-degrees/description
// 531. Six Degrees

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int sixDegrees(vector<UndirectedGraphNode*> graph,
                  UndirectedGraphNode *s,
                  UndirectedGraphNode *t) {
        set<UndirectedGraphNode*> vis;
        queue<pair<UndirectedGraphNode*, int>> q;
        q.push(make_pair(s, 0));
        vis.insert(s);
        while (!q.empty()) {
            UndirectedGraphNode* p;
            int d;
            tie(p, d) = q.front();
            q.pop();
            if (p == t) return d;
            for (auto v: p->neighbors) {
                if (vis.count(v) == 0) {
                    q.push(make_pair(v, d+1));
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution solution;
    return 0;
}
