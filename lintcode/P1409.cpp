// https://www.lintcode.com/problem/matrix-finding-number/description
// 1409. Matrix Finding Number

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int findingNumber(vector<vector<int>> &mat) {
        map<int, int> m;
        for (auto &v: mat) {
            sort(v.begin(), v.end());
            auto e = unique(v.begin(), v.end());
            for (auto it = v.begin(); it != e; it++) {
                m[*it]++;
            }
        }
        int ans = -1;
        for (auto it = m.begin(); it != m.end(); it++) {
            if (it->second == (int)mat.size()) {
                ans = it->first;
                break;
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    return 0;
}
