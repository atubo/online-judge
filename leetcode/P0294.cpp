// https://leetcode.com/problems/flip-game-ii/#/description
// 294. Flip Game II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canWin(string s) {
        const int N = s.length();
        vector<int> grundy(N+1);
        for (int i = 2; i <= N; i++) {
            set<int> s;
            for (int j = 2; j <= i; j++) {
                s.insert(grundy[j-2] ^ grundy[i-j]);
            }
            int g = 0;
            for (int k = 0; k <= N; k++) {
                if (s.count(k) == 0) {
                    g = k;
                    break;
                }
            }
            grundy[i] = g;
        }

        vector<int> cons;
        int p = 0, q = 0;
        while(true) {
            while (p < N && s[p] != '+') p++;
            if (p == N) break;
            q = p + 1;
            while (q < N && s[q] == '+') q++;
            cons.push_back(q-p);
            p = q;
        }

        int g = 0;
        for (int x: cons) {
            g ^= grundy[x];
        }

        return g != 0;
    }
};

int main() {
    Solution solution;
    solution.canWin("xxxxxxxxxxxxxxxxxxxxxxxxxxx");
    return 0;
}
