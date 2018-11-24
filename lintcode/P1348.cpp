#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int titleToNumber(string &s) {
        int ans = 0;
        for (char c: s) {
            ans = ans*26 + c - 'A' + 1;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    string s;
    cin >> s;
    cout << solution.titleToNumber(s) << endl;
    return 0;
}
