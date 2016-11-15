// http://codeforces.com/problemset/problem/177/D1
#include <bits/stdc++.h>

using namespace std;

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        scanf("%d", &A[i]);\
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
    int N, M, C;
    vector<int> A, B;
    vector<int> ps;
public:
    Solution() {
        cin >> N >> M >> C;
        A.resize(N);
        READ_ARRAY(N, A);
        B.resize(M);
        READ_ARRAY(M, B);
    }

    int add(int a, int b) {
        return (a + b) % C;
    }

    int sub(int a, int b) {
        return (a + C - b) % C;
    }

    void build_partial() {
        ps.resize(M);
        ps[0] = B[0];
        for (int i = 1; i < M; i++) {
            ps[i] = add(ps[i-1], B[i]);
        }
    }

    int calc(int b, int e) {
        if (b == 0) return ps[e];
        return sub(ps[e], ps[b-1]);
    }

    void solve() {
        build_partial();
        for (int i = 0; i < N; i++) {
            int b = max(0, i + (M - N));
            int e = min(i, M - 1);
            cout << add(A[i], calc(b, e)) << " ";
        }
        cout << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
