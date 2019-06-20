// https://leetcode.com/problems/valid-number/
// 65. Valid Number

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    bool isNumber(string s) {
        const int n = s.length();
        int p = 0, q = n-1;
        while (p < n && s[p] == ' ') p++;
        if (p == n) return false;
        while (q > p && s[q] == ' ') q--;
        s = s.substr(p, q-p+1);

        auto pos = s.find_first_of('e');
        if (pos != string::npos) {
            return parseFixed(s.substr(0, pos)) &&
                parseInt(s.substr(pos+1));
        }
        return parseFixed(s);
    }
private:
    bool parseFixed(const string &s) {
        const size_t n = s.length();
        size_t pos = 0;
        if (s[0] == '+' || s[0] == '-') {
            pos++;
        }
        auto q = s.find_first_of('.');
        if (q != string::npos) {
            if (q == pos && q+1 == n) return false;
            return (q == pos || parseInt(s.substr(pos, q-pos))) &&
                (q+1 == n || parseInt(s.substr(q+1), false));
        }
        return parseInt(s.substr(pos));
    }

    bool parseInt(const string &s, bool signok=true) {
        if (s.empty()) return false;
        int pos = 0;
        if (s[0] == '+' || s[0] == '-') {
            if (!signok) return false;
            pos++;
        }
        if (pos == (int)s.length()) return false;
        for (int i = pos; i < (int)s.length(); i++) {
            if (s[i] < '0' || s[i] > '9') return false;
        }
        return true;
    }
};

int main() {
    Solution solution;
    cout << solution.isNumber(".-4") << endl;
    return 0;
}
