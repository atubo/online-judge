// http://codeforces.com/problemset/problem/190/D
#include <algorithm>
#include <cassert>
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
private:
    int N, K;
    vector<int> A;
public:
    Solution() {
        cin >> N >> K;
        A.resize(N);
        READ_ARRAY(N, A);
    }

    void solve() {
        map<int, int> count;
        int p = 0, q = 0;
        int64_t ret = 0;
        while (p < N) {
            int e = -1;
            while (q < N) {
                int x = A[q];
                count[x]++;
                if (count[x] == K) {
                    e = x;
                    break;
                }
                q++;
            }
            if (q == N) break;
            assert(e > 0);
            while (p <= q) {
                ret += N - q;
                int x = A[p++];
                count[x]--;
                if (count[e] < K) {
                    break;
                }
            }
            q++;
        }
        cout << ret << endl;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}

