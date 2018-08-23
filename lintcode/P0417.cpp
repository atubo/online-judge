// https://www.lintcode.com/problem/valid-number/description
// 417. Valid Number

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isNumber(string &s) {
        const int n = s.length();
        int curr = 0, end = s.length();
        while (curr < n && isspace(s[curr])) curr++;
        while (end > 0 && isspace(s[end-1])) end--;
        if (peek(s, curr, end) == '+' || peek(s, curr, end) == '-') curr++;
        bool integral_part = parseNumber(s, curr, end);
        bool floating_part = false;
        if (peek(s, curr, end) == '.') {
            curr++;
            floating_part = parseNumber(s, curr, end);
        }
        if (!integral_part && !floating_part) return false;
        if (peek(s, curr, end) == 'e' || peek(s, curr,end) == 'E') {
            curr++;
            if (peek(s, curr, end) == '+' || peek(s, curr,end) == '-') curr++;
            bool ok = parseNumber(s, curr, end);
            if (!ok) return false;
        }
        return curr == end;
    }

    bool parseNumber(const string &s, int &p, int q) {
        if (p == q || !isdigit(s[p])) return false;
        while (p < q && isdigit(s[p])) p++;
        return true;
    }

    char peek(const string &s, int p, int end) {
        return (p < end ? s[p] : '\0');
    }
};

int main() {
    string s;
    getline(cin, s);
    Solution solution;
    cout << solution.isNumber(s) << endl;
    return 0;
}
