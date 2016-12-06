// https://www.luogu.org/problem/show?pid=1996
// 约瑟夫问题
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    if (N == 0) return 0;
    M = M % N;
    if (M == 0) M = N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) A[i] = i+1;
    int curr = 0;
    for (int i = 0; i < N; i++) {
        curr = (curr + M - 1) % (N - i);
        cout << A[curr] << " ";
        A.erase(A.begin() + curr);
    }
    cout << endl;
    return 0;
}
