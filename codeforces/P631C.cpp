// http://codeforces.com/contest/631/problem/C
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
    using PII = pair<int, int>;
private:
    int N, M;
    vector<int> A;
    vector<PII> ops;
public:
    Solution() {
        cin >> N >> M;
        A.resize(N);
        READ_ARRAY(N, A);

        ops.resize(M);
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &ops[i].first, &ops[i].second);
            ops[i].second--;
        }
    }

    void solve() {
        vector<PII> que;
        for (const PII& op: ops) {
            while (!que.empty() && que.back().second <= op.second) {
                que.pop_back();
            }
            que.push_back(op);
        }

        vector<int> ret = A;
        int t, p;
        tie(t, p) = que[0];
        sort(A.begin(), A.begin() + p + 1);

        int first = 0, last = p;
        for (int i = 0; i < (int)que.size(); i++) {
            tie(t, p) = que[i];
            int q = (i == (int)que.size()-1 ? 0 : que[i+1].second);
            if (t == 1) {
                for (int k = p; k > q; k--) {
                    ret[k] = A[last--];
                }
            } else {
                for (int k = p; k > q; k--) {
                    ret[k] = A[first++];
                }
            }
        }
        assert(first == last);
        ret[0] = A[first];
        printVector(ret);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
