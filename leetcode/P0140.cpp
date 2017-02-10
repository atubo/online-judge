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
        vector<vector<int> > dp(N);
        for (int i = 0; i < N; i++) {
            dp[i].resize(N, -1);
        }

        for (int i = 0; i < N; i++) {
            if (inDict(s.substr(i, 1), wordDict)) {
                dp[i][i] = i + 1;
            }
        }

        for (int len = 2; len <= N; len++) {
            for (int i = 0; i <= N-len; i++) {
                int j = i + len - 1;
                if (inDict(s.substr(i, len), wordDict)) {
                    dp[i][j] = j + 1;
                }
                for (int k = i; k <= j-1; k++) {
                    if (dp[i][k] >= 0 && dp[k+1][j] >= 0) {
                        dp[i][j] = k + 1;
                        break;
                    }
                }
            }
        }
        vector<string> result;
        build(dp, s, 0, s.length()-1, result);
        return result;
    }

    bool inDict(const string& s, const vector<string>& wordDict) {
        return binary_search(wordDict.begin(), wordDict.end(), s);
    }

    void build(const vector<vector<int> >& dp, const string& s,
               int p, int q, vector<string>& result) {
        if (dp[p][q] == q+1) {
            result.push_back(s.substr(p, q-p+1));
            return;
        }

        int k = dp[p][q];
        build(dp, s, p, k-1, result);
        build(dp, s, k, q, result);
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
