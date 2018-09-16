// https://www.lintcode.com/problem/origami/description
// 842. Origami

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string getString(int n) {
        string pat = "";
        for (int i = 1; i <= n; i++) {
            pat = pat + "0" + reverse(pat);
        }
        return pat;
    }

    string reverse(const string &pat) {
        if (pat.empty()) return pat;
        string ret = pat;
        std::reverse(ret.begin(), ret.end());
        for (char &c: ret) {
            c = '1' - c + '0';
        }
        return ret;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.getString(n) << endl;
    return 0;
}
