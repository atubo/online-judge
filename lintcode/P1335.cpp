// https://www.lintcode.com/problem/repeated-dna-sequences/description
// 1335. Repeated DNA Sequences

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    const char DNA[4] = {'A', 'C', 'G', 'T'};

    string decode(int x) {
        string ret(10, '\0');
        for (int i = 0; i < 10; i++) {
            ret[9-i] = DNA[x&3];
            x >>= 2;
        }
        return ret;
    }
public:
    vector<string> findRepeatedDnaSequences(string &s) {
        int id[26];
        id[0] = 0; id[2] = 1; id[6] = 2; id[19] = 3;
        unordered_map<int, int> cnt;
        vector<string> ret;
        const int n = s.length();
        if (n < 10) return ret;
        int h = 0;
        for (int i = 0; i < 10; i++) {
            h = (h << 2) | id[s[i]-'A'];
        }
        cnt[h]++;
        const int mask = (1 << 20) - 1;
        for (int i = 10; i < n; i++) {
            h = ((h << 2) & mask) | id[s[i]-'A'];
            cnt[h]++;
        }
        for (auto it = cnt.begin(); it != cnt.end(); ++it) {
            if (it->second > 1) {
                ret.push_back(decode(it->first));
            }
        }
        return ret;
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    auto ret = solution.findRepeatedDnaSequences(s);
    for (auto x: ret) {
        cout << x << endl;
    }
    return 0;
}
