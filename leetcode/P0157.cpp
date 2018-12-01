// https://leetcode.com/problems/read-n-characters-given-read4/
// 157. Read N Characters Given Read4

#include <bits/stdc++.h>
using namespace std;

int read4(char *buf);

class Solution {
public:
    int read(char *buf, int n) {
        int tot = 0;
        while (tot < n) {
            int sz = read4(buf+tot);
            tot += min(sz, n-tot);
            if (sz < 4) break;
        }
        return tot;
    }
};

int main() {
    return 0;
}
