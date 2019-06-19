// https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/
// 340. Longest Substring with At Most K Distinct Characters

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if (k == 0) return 0;
        int cnt[256] = {0};
        const int n = s.length();
        int ret = 0;
        int p = 0, q = -1;
        int nc = 0;
        while (true) {
            q++;
            while (q < n) {
                int c = s[q];
                cnt[c]++;
                if (cnt[c] == 1) nc++;
                if (nc > k) break;
                q++;
            }
            ret = max(ret, q-p);
            if (q >= n) break;
            while (nc > k) {
                int c = s[p++];
                cnt[c]--;
                if (cnt[c] == 0) nc--;
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    cout << solution.lengthOfLongestSubstringKDistinct("aba", 1) << endl;
    return 0;
}
