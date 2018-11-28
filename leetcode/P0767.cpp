// https://leetcode.com/problems/reorganize-string/
// 767. Reorganize String

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reorganizeString(string S) {
        const int n = S.length();
        string ret(n, '\0');
        process(S);
        for (int i = 0; i < n; i++) {
            if (2*i < n) ret[2*i] = S[i];
            else {
                if (n&1) ret[(2*i)%n] = S[i];
                else ret[(2*i)%n+1] = S[i];
            }
        }
        for (int i = 0; i < n-1; i++) {
            if (ret[i] == ret[i+1]) {
                ret.clear();
                break;
            }

        }
        return ret;
    }

    void process(string &s) {
        const int n = s.length();
        vector<int> freq(256);
        map<int, set<char>> toCharSet;
        for (char c: s) {
            freq[c]++;
        }
        for (int c = 0; c < 256; c++) {
            if (freq[c] > 0) {
                toCharSet[freq[c]].insert(c);
            }
        }
        int p = n-1;
        for (auto it = toCharSet.begin(); it != toCharSet.end(); ++it) {
            int f = it->first;
            for (char c: it->second) {
                for (int i = 0; i < f; i++) {
                    s[p--] = c;
                }
            }
        }
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    cout << solution.reorganizeString(s) << endl;
    return 0;
}
