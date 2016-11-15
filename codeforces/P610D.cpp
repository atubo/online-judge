// http://codeforces.com/problemset/problem/610/D
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
        cout << A[i] << (i == (int)A.size()-1 ? "" : " ");
    }
    cout << endl;
}

class Solution {
    using PII = pair<int, int>;
    using TIIII = tuple<int, int, int, int>;
private:
    int N;
    map<int, vector<PII>> vert, horz;
public:
    Solution() {
        cin >> N;
        for (int i = 0; i < N; i++) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            if (y1 == y2) {
                if (x1 > x2) swap(x1, x2);
                horz[y1].push_back(make_pair(x1, x2));
            } else {
                if (y1 > y2) swap(y1, y2);
                vert[x1].push_back(make_pair(y1, y2));
            }
        }
    }

    void solve() {
        for (auto it = horz.begin(); it != horz.end(); ++it) {
            merge(it->second);
        }
        for (auto it = vert.begin(); it != vert.end(); ++it) {
            merge(it->second);
        }

        int64_t ret = 0;
        vector<TIIII> pts;
        for (auto it = horz.begin(); it != horz.end(); ++it) {
            for (const PII& seg: it->second) {
                pts.push_back(make_tuple(seg.first, -1,
                                         it->first, it->first));
                pts.push_back(make_tuple(seg.second, 1,
                                         it->first, it->first));
                ret += seg.second - seg.first + 1;
            }
        }

        for (auto it = vert.begin(); it != vert.end(); ++it) {
            for (const PII& seg: it->second) {
                pts.push_back(make_tuple(it->first, 0,
                                        seg.first, seg.second));
                ret += seg.second - seg.first + 1;
            }
        }

        sort(pts.begin(), pts.end());

        ordered_set s;
        for (const TIIII& pt: pts) {
            switch (get<1>(pt)) {
                case -1:
                    s.insert(get<2>(pt));
                    break;
                case 1:
                    s.erase(get<2>(pt));
                    break;
                case 0:
                    ret -= s.order_of_key(get<3>(pt)+1) -
                           s.order_of_key(get<2>(pt));
                    break;
                default:
                    assert(0);
                    break;
            }
        }
        cout << ret << endl;
    }

    void merge(vector<PII>& segs) {
        vector<PII> ret;
        vector<PII> pts;
        for (const PII& seg: segs) {
            pts.push_back(make_pair(seg.first, -1));
            pts.push_back(make_pair(seg.second, 1));
        }
        sort(pts.begin(), pts.end());
        int count = 0;
        for (const PII& pt: pts) {
            if (count == 0 && pt.second == -1) {
                ret.push_back(make_pair(pt.first, INT_MIN));
            }
            count += pt.second;
            if (count == 0) {
                assert(ret.back().second == INT_MIN);
                ret.back().second = pt.first;
            }
        }
        swap(segs, ret);
    }

};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}

