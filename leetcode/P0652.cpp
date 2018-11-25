#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    using Key = tuple<int, int, int>;
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode *root) {
        if (!root) return vector<TreeNode*>();
        map<Key, int> toId;
        vector<int> cnt;
        vector<TreeNode*> nodes;
        dfs(root, toId, cnt, nodes);
        vector<TreeNode*> ret;
        for (int i = 0; i < (int)cnt.size(); i++) {
            if (cnt[i] > 1) ret.push_back(nodes[i]);
        }
        return ret;
    }

private:
    int dfs(TreeNode *root, map<Key, int> &toId,
            vector<int> &cnt, vector<TreeNode*> &nodes) {
        int left = -1, right = -1;
        if (root->left) left = dfs(root->left, toId, cnt, nodes);
        if (root->right) right = dfs(root->right, toId, cnt, nodes);
        Key key = {left, right, root->val};
        if (toId.count(key) == 0) {
            toId.insert(make_pair(key, toId.size()));
            cnt.push_back(1);
            nodes.push_back(root);
        } else {
            int id = toId.at(key);
            cnt[id]++;
        }
        return toId.at(key);
    }
};

int main() {
    Solution solution;
    TreeNode *root;
    cin >> root;
    auto ret = solution.findDuplicateSubtrees(root);
    for (auto v: ret) {
        printf("%d ", v->val);
    }
    return 0;
}
