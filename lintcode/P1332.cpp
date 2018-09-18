// https://www.lintcode.com/problem/number-of-1-bits/description
// 1332. Number of 1 Bits

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int hammingWeight(unsigned int n) {
        int ans = 0;
        while (n) {
            n &= (n-1);
            ans++;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    unsigned int n;
    cin >> n;
    cout << solution.hammingWeight(n) << endl;
    return 0;
}
