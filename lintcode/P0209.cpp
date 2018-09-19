// https://www.lintcode.com/problem/first-unique-character-in-a-string/description
// 209. First Unique Character in a String

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    char firstUniqChar(string &str) {
        int cnt[256] = {0};
        for (char c: str) {
            cnt[c]++;
        }
        for (char c: str) {
            if (cnt[c] == 1) return c;
        }
        return 0;
    }
};

int main() {
    Solution solution;
    return 0;
}
