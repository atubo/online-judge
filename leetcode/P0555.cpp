// https://leetcode.com/problems/split-concatenated-strings/description/
// 555. Split Concatenated Strings

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string  splitLoopedString(vector<string>& strs) {
        const int N = strs.size();
        for (string& s: strs) {
            string sc = s;
            reverse(sc.begin(), sc.end());
            if (sc > s) s = sc;
        }
        string ret;
        for (int i = 0; i < N; i++) {
            string curr = build(strs, i);
            if (curr > ret) ret = curr;
            reverse(strs[i].begin(), strs[i].end());
            curr = build(strs, i);
            if (curr > ret) ret = curr;
            reverse(strs[i].begin(), strs[i].end());
        }
        return ret;
    }

    string build(const vector<string>& strs, int i) {
        const int N = strs.size();
        string ret;
        for (int p = 0; p < (int)strs[i].length(); p++) {
            string curr = strs[i].substr(p);
            for (int j = 1; j < N; j++) {
                curr += strs[(i+j)%N];
            }
            curr += strs[i].substr(0, p);
            if (curr > ret) ret = curr;
        }
        return ret;
    }
};

int main() {
    int N;
    cin >> N;
    vector<string> strs;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        strs.push_back(s);
    }
    Solution solution;
    cout << solution.splitLoopedString(strs) << endl;
    return 0;
}
