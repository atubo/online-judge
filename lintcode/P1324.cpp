// https://www.lintcode.com/problem/count-primes/description
// 1324. Count Primes

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int countPrimes(int n) {
        n--;
        if (n <= 1) return 0;
        vector<bool> is_prime(n, true);
        int ret = 0;
        for (int i = 2; i <= n; i++) {
            if (is_prime[i]) {
                ret++;
                for (int j = 2*i; j <= n; j+=i) {
                    is_prime[j] = false;
                }
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.countPrimes(n) << endl;
    return 0;
}
