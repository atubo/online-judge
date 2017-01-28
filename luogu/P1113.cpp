// https://www.luogu.org/problem/show?pid=1113
// P1113 杂务
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    int N;
    vector<vector<int> > adj;
    vector<vector<int> > in;
    vector<int> topo;  // topologically sorted result
    vector<int> len;

private:
    void topologicalSortUtil(int v, bool visited[],
                             stack<int> &order) {
        visited[v] = true;

        for (int i = 0; i < (int)adj[v].size(); i++) {
            int m = adj[v][i];
            if (!visited[m]) {
                topologicalSortUtil(m, visited, order);
            }
        }

        order.push(v);
    }

public:
    Solution() {
        scanf("%d", &N);
        adj.resize(N);
        in.resize(N);
        len.resize(N);
        for (int i = 0; i < N; i++) {
            int idx, l;
            scanf("%d %d", &idx, &l);
            len[i] = l;
            int x;
            while (true) {
                scanf("%d", &x);
                if (x == 0) break;
                in[i].push_back(x-1);
                adj[x-1].push_back(i);
            }
        }
    }

    void solve() {
        sort();
        vector<int> dp(N);
        int ans = 0;
        for (int i = 0; i < N; i++) {
            int u = topo[i];
            int maxl = 0;
            for (int j = 0; j < (int)in[u].size(); j++) {
                int v = in[u][j];
                maxl = max(maxl, dp[v]);
            }
            dp[u] = maxl + len[u];
            ans = max(ans, dp[u]);
        }

        printf("%d\n", ans);
    }

    void sort() {
        topo.resize(N);

        stack<int> order;
        bool visited[N];
        for (int i = 0; i < N; i++) {
            visited[i] = false;
        }

        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, order);
            }
        }

        int i = 0;
        while (!order.empty()) {
            topo[i++] = order.top();
            order.pop();
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
