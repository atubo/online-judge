// https://leetcode.com/problems/custom-sort-string/
// 791. Custom Sort String

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string customSortString(string S, string T) {
        vector<bool> vis(26);
        vector<int> cnt(26);
        for (char c: T) {
            cnt[c-'a']++;
        }
        string ret;
        for (char c: S) {
            for (int i = 0; i < cnt[c-'a']; i++) {
                ret.push_back(c);
            }
            vis[c-'a'] = true;
        }
        for (int i = 0; i < 26; i++) {
            if (!vis[i]) {
                for (int j = 0; j < cnt[i]; j++) {
                    ret.push_back(i+'a');
                }
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
