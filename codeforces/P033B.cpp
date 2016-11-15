#include <vector>
using namespace std;

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


#include <algorithm>
#include <string>
#include <iostream>
int main()
{
    string s;
    string t;
    cin >> s >> t;
    const int MAX_VAL = 10000;
    int n;
    cin >> n;
    vector<vector<int> > graph(26, vector<int>(26, MAX_VAL));
    for (int i = 0; i < (int)graph.size(); i++) {
        graph[i][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        char a, b;
        cin >> a >> b;
        int w;
        cin >> w;
        int ia = a - 'a';
        int ib = b - 'a';
        graph[ia][ib] = min(graph[ia][ib], w);
    }

    FloydWarshall fw(graph);
    vector<vector<int> > dist = fw.getDist();

    if (s.length() != t.length()) {
        cout << -1 << endl;
        return 0;
    }

    string result;
    int totalCost = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        int a = s[i] - 'a';
        int b = t[i] - 'a';
        int minCost = MAX_VAL;
        char minChar = '\0';
        for (int c = 0; c < 26; c++) {
            if (dist[a][c] + dist[b][c] < minCost) {
                minCost = dist[a][c] + dist[b][c];
                minChar = c + 'a';
            }
        }
        if (minCost < MAX_VAL) {
            result.push_back(minChar);
            totalCost += minCost;
        }
        else {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << totalCost << endl;
    cout << result << endl;

    return 0;
}
