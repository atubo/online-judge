#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        m--; n--;
        return (int)(fact(m+n)/(fact(m)*fact(n)) + 0.5);
    }

    double fact(int n) {
        double ret = 1;
        for (int i = 2; i <= n; i++) ret *= i;
        return ret;
    }
};

int main() {
    Solution solution;
    int m, n;
    cin >> m >> n;
    cout << solution.uniquePaths(m, n) << endl;
    return 0;
}
