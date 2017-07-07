// https://leetcode.com/problems/count-of-range-sum/#/description
// 327. Count of Range Sum

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
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

    // get largest value with cumulative sum less than or equal to x;
    // for smallest, pass x-1 and add 1 to result
    int getind(int x) {
        int idx = 0, mask = N;
        while(mask && idx < N) {
            int t = idx + mask;
            if(x >= tree[t]) {
                idx = t;
                x -= tree[t];
            }
            mask >>= 1;
        }
        return idx;
    }

private:
    int64_t* tree;
    const int N;
};

class Solution {
public:
    int countRangeSum(vector<int>& A, int lo, int hi) {
        int N = A.size();
        vector<int64_t> ps(N+1);
        for (int i = 1; i <= N; i++) {
            ps[i] = ps[i-1] + A[i-1];
        }
        vector<int64_t> pts = ps;
        sort(pts.begin(), pts.end());
        pts.erase(unique(pts.begin(), pts.end()), pts.end());

        BIT st(1048576);
        int ret = 0;
        for (int i = 0; i <= N; i++) {
            int64_t x = ps[i];
            int idx1 = lowerIdx(pts, x - hi) + 1;
            int idx2 = upperIdx(pts, x - lo);
            ret += st.get(idx2) - st.get(idx1-1);
            st.set(lowerIdx(pts, x) + 1, 1);
        }
        return ret;
    }

    int lowerIdx(const vector<int64_t>& pts, int64_t x) {
        return lower_bound(pts.begin(), pts.end(), x) - pts.begin();
    }

    int upperIdx(const vector<int64_t>& pts, int64_t x) {
        return upper_bound(pts.begin(), pts.end(), x) - pts.begin();
    }
};

int main() {
    auto v = getVector();
    int lo, hi;
    cin >> lo >> hi;
    Solution solution;
    cout << solution.countRangeSum(v, lo, hi) << endl;
    return 0;
}
