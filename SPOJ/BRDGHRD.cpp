// http://www.spoj.com/problems/BRDGHRD/
#include <bits/stdc++.h>
using namespace std;

class LIS {
public:
    static int solve(const vector<int>& A) {
        const int N = A.size();
        vector<int> C(N+1, INT_MAX);
        C[0] = 0;
        int ret = 0;
        for (int x: A) {
            int p = upper_bound(C.begin(), C.end(), x) - C.begin();
            ret = max(ret, p);
            C[p] = min(C[p], x);
        }
        return ret;
    }
};

using PII = pair<int, int>;
int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;
        vector<int> A(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
        vector<int> B(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &B[i]);
        }
        vector<PII> pairs;
        for (int i = 0; i < N; i++) {
            pairs.push_back(make_pair(A[i], B[i]));
        }
        sort(pairs.begin(), pairs.end());
        vector<int> C(N);
        for (int i = 0; i < N; i++) {
            C[i] = pairs[i].second;
        }
        cout << LIS::solve(C) << endl;
    }
    return 0;
}
