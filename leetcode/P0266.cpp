// https://leetcode.com/problems/palindrome-permutation/#/description
// 266. Palindrome Permutation

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canPermutePalindrome(string s) {
        int cnt[128] = {0};
        for (char c: s) {
            cnt[int(c)]++;
        }
        int odd = 0;
        for (int i = 0; i < 128; i++) {
            odd += (cnt[i]&1);
        }
        return odd <= 1;
    }
};

int main() {
    Solution solution;
    return 0;
}
