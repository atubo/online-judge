#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool canPermutePalindrome(string &s) {
        int cnt[256];
        memset(cnt, 0, sizeof(cnt));
        for (char c: s) {
            cnt[c]++;
        }
        int odd_cnt = 0;
        for (int i = 0; i < 256; i++) {
            odd_cnt += (cnt[i]&1);
        }
        return odd_cnt < 2;
    }
};

int main() {
    Solution solution;
    return 0;
}
