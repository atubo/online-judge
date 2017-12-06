// http://poj.org/problem?id=1659
// Frogs' Neighborhood

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<PII> lakes(N);
        for (int i = 0; i < N; i++) {
            cin >> lakes[i].first;
            lakes[i].second = i;
        }
        vector<vector<int> > adj(N, vector<int>(N));
        bool done = false;
        for (int i = 0; i < N; i++) {
            sort(lakes.begin()+i, lakes.end(), greater<PII>());
            if (i + lakes[i].first >= N) {
                cout << "NO" << endl;
                done = true;
                goto DONE;
            }
            for (int j = i+1; j <= i+lakes[i].first; j++) {
                if (lakes[j].first == 0) {
                    cout << "NO" << endl;
                    done = true;
                    goto DONE;
                }
                lakes[j].first--;
                int u = lakes[i].second, v = lakes[j].second;
                adj[u][v] = adj[v][u] = 1;
            }
        }
DONE:
        if (!done) {
            cout << "YES" << endl;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    cout << adj[i][j];
                    if (j < N-1) cout << " ";
                }
                cout << endl;
            }
        }
        if (T >= 1) cout << endl;
    }
    return 0;
}
