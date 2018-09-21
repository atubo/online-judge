// https://www.lintcode.com/problem/add-digits/description
// 569. Add Digits

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int addDigits(int num) {
        return num == 0 ? 0 : (num%9 == 0 ? 9 : num%9);
    }
};

int main() {
    Solution solution;
    return 0;
}
