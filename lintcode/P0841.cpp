// https://www.lintcode.com/problem/string-replace/description
// 841. String Replace

#include <bits/stdc++.h>
using namespace std;

class Solution {
    const int SEED = 33;
    const int MOD = 1000000007;

    int str_hash(const string &s) {
        int ans = 0;
        for (char c : s) {
            ans = (1LL * ans * SEED + c - 'a') % MOD;
        }
        return ans;
    }
public:
    string stringReplace(vector<string> &a, vector<string> &b,
                         string &s) {
        vector<int> ahash;
        int maxlen = -1;
        for (const auto &w: a) {
            ahash.push_back(str_hash(w));
            maxlen = max(maxlen, (int)w.length());
        }
        maxlen = max(maxlen, (int)s.length());
        vector<int> shash;
        int ans = 0;
        shash.push_back(ans);
        for (char c: s) {
            ans = (1LL * ans * SEED + c - 'a') % MOD;
            shash.push_back(ans);
        }
        ans = 1;
        vector<int> base;
        base.push_back(ans);
        for (int i = 0; i < maxlen; i++) {
            ans = (1LL * ans * SEED) % MOD;
            base.push_back(ans);
        }

        string ret;
        for (int i = 0; i < (int)s.length(); i++) {
            int mx = -1, index = -1;
            for (int j = 0; j < (int)a.size(); j++) {
                int len_a = a[j].length();
                if (i + len_a <= (int)s.length()) {
                    int hs = ((1LL*shash[i+len_a] -
                             1LL*base[len_a]*shash[i]) % MOD + MOD) % MOD;
                    int ha = (ahash[j]) % MOD;
                    if (hs == ha && len_a > mx) {
                        mx = len_a;
                        index = j;
                    }
                }
            }
            if (mx != -1) {
                ret += b[index];
                i += mx - 1;
            } else {
                ret.push_back(s[i]);
            }
        }
        return ret;
    }
};

int main() {
    int n;
    cin >> n;
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<string> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    string s;
    cin >> s;
    Solution solution;
    cout << solution.stringReplace(a, b, s) << endl;

    return 0;
}
