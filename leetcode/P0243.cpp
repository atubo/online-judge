// https://leetcode.com/problems/shortest-word-distance/
// 243. Shortest Word Distance

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int pos1 = -1, pos2 = -1;
        int ans = INT_MAX;
        for (int i = 0; i < (int)words.size(); i++) {
            if (words[i] == word1) {
                if (pos2 != -1) ans = min(ans, i-pos2);
                pos1 = i;
            }
            if (words[i] == word2) {
                if (pos1 != -1) ans = min(ans, i-pos1);
                pos2 = i;
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    return 0;
}
