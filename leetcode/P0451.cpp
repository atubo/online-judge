// https://leetcode.com/problems/sort-characters-by-frequency/#/description
// 451. Sort Characters By Frequency

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string frequencySort(string s) {
        map<char, int> f;
        for (char c: s) {
            f[c]++;
        }
        map<int,string> g;
        for (const auto& p: f) {
            g[p.second].append(p.second, p.first);
        }
        string ret;
        for (auto it = g.rbegin(); it != g.rend(); it++) {
            ret += it->second;
        }
        return ret;
    }
};

int main() {
    Solution solution;
    string s;
    cin >> s;
    cout << solution.frequencySort(s) << endl;
    return 0;
}
