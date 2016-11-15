// http://codeforces.com/problemset/problem/514/D
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <vector>

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
    using DQ = deque<PII>;
private:
    int N, M, K;
    vector<vector<int>> A;
public:
    Solution() {
        cin >> N >> M >> K;
        A.resize(N);
        for (int i = 0; i < N; i++) {
            A[i].resize(M);
            for (int j = 0; j < M; j++) {
                cin >> A[i][j];
            }
        }
    }

    void solve() {
        vector<DQ> dqs(M);
        int p = 0;
        int ret = 0;
        vector<int> sol(M), maxSol(M);
        while (p < N) {
            int q = p;
            while (q < N) {
                for (int m = 0; m < M; m++) {
                    updateQueue(dqs[m], A[q][m], q);
                }
                if (sumMax(dqs, sol) > K) break;
                if (q - p + 1 > ret) {
                    ret = q - p + 1;
                    maxSol = sol;
                }
                q++;
            }
            if (q == N) break;
            p = findBoundary(dqs, p);
        }
        printVector(maxSol);
    }

    void updateQueue(deque<PII>& dq, int x, int pos) {
        for (int i = dq.size() - 1; i >= 0; i--) {
            if (dq[i].first > x) break;
            dq.pop_back();
        }
        dq.push_back(make_pair(x, pos));
    }

    int sumMax(const vector<DQ>& dqs, vector<int>& sol) {
        int total = 0;
        for (int m = 0; m < M; m++) {
            int t = dqs[m].empty() ? 0 : dqs[m].front().first;
            total += t;
            sol[m] = t;
        }
        return total;
    }

    int findBoundary(vector<DQ>& dqs, int p) {
        vector<int> sol(M);
        while (sumMax(dqs, sol) > K) {
            for (int m = 0; m < M; m++) {
                if (!dqs[m].empty() && dqs[m].front().second == p) {
                    dqs[m].pop_front();
                }
            }
            p++;
        }
        return p;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
