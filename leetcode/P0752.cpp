// https://leetcode.com/problems/open-the-lock/
// 752. Open the Lock

#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        vector<int> de(10000);
        for (const auto &s: deadends) {
            int x = convert(s);
            de[x] = true;
        }
        if (de[0]) return -1;
        queue<int> q;
        vector<int> dist(10000, -1);
        q.push(0);
        dist[0] = 0;
        int tx = convert(target);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            int d = dist[x];
            if (x == tx) return d;
            for (int k = 0; k < 4; k++) {
                for (int t = -1; t <= 1; t += 2) {
                    int y = move(x, k, t);
                    if (!de[y] && dist[y] == -1) {
                        q.push(y);
                        dist[y] = d + 1;
                    }
                }
            }
        }
        return -1;
    }

    int convert(const string &s) {
        int ret = 0;
        for (int i = 0; i < 4; i++) {
            ret = ret * 10 + s[i] - '0';
        }
        return ret;
    }

    int move(int x, int d, int t) {
        static const int P[4] = {1, 10, 100, 1000};
        int u = x / P[d];
        int v = x % P[d];
        int u1 = u / 10;
        int u2 = u % 10;
        int u3 = (u2 + 10 + t) % 10;
        return (u1*10 + u3) * P[d] + v;
    }
};

int main() {
    Solution solution;
    return 0;
}
