// https://www.lintcode.com/problem/reverse-words-in-a-string-ii/description
// 927. Reverse Words in a String II

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string reverseWords(string &str) {
        string ret = str;
        const int n = str.length();
        int p = 0;
        while (p < n) {
            int q = p;
            while (q < n && ret[q] != ' ') q++;
            reverse(ret.begin()+p, ret.begin()+q);
            p = q + 1;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
