// https://www.lintcode.com/problem/tuple-multiply/description
// 933. Tuple Multiply

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long tupleMultiply(string &tuple, int n) {
        const int len = tuple.length();
        int i = 0;
        int64_t ans = 1;
        while (i < len) {
            ans *= parse(tuple, n, i);
            i++;
        }
        return ans;
    }

    int parse(const string &tuple, int n, int &i) {
        match(tuple, '(', i);
        int idx = 1;
        int ret = 1;
        while (true) {
            int x = parseInteger(tuple, i);
            if (idx++ == n) ret = x;
            if (peek(tuple, i) == ')')  break;
            match(tuple, ',', i);
        }
        match(tuple, ')', i);
        return ret;
    }

    void match(const string &s, char c, int &i) {
        assert(s[i] == c);
        i++;
    }

    int parseInteger(const string &s, int &i) {
        int ret = 0;
        int sgn = 1;
        if (peek(s, i) == '-') {
            sgn = -1;
            i++;
        }
        while (peek(s, i) >= '0' && peek(s, i) <= '9') {
            ret = ret * 10 + peek(s, i) - '0';
            i++;
        }
        return ret * sgn;
    }

    char peek(const string &s, int i) {
        return s[i];
    }
};

int main() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    Solution solution;
    cout << solution.tupleMultiply(s, n) << endl;
    return 0;
}
