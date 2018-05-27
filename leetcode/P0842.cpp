// https://leetcode.com/problems/split-array-into-fibonacci-sequence/description/
// 842. Split Array into Fibonacci Sequence

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> splitIntoFibonacci(string s) {
        const int N = s.length();
        vector<int> ans;
        for (int i = 1; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                ans = solve(s, i, j);
                if (!ans.empty()) return ans;
            }
        }
        return ans;
    }

    bool invalidLeadingZero(const string &s, int p, int q) {
        int64_t x = stoll(s.substr(p, q-p));
        return (s[p] == '0' && !(x == 0 && q-p == 1));
    }

    vector<int> solve(const string &s, int p, int q) {
        const int N = s.length();
        vector<int> EMPTY;
        vector<int> ans;
        if (p > 10 || q - p > 10) return EMPTY;
        int64_t x = stoll(s.substr(0, p));
        int64_t y = stoll(s.substr(p, q-p));
        if (x > INT_MAX || y > INT_MAX) return EMPTY;
        if (invalidLeadingZero(s, 0, p) || invalidLeadingZero(s, p, q)) {
            return EMPTY;
        }
        ans.push_back(x);
        ans.push_back(y);
        p = q;
        while (p < N) {
            int64_t z = x + y;
            if (z > INT_MAX) return EMPTY;
            string t = to_string(z);
            q = p + t.length();
            if (q > N) return EMPTY;
            if (s.substr(p, q-p) != t) return EMPTY;
            ans.push_back(z);
            x = y;
            y = z;
            p = q;
        }
        return ans;
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    vector<int> ret = solution.splitIntoFibonacci(s);
    for (int x: ret) {
        printf("%d ", x);
    }
    printf("\n");
    return 0;
}

