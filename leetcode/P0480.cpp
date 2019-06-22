// https://leetcode.com/problems/sliding-window-median/
// 480. Sliding Window Median

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& A, int k) {
        const int n = A.size();
        vector<double> ret;
        if (n == 0) return ret;
        if (k == 1) {
            for (int i = 0; i < n; i++) ret.push_back(A[i]);
            return ret;
        }

        multiset<int> top, bot;
        vector<int> tmp;
        for (int i = 0; i < k; i++) tmp.push_back(A[i]);
        sort(tmp.begin(), tmp.end());
        for (int i = 0; i < k; i++) {
            if (i < k/2) bot.insert(tmp[i]);
            else top.insert(tmp[i]);
        }
        ret.push_back(calc(top, bot));

        for (int i = k; i < n; i++) {
            add(A[i], A[i-k], top, bot);
            ret.push_back(calc(top, bot));
        }

        return ret;
    }

    double calc(const multiset<int> &top, const multiset<int> &bot) {
        int x1 = *top.begin();
        int x2 = *bot.rbegin();
        if (top.size() != bot.size()) return x1;
        return (1.0*x1 + x2) / 2.0;
    }

    void add(int x1, int x0, multiset<int> &top, multiset<int> &bot) {
        if (top.find(x0) != top.end()) {
            top.erase(top.find(x0));
            int x2 = *bot.rbegin();
            if (x1 < x2) {
                bot.erase(bot.find(x2));
                bot.insert(x1);
                top.insert(x2);
            } else {
                top.insert(x1);
            }
        } else {
            bot.erase(bot.find(x0));
            int x2 = *top.begin();
            if (x1 > x2) {
                top.erase(top.find(x2));
                top.insert(x1);
                bot.insert(x2);
            } else {
                bot.insert(x1);
            }
        }
    }
};

int main() {
    Solution solution;
    vector<int> A{7, 0, 3, 9, 9, 9, 1, 7, 2, 3};
    auto ret = solution.medianSlidingWindow(A, 6);
    for (double x: ret) {
        printf("%.3f ", x);
    }
    printf("\n");
    return 0;
}
