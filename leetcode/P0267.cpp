// https://leetcode.com/problems/palindrome-permutation-ii/#/description
// 267. Palindrome Permutation II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> generatePalindromes(string s) {
        const int N = s.length();
        int freq[128] = {0};
        for (char c: s) {
            freq[int(c)]++;
        }
        vector<string> ret;
        int odd = 0;
        for (int i = 0; i < 128; i++) {
            odd += (freq[i] & 1);
        }
        if (odd > 1) return ret;

        string curr(N, '\0');
        solve(freq, 0, N, curr, ret);
        return ret;
    }

    void solve(int* freq, int pos, int N, string& curr, vector<string>& ret) {
        if (N % 2 == 0 && pos >= N/2) {
            ret.push_back(curr);
            return;
        }
        if (N % 2 == 1 && pos == N/2) {
            for (int i = 0; i < 128; i++) {
                if (freq[i] == 1) {
                    curr[pos] = char(i);
                    ret.push_back(curr);
                    break;
                }
            }
            return;
        }

        for (int i = 0; i < 128; i++) {
            if (freq[i] >= 2) {
                curr[pos] = curr[N-1-pos] = char(i);
                freq[i] -= 2;
                solve(freq, pos+1, N, curr, ret);
                freq[i] += 2;
            }
        }
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    auto ret = solution.generatePalindromes(s);
    for (auto x: ret) {
        cout << x << endl;
    }
    return 0;
}
