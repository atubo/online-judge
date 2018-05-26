// https://leetcode.com/problems/push-dominoes/description/
// 838. Push Dominoes

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string pushDominoes(string dominos) {
        const int N = dominos.length();
        string res = dominos;
        int p = 0;
        while (true) {
            while (p < N && dominos[p] == 'L') p++;
            if (p >= N) break;
            int q = p + 1;
            while (q < N && dominos[q] == '.') q++;
            if (q == N || dominos[q] == 'R') {
                for (int i = p; i < q; i++) res[i] = dominos[p];
                p = q;
                continue;
            }
            if (dominos[p] == '.') {
                for (int i = p; i < q; i++) res[i] = 'L';
                p = q + 1;
                continue;
            }
            for (int i = p; i <= (p+q-1)/2; i++) res[i] = 'R';
            for (int i = (p+q)/2+1; i <= q; i++) res[i] = 'L';
            p = q + 1;
        }
        return res;
    }
};

int main() {
    string s;
    cin >> s;
    Solution solution;
    cout << solution.pushDominos(s) << endl;
    return 0;
}
