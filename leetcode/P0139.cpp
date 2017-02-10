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
    bool wordBreak(string s, vector<string>& wordDict) {
        sort(wordDict.begin(), wordDict.end());
        const int N = s.length();
        vector<vector<bool> > dp(N);
        for (int i = 0; i < N; i++) {
            dp[i].resize(N);
        }

        for (int i = 0; i < N; i++) {
            dp[i][i] = inDict(s.substr(i, 1), wordDict);
        }

        for (int len = 2; len <= N; len++) {
            for (int i = 0; i <= N-len; i++) {
                int j = i + len - 1;
                dp[i][j] = inDict(s.substr(i, len), wordDict);
                for (int k = i; k <= j-1; k++) {
                    dp[i][j] = dp[i][j] || (dp[i][k] && dp[k+1][j]);
                }
            }
        }
        return dp[0][N-1];
    }

    bool inDict(const string& s, const vector<string>& wordDict) {
        return binary_search(wordDict.begin(), wordDict.end(), s);
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
    cout << solution.wordBreak(s, wordDict) << endl;
    return 0;
}
