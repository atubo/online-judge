// https://www.luogu.org/problem/show?pid=1983
// P1983 车站分级

#include <cstdio>
#include <set>
#include <stack>
#include <vector>
using namespace std;

typedef set<int>::const_iterator Iter;

const int MAXN = 1010;
int station[MAXN];

class Solution {
public:
    int N, M;
    vector<vector<int> > adj;
    vector<vector<int> > in;
    vector<int> topo;  // topologically sorted result

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
        scanf("%d %d", &N, &M);
        adj.resize(N);
        in.resize(N);
        for (int i = 0; i < N; i++) {
            adj.reserve(N);
            in.reserve(N);
        }
        for (int i = 0; i < M; i++) {
            //set<int> s;
            int sz;
            scanf("%d", &sz);
            for (int j = 0; j < sz; j++) {
                int u;
                scanf("%d", &u);
                u--;
                //s.insert(u);
                station[j] = u;
            }
            int first = station[0];
            int last = station[sz-1];
            int p = 0;
            for (int j = first; j <= last; j++) {
                if (j == station[p]) {
                    p++;
                    continue;
                }
                for (int k = 0; k < sz; k++) {
                    adj[station[k]].push_back(j);
                    in[j].push_back(station[k]);
                }
#if 0
                if (s.count(j) == 0) {
                    for (Iter it = s.begin(); it != s.end(); ++it) {
                        adj[*it].push_back(j);
                        in[j].push_back(*it);
                    }
                }
#endif
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
            dp[u] = 1 + maxl;
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
