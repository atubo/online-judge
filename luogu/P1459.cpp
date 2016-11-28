// https://www.luogu.org/problem/show?pid=1459
#include <algorithm>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    typedef vector<vector<int> > Adj;
private:
    int N;
    vector<int> A;
public:
    Solution() {
        scanf("%d", &N);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
            A[i]--;
        }
    }

    int count(Adj& adj, int u, int v) {
        int ret = min(adj[u][v], adj[v][u]);
        adj[u][v] -= ret;
        adj[v][u] -= ret;
        return ret;
    }

    int countCircle(const Adj& adj) {
        assert(adj[0][1] == adj[1][2] && adj[1][2] == adj[2][0]);
        assert(adj[1][0] == adj[2][1] && adj[2][1] == adj[0][2]);
        assert(adj[0][1] == 0 || adj[1][0] == 0);
        return (adj[0][1] + adj[1][0]) * 2;
    }

    void solve() {
        vector<int> B = A;
        sort(B.begin(), B.end());
        Adj adj(3, vector<int>(3, 0));
        for (int i = 0; i < N; i++) {
            int a = A[i], b = B[i];
            adj[a][b]++;
        }
        int ret = 0;
        ret += count(adj, 0, 1);
        ret += count(adj, 0, 2);
        ret += count(adj, 1, 2);
        ret += countCircle(adj);
        cout << ret << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
