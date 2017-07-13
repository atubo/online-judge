// https://leetcode.com/problems/count-primes/#/description
// 204. Count Primes

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPrimes(int n) {
        if (n <= 1) return 0;
        vector<bool> prime(n+1, true);
        int ret = 0;
        for (int i = 2; i <= n; i++) {
            if (!prime[i]) continue;
            ret++;
            for (int j = 2; i*j <= n; j++) {
                prime[i*j] = false;
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
