// https://leetcode.com/problems/random-pick-with-weight/
// 528. Random Pick with Weight

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    Solution(vector<int> w): ps_(w.size()), gen_(rd_()) {
        partial_sum(w.begin(), w.end(), ps_.begin());
    }

    int pickIndex() {
        uniform_int_distribution<> dis(1, ps_.back());
        int x = dis(gen_);
        return lower_bound(ps_.begin(), ps_.end(), x) - ps_.begin();
    }
private:
    vector<int> ps_;
    random_device rd_;
    mt19937 gen_;
};

int main() {
    auto v = getBracketedIntVector();
    int tot = 0;
    for (int x: v) tot += x;
    Solution solution(v);
    vector<int> cnt(v.size());
    for (int i = 0; i < 1000; i++) {
        int x = solution.pickIndex();
        printf("%d\n", x);
        if (x < 0 || x >= (int)cnt.size()) {
            printf("error\n");
            return 0;
        }
        cnt[x]++;
    }

    printf("====\n");
    for (int i = 0; i < (int)v.size(); i++) {
        printf("%.2f %.2f\n", double(v[i])/tot, double(cnt[i])/1000);
    }
    return 0;
}
