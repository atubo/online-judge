// https://www.luogu.org/problem/show?pid=1004
// 方格取数

#include <iostream>
#include <vector>
using namespace std;

const int DX[2] = {-1, 0};
const int DY[2] = {0, -1};

const int MAXN = 10;
int dp[MAXN][MAXN][MAXN][MAXN];

class Solution {
private:
    int N;
    vector<vector<int> > board;
public:
    Solution() {
        cin >> N;
        board.resize(N, vector<int>(N, 0));
        while (true) {
            int r, c, x;
            cin >> r >> c >> x;
            if (r == 0 && c == 0 && x == 0) break;
            board[r-1][c-1] = x;
        }
    }

    bool inRange(int i, int j) {
        return 0 <= i && i < N && 0 <= j && j < N;
    }

    void solve() {
        dp[0][0][0][0] = board[0][0];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    for (int l = 0; l < N; l++) {
                        for (int d1 = 0; d1 < 2; d1++) {
                            for (int d2 = 0; d2 < 2; d2++) {
                                int i0 = i + DX[d1];
                                int j0 = j + DY[d1];
                                int k0 = k + DX[d2];
                                int l0 = l + DY[d2];
                                if (!inRange(i0, j0) || !inRange(k0, l0)) continue;
                                if (i == k && j == l) {
                                    dp[i][j][k][l] = max(dp[i][j][k][l],
                                                         dp[i0][j0][k0][l0] + board[i][j]);
                                } else {
                                    dp[i][j][k][l] = max(dp[i][j][k][l],
                                                         dp[i0][j0][k0][l0] +
                                                         board[i][j] + board[k][l]);
                                }
                            }
                        }
                    }
                }
            }
        }
        cout << dp[N-1][N-1][N-1][N-1] << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
                            

