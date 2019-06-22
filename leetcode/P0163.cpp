// https://leetcode.com/problems/missing-ranges/
// 163. Missing Ranges

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> ret;
        int64_t prev = 1LL*lower - 1;
        for (int x: nums) {
            if (x != prev && x != prev + 1) {
                ret.push_back(convert(prev+1, x-1));
            }
            prev = x;
        }
        if (prev != upper) ret.push_back(convert(prev+1, upper));
        return ret;
    }

    string convert(int x, int y) {
        if (x == y) return to_string(x);
        return to_string(x) + "->" + to_string(y);
    }
};

int main() {
    Solution solution;
    return 0;
}
