#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main()
{
    typedef pair<int, int> PII;

    int n;
    cin >> n;
    vector<PII> q;
    for (int i = 0; i < n; i++) {
        int qi;
        cin >> qi;
        q.push_back(make_pair(qi, i));
    }
    sort(q.begin(), q.end());

    const int INF = numeric_limits<int>::max();
    vector<int> cost(n, INF);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        cost[b] = min(cost[b], c);
    }

    int totalCost = 0;
    bool success = true;
    for (int i = 0; i < n-1; i++) {
        int subordinate = q[i].second;
        if (cost[subordinate] == INF) {
            success = false;
            break;
        }
        totalCost += cost[subordinate];
    }

    cout << (success ? totalCost : -1) << endl;

    return 0;
}
