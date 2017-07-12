// https://leetcode.com/problems/course-schedule-ii/#/description
// 210. Course Schedule II

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    vector<int> findOrder(int N, vector<PII>& edges) {
        vector<int> d(N);
        vector<vector<int>> adj(N);
        for (const auto& e: edges) {
            d[e.first]++;
            adj[e.second].push_back(e.first);
        }
        queue<int> q;
        for (int i = 0; i < N; i++) {
            if (d[i] == 0) q.push(i);
        }

        vector<int> ret;
        while (!q.empty()) {
            int u = q.front();
            ret.push_back(u);
            q.pop();
            for (int v: adj[u]) {
                if (--d[v] == 0) q.push(v);
            }
        }
        if ((int)ret.size() != N) ret.clear();
        return ret;
    }
};

int main() {
    Solution solution;
    return 0;
}
