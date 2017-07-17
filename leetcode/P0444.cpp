// https://leetcode.com/problems/sequence-reconstruction/#/description
// 444. Sequence Reconstruction

#include "BinaryTree.h"
#include "Graph.h"
#include "LinkedList.h"
#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool sequenceReconstruction(vector<int>& A, vector<vector<int>>& seqs_) {
        const int N = A.size();
        vector<vector<int>> seqs;
        for (const auto& v: seqs_) {
            if (v.size() >= 1) seqs.push_back(v);
        }
        if (seqs.empty()) return false;

        for (int i = 0; i < N; i++) A[i]--;
        vector<vector<int>> adj(N);
        vector<int> in(N);
        for (const auto& seq: seqs) {
            if (!isValid(seq[0]-1, N)) return false;
            for (int i = 0; i < (int)seq.size()-1; i++) {
                int u = seq[i], v = seq[i+1];
                u--; v--;
                if (!isValid(u, N) || !isValid(v, N)) return false;
                addEdge(u, v, adj, in);
            }
        }

        vector<int> ts = topoSort(adj, in);
        if ((int)ts.size() < N) return false;
        int maxLen = calcMaxLen(adj, ts);
        return maxLen == N && ts == A;
    }

    bool isValid(int u, int N) {
        return 0 <= u && u < N;
    }

    void addEdge(int u, int v, vector<vector<int>>& adj, vector<int>& in) {
        in[v]++;
        adj[u].push_back(v);
    }

    vector<int> topoSort(const vector<vector<int>>& adj, vector<int>& in) {
        const int N = adj.size();
        queue<int> q;
        for (int i = 0; i < N; i++) {
            if (in[i] == 0) q.push(i);
        }

        vector<int> ret;
        while (!q.empty()) {
            int u = q.front();
            ret.push_back(u);
            q.pop();
            for (int v: adj[u]) {
                if (--in[v] == 0) q.push(v);
            }
        }
        return ret;
    }

    int calcMaxLen(const vector<vector<int>>& adj, const vector<int>& ts) {
        const int N = adj.size();
        vector<int> dp(N);
        int ret = 0;
        for (int i = ts.size()-1; i >= 0; i--) {
            int u = ts[i];
            dp[u] = 1;
            for (int v: adj[u]) {
                dp[u] = max(dp[u], 1 + dp[v]);
            }
            ret = max(ret, dp[u]);
        }
        return ret;
    }
};

int main() {
    auto A = getBracketedIntVector();
    int n;
    cin >> n;
    vector<vector<int>> seqs(n);
    string tmp;
    getline(cin, tmp);
    for (int i = 0; i < n; i++) {
        seqs[i] = getBracketedIntVector();
    }
    Solution solution;
    cout << solution.sequenceReconstruction(A, seqs) << endl;
    return 0;
}
