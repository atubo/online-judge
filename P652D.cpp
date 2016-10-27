// http://codeforces.com/problemset/problem/652/D
#include <algorithm>
#include <cassert>
#include <climits>
#include <deque>
#include <iostream>
#include <map>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
        tree_order_statistics_node_update> ordered_set;

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        cin >> A[i];\
    }

template <typename T>
void printVector(const vector<T>& A) {
    for (int i = 0; i < (int)A.size(); i++) {
        cout << A[i] << endl;
    }
}

class Solution {
    using TIII = tuple<int, int, int>;
private:
    int N;
    vector<int> le, re;
public:
    Solution() {
        cin >> N;
        le.resize(N);
        re.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &le[i], &re[i]);
        }
    }

    void solve() {
        vector<TIII> points = buildPts();
        sort(points.begin(), points.end());
        vector<int> ret(N);
        ordered_set s;
        for (const TIII& pt: points) {
            int pos, type, idx;
            tie(pos, type, idx) = pt;
            if (type == 0) {
                ret[idx] = -s.order_of_key(re[idx]);
                s.insert(re[idx]);
            } else {
                ret[idx] += s.order_of_key(re[idx]);
            }
        }
        printVector(ret);
    }

    vector<TIII> buildPts() const {
        vector<TIII> ret;
        for (int i = 0; i < N; i++) {
            ret.push_back(make_tuple(le[i], 0, i));
            ret.push_back(make_tuple(re[i], 1, i));
        }
        return ret;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}

