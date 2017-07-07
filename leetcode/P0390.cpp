// https://leetcode.com/problems/elimination-game/#/description
// 390. Elimination Game

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lastRemaining(int n) {
        return solve1(n);
    }

    int solve1(int n) {
        if (n == 1) return 1;
        return 2 * solve2(n/2);
    }

    int solve2(int n) {
        if (n == 1) return 1;
        return 2 * solve1(n/2) - (n % 2 == 0);
    }
};

int main() {
    int n;
    cin >> n;
    Solution solution;
    cout << solution.lastRemaining(n) << endl;
    return 0;
}
