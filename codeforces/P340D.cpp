// http://codeforces.com/problemset/problem/340/D
// simple LIS

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    vector<int> C(N+1, INT_MAX);
    C[0] = 0;
    int ret = 0;
    for (int x: A) {
        int p = lower_bound(C.begin(), C.end(), x) - C.begin();
        ret = max(ret, p);
        C[p] = min(C[p], x);
    }
    cout << ret << endl;
    return 0;
}
