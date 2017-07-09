// https://leetcode.com/problems/shopping-offers/#/description
// 638. Shopping Offers

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special,
                       vector<int>& needs) {
        vector<PII> offer;
        const int N = price.size();
        for (int i = 0; i < N; i++) {
            vector<int> x(N);
            x[i] = 1;
            int k = encode(x);
            offer.push_back(make_pair(k, price[i]));
        }
        const int M = special.size();
        for (int i = 0; i < M; i++) {
            vector<int> x(N);
            for (int j = 0; j < N; j++) {
                x[j] = special[i][j];
            }
            int k = encode(x);
            offer.push_back(make_pair(k, special[i][N]));
        }
        unordered_map<int, int> dp;
        return solve(offer, encode(needs), dp);
    }

    int encode(const vector<int>& k) {
        int ret = 0;
        for (int i = 0; i < (int)k.size(); i++) {
            ret = ret * 7 + k[i];
        }
        return ret;
    }

    int dec(int key1, int key2) {
        int ret = 0;
        int d = 1;
        for (int i = 0; i < 6; i++) {
            int x = (key1 % 7) - (key2 % 7);
            if (x < 0) return -1;
            ret = ret + x * d;
            key1 = key1 / 7;
            key2 = key2 / 7;
            d *= 7;
        }
        return ret;
    }

    int solve(const vector<PII>& offer, int key, unordered_map<int, int>& dp) {
        if (dp.count(key) > 0) return dp[key];
        if (key == 0) return 0;

        int& ret = dp[key] = INT_MAX;

        for (const auto& o: offer) {
            int key2 = o.first;
            int price = o.second;
            int kn = dec(key, key2);
            if (kn >= 0) {
                int tmp = solve(offer, kn,dp);
                if (tmp != INT_MAX) {
                    ret = min(ret, price + tmp);
                }
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
