// https://www.lintcode.com/problem/excel-sheet-column-title/description
// 1350. Excel Sheet Column Title

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    string convertToTitle(int n) {
        string ret;
        while (n) {
            ret.push_back(((25LL+n)%26)+'A');
            n = n/26 - (n%26==0);
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.convertToTitle(n) << endl;
    return 0;
}
