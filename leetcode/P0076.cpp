// https://leetcode.com/problems/minimum-window-substring/
// 76. Minimum Window Substring

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        const int n = s.length();
        vector<int> freqt(256), freqs(256);
        int req = process(t, freqt);
        int p = 0, q = 0;
        int pm = 0, qm = 0, lenm = INT_MAX;
        while (true) {
            while (p < n && req > 0) {
                char c = s[p++];
                freqs[c]++;
                if (freqs[c] == freqt[c]) req--;
            }
            if (p == n && req > 0) break;

            while (req == 0) {
                if (p - q < lenm) {
                    lenm = p - q;
                    pm = p;
                    qm = q;
                }
                char c = s[q++];
                if (freqs[c] == freqt[c]) req++;
                freqs[c]--;
            }
        }
        string ret;
        if (lenm < INT_MAX) ret = s.substr(qm, pm-qm);
        return ret;
    }

    int process(const string &s, vector<int> &freq) {
        int ans = 0;
        for (char c: s) {
            if (freq[c] == 0) ans++;
            freq[c]++;
        }
        return ans;
    }
};


int main() {
    string s, t;
    cin >> s >> t;
    Solution solution;
    cout << solution.minWindow(s, t) << endl;
    return 0;
}
