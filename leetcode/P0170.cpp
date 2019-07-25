// https://leetcode.com/problems/two-sum-iii-data-structure-design/
// 170. Two Sum III - Data structure design

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class TwoSum {
public:
    TwoSum() {}

    void add(int x) {
        d_[x]++;
        s_.insert(x);
    }

    bool find(int value) {
        for (auto it = s_.begin(); it != s_.end(); ++it) {
            int x = *it;
            int y = value - x;
            if ((y != x && d_.find(y) != d_.end()) ||
                (y == x && d_.find(y) != d_.end() && d_.at(y) > 1)) {
                return true;
            }
        }
        return false;
    }

private:
    map<int, int> d_;
    set<int> s_;
};

int main() {
    return 0;
}
