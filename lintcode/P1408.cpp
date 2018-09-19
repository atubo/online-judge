// https://www.lintcode.com/problem/gas-station-ii/description
// 1408. Gas Station II

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int getTimes(int target, int original, vector<int> &distance,
                 vector<int> &apply) {
        while (!distance.empty() && distance.back() > target) {
            distance.pop_back();
            apply.pop_back();
        }
        if (distance.empty() || distance.back() < target) {
            distance.push_back(target);
            apply.push_back(0);
        }
        const int n = distance.size();
        int remain = original;
        int ans = 0;
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 0; i < n; i++) {
            int delta = (i == 0 ? distance[i]: distance[i]-distance[i-1]);
            remain -= delta;
            if (remain >= 0) {
                pq.push(apply[i]);
            } else {
                while (remain < 0) {
                    if (pq.empty()) return -1;
                    int c = pq.top();
                    pq.pop();
                    ans++;
                    remain += c;
                }
                pq.push(apply[i]);
            }
        }
        return ans;
    }
};

int main() {
    int target, original;
    cin >> target >> original;
    string tmp;
    getline(cin, tmp);
    auto d = getBracketedIntVector();
    auto a = getBracketedIntVector();
    Solution solution;
    cout << solution.getTimes(target, original, d, a) << endl;
    return 0;
}
