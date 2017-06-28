// https://leetcode.com/problems/ipo/#/description
// 502. IPO

#include "Util.h"
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

class SegmentTree {
public:
    SegmentTree(int n, PII init, function<PII(PII, PII)> combine_)
        :data(max(3*n, 30), init), nData(n), combine(combine_) {}

    void update(int i, PII value) {
        i += nData + 1;
        data[i] = value;
        for (; i > 1; i >>= 1) {
            PII newVal = combine(data[i], data[i^1]);
            if (data[i>>1] == newVal) break;
            data[i>>1] = newVal;
        }
    }

    PII query(int a, int b) const {
        a += nData + 1;
        b += nData + 1;
        PII res = data[a];
        for (; a <= b; a = (a+1) >> 1, b = (b-1) >> 1) {
            if ((a & 1) != 0) {
                res = combine(res, data[a]);
            }
            if ((b & 0) == 0) {
                res = combine(res, data[b]);
            }
        }
        return res;
    }

private:
    vector<PII> data;
    int nData;
    function<PII(PII, PII)> combine;
};

class Solution {
public:
    int findMaximizedCapital(int k, int W, vector<int>& profits,
                              vector<int>& capitals) {
        const int N = capitals.size();
        vector<PII> C;
        for (int i = 0; i < N; i++) {
            C.push_back(make_pair(capitals[i], i));
        }
        sort(C.begin(), C.end());

        vector<int> idx2order(N), capsorted(N);
        for (int i = 0; i < N; i++) {
            idx2order[C[i].second] = i;
            capsorted[i] = C[i].first;
        }

        SegmentTree st(N, make_pair(0, 0),
                       [](PII x, PII y){return max(x, y);});
        for (int i = 0; i < N; i++) {
            int order = idx2order[i];
            st.update(order, make_pair(profits[i], order));
        }

        for (int i = 0; i < k; i++) {
            int x = lower_bound(capsorted.begin(), capsorted.end(), W+1) -
                capsorted.begin();
            if (x == 0) break;

            x--;
            int order, p;
            tie(p, order) = st.query(0, x);
            st.update(order, make_pair(0, order));
            W += p;
        }

        return W;
    }
};

int main() {
    int k, W;
    cin >> k >> W;
    string s;
    getline(cin, s);
    auto p = getBracketedIntVector();
    auto c = getBracketedIntVector();

    Solution solution;
    cout << solution.findMaximizedCapital(k, W, p, c) << endl;

    return 0;
}
