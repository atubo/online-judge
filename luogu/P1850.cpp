// https://www.luogu.org/problem/show?pid=1850
// 换教室
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

double dp[2001][2001][2];

class FloydWarshall {
public:
    FloydWarshall(const vector<vector<int> >& graph)
        :m_graph(graph), m_dist(graph)
    {
        int V = m_graph.size();

        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (m_dist[i][k] + m_dist[k][j] < m_dist[i][j]) {
                        m_dist[i][j] = m_dist[i][k] + m_dist[k][j];
                    }
                }
            }
        }
    }

    const vector<vector<int> > getDist() const {
        return m_dist;
    }
private:
    vector<vector<int> > m_graph;
    vector<vector<int> > m_dist;
};

class Solution {
    typedef vector<vector<int> > Adj;
private:
    int N, M, V, E;
    vector<int> C, D;
    vector<double> K;
    Adj adj;
public:
    Solution() {
        cin >> N >> M >> V >> E;
        C.resize(N);
        D.resize(N);
        K.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &C[i]);
            C[i]--;
        }
        for (int i = 0; i < N; i++) {
            scanf("%d", &D[i]);
            D[i]--;
        }
        for (int i = 0; i < N; i++) {
            scanf("%lf", &K[i]);
        }
        adj.resize(V, vector<int>(V, 123456789));
        for (int i = 0; i < E; i++) {
            int a, b, w;
            scanf("%d %d %d", &a, &b, &w);
            a--; b--;
            adj[a][b] = min(adj[a][b], w);
            adj[b][a] = adj[a][b];
        }
        for (int i = 0; i < V; i++) {
            adj[i][i] = 0;
        }
    }

    void solve() {
        const double INF = 1e12;
        FloydWarshall fw(adj);
        vector<vector<int> > dist = fw.getDist();
        // initialize all to INF
        for (int i = 0; i < 2001; i++) {
            for (int j = 0; j < 2001; j++) {
                dp[i][j][0] = dp[i][j][1] = INF;
            }
        }

        dp[0][0][0] = 0;
        dp[0][1][1] = 0;
        for (int i = 1; i < N; i++) {
            int d_c0c1 = dist[C[i-1]][C[i]];
            int d_c0d1 = dist[C[i-1]][D[i]];
            int d_d0c1 = dist[D[i-1]][C[i]];
            int d_d0d1 = dist[D[i-1]][D[i]];
            for (int j = 0; j <= min(i+1, M); j++) {
                dp[i][j][0] = min(
                    dp[i-1][j][0] + d_c0c1,
                    dp[i-1][j][1] + K[i-1] * d_d0c1 + (1 - K[i-1]) * d_c0c1
                    );
                if (j == 0) continue;
                dp[i][j][1] = min(
                    dp[i-1][j-1][0] + K[i] * d_c0d1 + (1 - K[i]) * d_c0c1,
                    dp[i-1][j-1][1] + K[i-1]*K[i]*d_d0d1 + K[i-1]*(1-K[i])*d_d0c1
                    + (1-K[i-1])*K[i]*d_c0d1 + (1-K[i-1])*(1-K[i])*d_c0c1
                    );
            }
        }
        double minlen = INF;
        for (int i = 0; i < 2001; i++) {
            minlen = min(minlen, dp[N-1][i][0]);
            minlen = min(minlen, dp[N-1][i][1]);
        }
        printf("%.2f\n", minlen);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
