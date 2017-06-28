// https://leetcode.com/problems/reverse-pairs/#/description
// 493. Reverse Pairs

#include "Util.h"
#include <bits/stdc++.h>

using namespace std;

class BIT {
public:
    // Note size needs to be power of 2
    BIT(int size): N(size) {
        tree = (int64_t*)malloc((size+1) * sizeof(int64_t));
        clear();
    }
    
    ~BIT() {
        free(tree);
        tree = NULL;
    }

    void clear() {
        memset(tree, 0, (N+1) * sizeof(int64_t));
    }

    // add v to value at x
    void set(int x, int v) {
        while(x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    // get cumulative sum up to and including x
    int64_t get(int x) const {
        int64_t res = 0;
        while(x) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }

    // get result for [x, y]
    int64_t get(int x, int y) const {
        return get(y) - (x > 1 ? get(x-1) : 0);
    }

private:
    int64_t* tree;
    const int N;
};

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        const int N = nums.size();
        vector<int64_t> A(N);
        copy(nums.begin(), nums.end(), A.begin());
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        BIT ft(65536);
        int res = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            int64_t x = nums[i];
            int j = upper_bound(A.begin(), A.end(), 2*x) - A.begin();
            res += (i - (j > 0 ? ft.get(j) : 0));
            j = lower_bound(A.begin(), A.end(), x) - A.begin();
            ft.set(j+1, 1);
        }
        return res;
    }
};

int main() {
    Solution solution;
    auto A = getVector();
    cout << solution.reversePairs(A) << endl;
    return 0;
}
