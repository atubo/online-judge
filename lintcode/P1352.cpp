// https://www.lintcode.com/problem/compare-version-numbers/description
// 1352. Compare Version Numbers

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int compareVersion(string &version1, string &version2) {
        int p = 0, q = 0;
        while (true) {
            int p2 = version1.find_first_of('.', p);
            int q2 = version2.find_first_of('.', q);
            int v1 = stoi(version1.substr(p, p2-p));
            int v2 = stoi(version2.substr(q, q2-q));
            if (v1 > v2) return 1;
            if (v1 < v2) return -1;
            if (p2 == string::npos && q2 == string::npos) return 0;
            if (p2 == string::npos) return -1;
            if (q2 == string::npos) return 1;
            p = p2 + 1;
            q = q2 + 1;
        }
        return 0;
    }
};

int main() {
    Solution solution;
    return 0;
}
