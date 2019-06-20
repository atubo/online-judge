// https://leetcode.com/problems/friends-of-appropriate-ages/
// 825. Friends Of Appropriate Ages

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int numFriendRequests(vector<int> &ages) {
        sort(ages.begin(), ages.end());
        const int n = ages.size();
        int ret = 0;
        for (int i = 0; i < n; i++) {
            int x = ages[i];
            int t = x/2 + 7;
            if (t >= x) continue;
            int k = upper_bound(ages.begin(), ages.end(), t) - ages.begin();
            int q = upper_bound(ages.begin(), ages.end(), x) - ages.begin();
            ret += q - k - 1;
        }
        return ret;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {20, 30, 100, 110, 120};
    cout << solution.numFriendRequests(nums);
    return 0;
}
