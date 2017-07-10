// https://leetcode.com/problems/next-greater-element-iii/#/description
// 556. Next Greater Element III

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int nextGreaterElement(int n) {
        if (n == 0) return -1;
        vector<int> d;
        int x = n;
        while (x > 0) {
            d.push_back(x % 10);
            x /= 10;
        }
        int i = 1;
        for(; i < (int)d.size(); i++) {
            if (d[i] < d[i-1]) break;
        }
        if (i == (int)d.size()) return -1;
        for (int j = 0; j <= i-1; j++) {
            if (d[j] > d[i]) {
                swap(d[i], d[j]);
                break;
            }
        }
        reverse(d.begin(), d.begin() + i);
        int64_t ret = 0;
        for (i = (int)d.size()-1; i >= 0; i--) {
            ret = ret * 10 + d[i];
        }
        return (ret > INT_MAX ? -1 : ret);
    }
};

int main() {
    int n;
    cin >> n;
    Solution solution;
    cout << solution.nextGreaterElement(n) << endl;
    return 0;
}
