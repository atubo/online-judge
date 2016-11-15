// http://codeforces.com/contest/631/problem/B
#include <bits/stdc++.h>

using namespace std;

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        cin >> A[i];\
    }

template <typename T>
void printVector(const vector<T>& A) {
    for (int i = 0; i < (int)A.size(); i++) {
        cout << A[i] << (i == (int)A.size()-1 ? "" : " ");
    }
    cout << endl;
}

class Solution {
    using PII = pair<int, int>;
private:
    int N, M, K;
    vector<PII> row, col;
public:
    Solution() {
        cin >> N >> M >> K;
        row.resize(N, {0, 0});
        col.resize(M, {0, 0});
    }

    void solve() {
        for (int i = 1; i <= K; i++) {
            int t, x, a;
            scanf("%d %d %d", &t, &x, &a);
            x--;
            if (t == 1) row[x] = {i, a};
            else col[x] = {i, a};
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                int a = (row[i].first > col[j].first ?
                         row[i].second : col[j].second);
                cout << a << (j == M-1 ? "" : " ");
            }
            cout << endl;
        }
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
