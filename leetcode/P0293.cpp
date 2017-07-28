// https://leetcode.com/problems/flip-game/tabs/description
// 293. Flip Game

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        const int N = s.length();
        vector<string> ret;
        for (int i = 0; i <= N-2; i++) {
            if (s[i] == '+' && s[i+1] == '+') {
                s[i] = s[i+1] = '-';
                ret.push_back(s);
                s[i] = s[i+1] = '+';
            }
        }
        return ret;
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    auto ret = solution.generatePossibleNextMoves(s);
    for (auto x: ret) {
        cout << x << endl;
    }
    return 0;
}
