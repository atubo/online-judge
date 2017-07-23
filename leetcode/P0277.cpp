// https://leetcode.com/problems/find-the-celebrity/#/description
// 277. Find the Celebrity

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

bool knows(int a, int b);

class Solution {
public:
    int findCelebrity(int n) {
        vector<int> prev(n);
        iota(prev.begin(), prev.end(), 0);
        while (prev.size() > 1) {
            vector<int> curr;
            for (int i = 0; i <= (int)prev.size()-2; i+=2) {
                bool ab = knows(prev[i], prev[i+1]);
                bool ba = knows(prev[i+1], prev[i]);
                if (ab && !ba) curr.push_back(prev[i+1]);
                else if (!ab && ba) curr.push_back(prev[i]);
            }
            if (prev.size()&1) curr.push_back(prev.back());
            swap(prev, curr);
        }
        if (prev.empty()) return -1;
        bool ret =  true;
        int candidate = prev[0];
        for (int i = 0; i < n; i++) {
            if (i == candidate) continue;
            if (!(knows(i, candidate) && !knows(candidate, i))) {
                ret = false;
                break;
            }
        }
        return ret ? candidate : -1;
    }
};

int main() {
    Solution solution;
    return 0;
}
