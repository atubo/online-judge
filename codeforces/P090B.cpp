// http://codeforces.com/problemset/problem/455/B
#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<char>> cw(N), status(N);
    for (int i = 0; i < N; i++) {
        cw[i].resize(M);
        status[i].resize(M, 1);
        string s;
        cin >> s;
        for (int j = 0; j < M; j++) {
            cw[i][j] = s[j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < M; k++) {
                if (k == j) continue;
                if (cw[i][j] == cw[i][k]) {
                    status[i][j] = status[i][k] = 0;
                }
            }
            for (int k = 0; k < N; k++) {
                if (k == i) continue;
                if (cw[i][j] == cw[k][j]) {
                    status[i][j] = status[k][j] = 0;
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (status[i][j]) cout << cw[i][j];
        }
    }
    cout << endl;
    return 0;
}

