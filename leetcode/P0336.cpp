// https://leetcode.com/problems/palindrome-pairs/
// 336. Palindrome Pairs

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string> &words) {
        map<string, int> toId;
        const int n = words.size();
        for (int i = 0; i < n;  i++) {
            toId[words[i]] = i;
        }
        vector<vector<int>> ret;
        for (int i = 0; i < n; i++) {
            check(words, i, toId, ret);
        }
        sort(ret.begin(), ret.end());
        ret.erase(unique(ret.begin(), ret.end()), ret.end());
        return ret;
    }

    void check(const vector<string> &words, int idx,
               const map<string, int> &toId,
               vector<vector<int>> &ret) {
        string word = words[idx];
        if (word.empty()) return;
        const int n = word.length();
        for (int i = n-1; i >= n/2; i--) {
            int ok = true;
            for (int j = 1; j <= (n-1-i); j++) {
                if (word[i-j] != word[i+j]) {
                    ok = false;
                    break;
                }

            }
            if (ok) {
                int x = 2*i+1-n;
                string right = word.substr(0, x);
                reverse(right.begin(), right.end());
                if (toId.count(right) > 0 &&
                    toId.at(right) != idx) {
                    ret.push_back({idx, toId.at(right)});
                }
            }
        }
        for (int i = 0; i <= (n-1)/2; i++) {
            int ok = true;
            for (int j = 1; j <= i; j++) {
                if (word[i-j] != word[i+j]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                int x = 2*i;
                string left = word.substr(x+1);
                reverse(left.begin(), left.end());
                if (toId.count(left) > 0 &&
                    toId.at(left) != idx) {
                    ret.push_back({toId.at(left), idx});
                }
            }
        }
        for (int i = n; i >= (n+1)/2; i--) {
            int ok = true;
            for (int j = 0; j <= n-1-i; j++) {
                if (word[i+j] != word[i-j-1]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                int x = 2*i-n;
                string right = word.substr(0, x);
                reverse(right.begin(), right.end());
                if (toId.count(right) > 0 &&
                    toId.at(right) != idx) {
                    ret.push_back({idx, toId.at(right)});
                }
            }
        }
        for (int i = 0; i <= n/2; i++) {
            int ok = true;
            for (int j = 0; j <= i-1; j++) {
                if (word[i+j] != word[i-j-1]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                int x = 2*i-1;
                string left = word.substr(x+1);
                reverse(left.begin(), left.end());
                if (toId.count(left) > 0 &&
                    toId.at(left) != idx) {
                    ret.push_back({toId.at(left), idx});
                }
            }
        }
    }
};


int main() {
#if 0
    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }
#endif
    vector<string> words = {"a", ""};
    Solution solution;
    auto ret = solution.palindromePairs(words);
    for (auto v: ret) {
        for (int x: v) {
            printf("%d ", x);
        }
        printf("\n");
    }
    return 0;
}
