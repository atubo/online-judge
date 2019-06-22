// https://leetcode.com/problems/valid-parenthesis-string/
// 678. Valid Parenthesis String

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool checkValidString(string s) {
        const int n = s.length();
        deque<int> dq;
        stack<int> lp;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') lp.push(i);
            else if (s[i] == '*') dq.push_back(i);
            else {
                if (!lp.empty()) lp.pop();
                else {
                    if (dq.empty()) return false;
                    dq.pop_front();
                }
            }
        }
        while (!lp.empty()) {
            int x = lp.top();
            if (dq.empty()) return false;
            int y = dq.back();
            if (y < x) return false;
            dq.pop_back();
            lp.pop();
        }
        return true;
    }
};

int main() {
    Solution solution;
    return 0;
}
