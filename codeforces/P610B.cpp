// http://codeforces.com/problemset/problem/610/B
#include <bits/stdc++.h>

using namespace std;

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        scanf("%d", &A[i]);\
    }

int findMaxDist(const vector<int>& A, int x) {
    const int N = A.size();
    int p = 0;
    int ret = 0;
    while (p < N) {
        while (p < N && A[p] != x) p++;
        if (p == N) break;
        int q = p + 1;
        while (q < p + N && A[q%N] != x) q++;
        ret = max(ret, q - p - 1);
        p = q;
    }
    return ret;
}

int main() {
    int64_t N;
    cin >> N;
    vector<int> A(N);
    READ_ARRAY(N, A);

    int minElem = *min_element(A.begin(), A.end());
    int maxDist = findMaxDist(A, minElem);
    int64_t ret = N * minElem + maxDist;
    cout << ret << endl;
    return 0;
}
