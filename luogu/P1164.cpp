// https://www.luogu.org/problem/show?pid=1164
// 小A点菜
#include <limits.h>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int64_t> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    vector<int64_t> dpPrev(M+1, 0), dpCurr(M+1);
    dpPrev[0] = 1;
    for (int i = 0; i < N; i++) {
        for (int w = 0; w <= M; w++) {
            dpCurr[w] = dpPrev[w];
            if (w >= A[i]) dpCurr[w] += dpPrev[w-A[i]];
        }
        swap(dpPrev, dpCurr);
    }
    cout << dpPrev[M] << endl;
    return 0;
}
