// http://codeforces.com/contest/631/problem/A
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

int64_t orsum(const vector<int64_t>& A) {
    int64_t ret = 0;
    for (auto x: A) ret |= x;
    return ret;
}

int main() {
    int N;
    cin >> N;
    vector<int64_t> A(N);
    vector<int64_t> B(N);
    READ_ARRAY(N, A);
    READ_ARRAY(N, B);

    cout << orsum(A) + orsum(B) << endl;
    return 0;
}
