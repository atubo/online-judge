// http://codeforces.com/problemset/problem/282/E
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
private:
    const int MAXD = 41;
    int N;
    vector<int64_t> A;
    vector<int64_t> psLeft, psRight;
public:
    Solution() {
        cin >> N;
        A.resize(N);
        READ_ARRAY(N, A);
        psLeft.resize(N);
        psRight.resize(N);
    }

    void build_ps() {
        psLeft[0] = A[0];
        for (int i = 1; i < N; i++) {
            psLeft[i] = psLeft[i-1] ^ A[i];
        }
        for (int i = N-1; i > 0; i--) {
            psRight[i] = psLeft[N-1] ^ psLeft[i-1];
        }
        psRight[0] = psLeft[N-1];
    }

    bool feasible(int64_t mask, int d) {
        set<int64_t> left;
        int64_t maskhi = ((1LL << d) - 1) << (MAXD - d);
        if ((psRight[0] & maskhi) == mask) return true;
        for (int i = 0; i < N-1; i++) {
            int64_t hiLeft = psLeft[i] & maskhi;
            int64_t hiRight = psRight[i+1] & maskhi;
            left.insert(hiLeft);
            if (hiLeft == mask || hiRight == mask || left.count(hiRight^mask) > 0) {
                return true;
            }
        }
        return (psLeft[N-1] & maskhi) == mask;
    }

    void solve() {
        build_ps();

        int64_t ret = 0;
        for (int d = 1; d <= MAXD; d++) {
            int64_t mask = ret | (1LL << (MAXD - d));
            if (feasible(mask, d)) {
                ret = mask;
            }
        }
        cout << ret << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
