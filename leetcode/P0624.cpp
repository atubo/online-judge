// https://leetcode.com/problems/maximum-distance-in-arrays/#/description
// 624. Maximum Distance in Arrays

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    int maxDistance(vector<vector<int>>& A) {
        vector<PII> minmax;
        for (const auto& v: A) {
            if (!v.empty()) minmax.push_back(make_pair(v.front(), v.back()));
        }
        const int N = minmax.size();
        vector<int> minelem(N+2), maxleft(N+2), maxright(N+2);
        for (int i = 1; i <= N; i++) {
            minelem[i] = minmax[i-1].first;
        }
        maxleft[0] = INT_MIN;
        for (int i = 1; i <= N; i++) {
            maxleft[i] = max(maxleft[i-1], minmax[i-1].second);
        }
        maxright[N+1] = INT_MIN;
        for (int i = N; i >= 0; i--) {
            maxright[i] = max(maxright[i+1], minmax[i-1].second);
        }
        int ret = 0;
        for (int i = 1; i <= N; i++) {
            ret = max(ret, max(maxleft[i-1], maxright[i+1]) - minelem[i]);
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
