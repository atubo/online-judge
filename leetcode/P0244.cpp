// https://leetcode.com/problems/shortest-word-distance-ii/
// 244. Shortest Word Distance II

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class WordDistance {
public:
    WordDistance(vector<string> &words) {
        for (int i = 0; i < (int)words.size(); i++) {
            pos_[words[i]].push_back(i);
        }
    }
    int shortest(string word1, string word2) {
        auto l1 = pos_[word1];
        auto l2 = pos_[word2];
        int ans = INT_MAX;
        for (int x: l1) {
            auto it = upper_bound(l2.begin(), l2.end(), x);
            if (it != l2.end()) ans = min(ans, *it-x);
        }
        for (int x: l2) {
            auto it = upper_bound(l1.begin(), l1.end(), x);
            if (it != l1.end()) ans = min(ans, *it-x);
        }
        return ans;
    }
private:
    map<string, vector<int>> pos_;
};

int main() {
    return 0;
}
