// https://leetcode.com/problems/integer-to-english-words/
// 273. Integer to English Words

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    const static int K = 1000;
    const static int M = K*K;
    const static int B = K*M;
    const vector<string> TENS{"", "", "Twenty", "Thirty", "Forty",
        "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const vector<string> TEENS{"Ten", "Eleven", "Twelve", "Thirteen",
        "Fourteen", "Fifteen", "Sixteen", "Seventeen",
        "Eighteen", "Nineteen"};
    const vector<string> SINGLE{"Zero", "One", "Two", "Three", "Four",
        "Five", "Six", "Seven", "Eight", "Nine"};
public:
    string numberToWords(int num) {
        if (num == 0) return SINGLE[0];
        return build(num);
    }

    string build(int x) {
        if (x == 0) return "";
        if (x >= B) {
            string ret = build(x/B) + " Billion";
            string suffix = build(x%B);
            concat(ret, suffix);
            return ret;
        } else if (x >= M) {
            string ret = build(x/M) + " Million";
            string suffix = build(x%M);
            concat(ret, suffix);
            return ret;
        } else if (x >= K) {
            string ret = build(x/K) + " Thousand";
            string suffix = build(x%K);
            concat(ret, suffix);
            return ret;
        } else if (x >= 100) {
            string ret = build(x/100) + " Hundred";
            string suffix = build(x%100);
            concat(ret, suffix);
            return ret;
        } else if (x >= 20) {
            string ret = TENS[x/10];
            string suffix = build(x%10);
            concat(ret, suffix);
            return ret;
        } else if (x >= 10) {
            string ret = TEENS[x-10];
            return ret;
        } else {
            return SINGLE[x];
        }
    }

    void concat(string &ret, const string &suffix) {
        if (!suffix.empty()) ret += " " + suffix;
    }
};

int main() {
    Solution solution;
    return 0;
}
