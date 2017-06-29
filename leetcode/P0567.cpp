// https://leetcode.com/problems/permutation-in-string/#/description
// 567. Permutation in String

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> expected(26), test(26);
        for (char c: s1) {
            expected[c-'a']++;
        }

        const int M = s1.length(), N = s2.length();
        for (int i = 0; i < N; i++) {
            test[s2[i]-'a']++;
            if (i >= M) test[s2[i-M]-'a']--;
            if (test == expected) return true;
        }
        return false;
    }
};

int main() {
    Solution solution;
    string s1, s2;
    cin >> s1 >> s2;
    cout << solution.checkInclusion(s1, s2) << endl;
    return 0;
}
