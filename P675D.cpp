// http://codeforces.com/problemset/problem/675/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

struct TreeNode {
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    int val;

    TreeNode(int val_): left(NULL), right(NULL), parent(NULL), val(val_) {}
};

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, TreeNode*, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> NodeMap;

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        scanf("%d", &A[i]);\
    }

template <typename T>
void printVector(const vector<T>& A) {
    for (int i = 0; i < (int)A.size(); i++) {
        cout << A[i] << (i == (int)A.size()-1 ? "" : " ");
    }
    cout << endl;
}

class Solution {
    using Node = TreeNode;
private:
    int N;
    vector<int> A;
public:
    Solution() {
        cin >> N;
        A.resize(N);
        READ_ARRAY(N, A);
    }

    Node* createToRight(Node* node, int val) {
        Node* curr = new Node(val);
        node->right = curr;
        curr->parent = node;
        return curr;
    }

    Node* createToLeft(Node* node, int val) {
        Node* curr = new Node(val);
        node->left = curr;
        curr->parent = node;
        return curr;
    }

    void solve() {
        auto root = new Node(A[0]);
        map<int, Node*> nodeMap;
        nodeMap.insert(make_pair(A[0], root));

        for (int i = 1; i < N; i++) {
            auto succIt = nodeMap.lower_bound(A[i]);
            Node* curr = NULL;
            if (succIt == nodeMap.end()) {
                auto predIt = succIt;
                predIt--;
                curr = createToRight(predIt->second, A[i]);
            } else if (succIt == nodeMap.begin()) {
                curr = createToLeft(succIt->second, A[i]);
            } else {
                auto predIt = succIt;
                predIt--;
                auto pred = predIt->second;
                auto succ = succIt->second;
                if (pred->right) {
                    assert(!succ->left);
                    curr = createToLeft(succ, A[i]);
                } else {
                    curr = createToRight(pred, A[i]);
                }
            }
            nodeMap[A[i]] = curr;
            cout << curr->parent->val << " ";
        }
        cout << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
