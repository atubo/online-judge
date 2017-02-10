#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <strings.h>
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        sort(wordDict.begin(), wordDict.end());
        const int N = s.length();
        vector<vector<vector<int> > >dp(N);
        for (int i = 0; i < N; i++) {
            dp[i].resize(N);
        }

        for (int i = 0; i < N; i++) {
            if (inDict(s.substr(i, 1), wordDict)) {
                dp[i][i].push_back(i+1);
            }
        }

        for (int len = 2; len <= N; len++) {
            for (int i = 0; i <= N-len; i++) {
                int j = i + len - 1;
                if (inDict(s.substr(i, len), wordDict)) {
                    dp[i][j].push_back(j+1);
                }
                for (int k = i; k <= j-1; k++) {
                    if (!dp[i][k].empty() && !dp[k+1][j].empty()) {
                        dp[i][j].push_back(k+1);
                    }
                }
            }
        }
        vector<vector<set<string> > > dp2(N);
        for (int i = 0; i < N; i++) {
            dp2[i].resize(N);
        }
        set<string> resultSet = build(dp, s, 0, s.length()-1, dp2);
        vector<string> result(resultSet.begin(), resultSet.end());
        return result;
    }

    bool inDict(const string& s, const vector<string>& wordDict) {
        return binary_search(wordDict.begin(), wordDict.end(), s);
    }

    set<string> build(const vector<vector<vector<int> > >& dp, const string& s,
                      int p, int q,
                      vector<vector<set<string> > >& dp2) {
        if (!dp2[p][q].empty()) return dp2[p][q];
        set<string>& result = dp2[p][q];

        for (int k: dp[p][q]) {
            if (k == q + 1) {
                result.insert(s.substr(p, q-p+1));
            } else {
                auto left  = build(dp, s, p, k-1, dp2);
                auto right = build(dp, s, k, q, dp2);
                for (auto& l: left) {
                    for (auto& r: right) {
                        result.insert(l + " " + r);
                    }
                }
            }
        }
        return result;
    }
};

int main() {
    Solution solution;
    string s;
    cin >> s;
    int N;
    cin >> N;
    vector<string> wordDict;
    for (int i = 0; i < N; i++) {
        string word;
        cin >> word;
        wordDict.push_back(word);
    }
    vector<string> result = solution.wordBreak(s, wordDict);
    for (auto w: result) {
        cout << w << endl;
    }
    return 0;
}
