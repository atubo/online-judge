// https://www.luogu.org/problem/show?pid=1199
// 三国游戏
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<vector<int> > matrix(N, vector<int>(N, 0));
    for (int i = 0; i < N-1; i++) {
        for (int j = i+1; j < N; j++) {
            int x;
            cin >> x;
            matrix[i][j] = matrix[j][i] = x;
        }
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        sort(matrix[i].begin(), matrix[i].end());
        ans = max(ans, matrix[i][N-2]);
    }
    cout << "1" << endl;
    cout << ans << endl;
    return 0;
}
