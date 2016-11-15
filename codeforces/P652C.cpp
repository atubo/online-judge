// http://codeforces.com/problemset/problem/652/C
#include <algorithm>
#include <cassert>
#include <climits>
#include <deque>
#include <iostream>
#include <map>
#include <vector>

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
    vector<int> P;
    vector<PII> foePairs;
public:
    Solution() {
        cin >> N >> M;
        P.resize(N);
        READ_ARRAY(N, P);
        foePairs.resize(M);
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &foePairs[i].first, &foePairs[i].second);
        }
    }

    void solve() {
        vector<int> valueToIdx(N+1);
        for (int i = 0; i < N; i++) {
            valueToIdx[P[i]] = i;
        }

        vector<PII> foeIdxPair;
        for (const auto& fp: foePairs) {
            int pi = valueToIdx.at(fp.first);
            int qi = valueToIdx.at(fp.second);
            if (pi > qi) swap(pi, qi);
            foeIdxPair.push_back(make_pair(pi, qi));
        }

        vector<int> foeMapping(N+1, INT_MAX);
        for (const auto& fp: foeIdxPair) {
            foeMapping[fp.first] = min(foeMapping[fp.first], fp.second);
        }

        int64_t ret = 0;
        int p = 0, q = 0;
        vector<int> lookfor(N+1, INT_MAX);
        while (p < N) {
            int m = -1;
            while (q < N) {
                if (foeMapping[q] < INT_MAX) {
                    lookfor[foeMapping[q]] = q;
                }
                if (lookfor[q] < INT_MAX) {
                    m = lookfor[q];
                    break;
                }
                q++;
            }
            if (q == N) {
                ret += ((int64_t)q - p) * (q - p + 1) / 2;
                break;
            }

            assert(p <= m && m < q);
            for (; p <= m; p++) {
                ret += q - p;
                if (foeMapping[p] < INT_MAX &&
                    lookfor.at(foeMapping[p]) == p) {
                    lookfor.at(foeMapping[p]) = INT_MAX;
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
