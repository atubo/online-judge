// https://leetcode.com/problems/shopping-offers/#/description
// 638. Shopping Offers

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special,
                       vector<int>& needs) {
        unordered_map<int, int> dp;
        return solve(price, special, needs, dp);
    }

    int encode(const vector<int>& k) {
        int ret = 0;
        for (int i = k.size()-1; i >= 0; i--) {
            ret = ret * 7 + k[i];
        }
        return ret;
    }

    int solve(const vector<int>& price, const vector<vector<int>>& special,
              vector<int>& needs, unordered_map<int, int>& dp) {
        int key = encode(needs);
        if (dp.count(key) > 0) return dp[key];
        if (*max_element(needs.begin(), needs.end()) == 0) return 0;

        int& ret = dp[key] = INT_MAX;

        const int N = price.size();
        for (int i = 0; i < N; i++) {
            if (needs[i] > 0) {
                needs[i]--;
                ret = min(ret, price[i] + solve(price, special, needs, dp));
                needs[i]++;
            }
        }

        const int M = special.size();
        for (int i = 0; i < M; i++) {
            vector<int> next(N);
            for (int j = 0; j < N; j++) {
                next[j] = needs[j] - special[i][j];
            }
            if (*min_element(next.begin(), next.end()) >= 0) {
                ret = min(ret, special[i][N] + solve(price, special, next, dp));
            }
        }
        return ret;
    }
};

int main() {
    auto price = getBracketedIntVector();
    int n;
    cin >> n;
    string s;
    getline(cin, s);
    vector<vector<int>> specials(n);
    for (int i = 0; i < n; i++) {
        specials[i] = getBracketedIntVector();
    }
    auto needs = getBracketedIntVector();

    Solution solution;
    cout << solution.shoppingOffers(price, specials, needs) << endl;
    return 0;
}
