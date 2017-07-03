// https://leetcode.com/problems/minimum-genetic-mutation/#/description
// 433. Minimum Genetic Mutation

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
    using PII = pair<int, int>;
public:
    int minMutation(string start, string end, vector<string>& bank) {
        const int N = bank.size();
        vector<vector<int>> adj(N+1);
        int b = N, e = -1;
        for (int i = 0; i < N; i++) {
            if (bank[i] == end) e = i;
            if (bank[i] == start) b = i;
            for (int j = i+1; j < N; j++) {
                if (isMutation(bank[i], bank[j])) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        if (e == -1) return -1;
        if (b == N) {
            for (int i = 0; i < N; i++) {
                if (isMutation(bank[i], start)) {
                    adj[N].push_back(i);
                }
            }
        }

        return bfs(b, e, adj);
    }

    bool isMutation(const string& s, const string& t) {
        int diff = 0;
        for (int i = 0; i < 8; i++) {
            diff += (s[i] != t[i]);
        }
        return diff == 1;
    }

    int bfs(int b, int e, const vector<vector<int>>& adj) {
        queue<PII> q;
        vector<bool> visited(adj.size(), false);
        q.push(make_pair(b, 0));
        visited[b] = true;
        while (!q.empty()) {
            int u, d;
            tie(u, d) = q.front();
            q.pop();
            if (u == e) return d;
            for (int v: adj[u]) {
                if (!visited[v]) {
                    q.push(make_pair(v, d+1));
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution solution;
    string s, t, tmp;
    cin >> s >> t;
    getline(cin, tmp);
    auto bank = getStringVector();
    cout << solution.minMutation(s, t, bank) << endl;
    return 0;
}
