// http://codeforces.com/problemset/problem/652/C
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
            cin >> foePairs[i].first >> foePairs[i].second;
        }
    }

    void solve() {
        map<int, int> valueToIdx;
        for (int i = 0; i < N; i++) {
            valueToIdx[P[i]] = i;
        }

        vector<PII> foeIdxPair;
        for (const auto& fp: foePairs) {
            int p, q;
            tie(p, q) = fp;
            int pi = valueToIdx.at(p);
            int qi = valueToIdx.at(q);
            if (pi > qi) swap(pi, qi);
            foeIdxPair.push_back(make_pair(pi, qi));
        }

        map<int, int> foeMapping;
        for (const auto& fp: foeIdxPair) {
            int p, q;
            tie(p, q) = fp;
            if (foeMapping.count(p) == 0) {
                foeMapping[p] = q;
            } else {
                foeMapping[p] = min(foeMapping[p], q);
            }
        }

        int64_t ret = 0;
        int p = 0, q = 0;
        map<int, int> lookfor;
        while (p < N) {
            int m = -1;
            while (q < N) {
                if (foeMapping.count(q) > 0) {
                    lookfor[foeMapping[q]] = q;
                }
                if (lookfor.count(q) > 0) {
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
                if (foeMapping.count(p) > 0 &&
                    lookfor.at(foeMapping[p]) == p) {
                    lookfor.erase(foeMapping[p]);
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
