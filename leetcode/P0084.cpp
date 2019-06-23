// https://leetcode.com/problems/largest-rectangle-in-histogram/
// 84. Largest Rectangle in Histogram

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    struct Data {
        int x, y;
    };
public:
    int largestRectangleArea(vector<int>& heights) {
        const int n = heights.size();
        vector<int> ret(n);
        if (n == 0) return 0;
        stack<Data> st;
        for (int i = 0; i < n; i++) {
            int x = i, y = heights[i];
            while (!st.empty() && st.top().y >= y) {
                x = st.top().x;
                st.pop();
            }
            ret[i] = y * (i-x);
            st.push({x, y});
        }
        while (!st.empty()) st.pop();
        int ans = 0;
        for (int i = n-1; i >= 0; i--) {
            int x = i, y = heights[i];
            while (!st.empty() && st.top().y >= y) {
                x = st.top().x;
                st.pop();
            }
            ret[i] += y * (x-i) + y;
            ans = max(ans, ret[i]);
            st.push({x, y});
        }
        return ans;
    }
};

int main() {
    Solution solution;
    return 0;
}
