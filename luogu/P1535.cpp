// https://www.luogu.org/problemnew/show/P1535
// 游荡的奶牛

#include <bits/stdc++.h>
using namespace std;

int N, M, T, R1, C1, R2, C2;
int64_t dp[100][100][16];
bool field[100][100];

const int DX[4] = {0, -1, 0, 1};
const int DY[4] = {1, 0, -1, 0};

bool inRange(int r, int c) {
    return 0 <= r && r < N && 0 <= c && c < M;
}

int main() {
    cin >> N >> M >> T;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < M; j++) {
            field[i][j] = (s[j] == '.');
        }
    }

    cin >> R1 >> C1 >> R2 >> C2;
    R1--; C1--; R2--; C2--;

    dp[R1][C1][0] = 1;
    for (int t = 1; t <= T; t++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (!field[i][j]) continue;
                for (int d = 0; d < 4; d++) {
                    int k = i + DX[d];
                    int l = j + DY[d];
                    if (inRange(k, l)) dp[i][j][t] += dp[k][l][t-1];
                }
            }
        }
    }

    cout << dp[R2][C2][T] << endl;
    return 0;
}
