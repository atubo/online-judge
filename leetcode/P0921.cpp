// https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/
// 921. Minimum Add to Make Parentheses Valid

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int minAddToMakeValid(string S) {
        int addLeft = 0;
        int surplus = 0;
        for (char c: S) {
            if (c == ')') {
                if (surplus == 0) addLeft++;
                else surplus--;
            } else {
                surplus++;
            }
        }
        return addLeft + surplus;
    }
};

int main() {
    Solution solution;
    return 0;
}
