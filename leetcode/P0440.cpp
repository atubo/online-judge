// 440. K-th Smallest in Lexicographical Order

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthNumber(int n, int k) {
        int m = 0, prefix = 0;
        for (int d = 0; d <= 9; d++) {
            for (int i = 0; i <= 9; i++) {
                int p2 = prefix * 10 + i;
                int cnt = count(p2, n);
                if (m + cnt >= k) {
                    prefix = p2;
                    break;
                }
                m += cnt;
            }
            if (m + 1 == k) return prefix;
            m++;
        }
        assert(0);
        return 0;
    }

    int count(int64_t x, int64_t n) {
        if (x == 0) return 0;
        int64_t d = 1;
        int64_t ret = 0;
        while (x <= n) {
            ret += min(n - x + 1, d);
            x *= 10;
            d *= 10;
        }
        return ret;
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    Solution solution;
    cout << solution.findKthNumber(n, k) << endl;
    return 0;
}
