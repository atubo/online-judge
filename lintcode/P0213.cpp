// https://www.lintcode.com/problem/string-compression/description
// 213. String Compression

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string compress(string &originalString) {
        string ret;
        const int n = originalString.length();
        int p = 0;
        while (p < n) {
            int q = p+1;
            while (q < n && originalString[q] == originalString[p]) q++;
            ret.push_back(originalString[p]);
            ret += to_string(q-p);
            p = q;
        }
        if ((int)ret.length() >= n) ret = originalString;
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
