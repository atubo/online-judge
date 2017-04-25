// https://www.luogu.org/problem/show?pid=2448
// 无尽的生命

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

class Solution {
    unordered_map<int, int> smap;
    int K;
    int N;
    vector<int> tmp;
public:
    Solution() {
        scanf("%d", &K);
        for (int i = 0; i < K; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            swapSkill(u, v);
        }
    }

    void swapSkill(int u, int v) {
        if (smap.count(u) == 0) smap[u] = u;
        if (smap.count(v) == 0) smap[v] = v;
        swap(smap[u], smap[v]);
    }

    void solve() {
        vector<PII> v;
        for (auto it = smap.begin(); it != smap.end(); ++it) {
            v.push_back(*it);
        }
        N = v.size();
        tmp.resize(N);
        sort(v.begin(), v.end());
        vector<int> v2(N);
        for (int i = 0; i < N; i++) {
            v2[i] = v[i].second;
        }

        int64_t ret = countRev1(v2);
        ret += countRev2(v);
        printf("%lld\n", ret);
    }

    int countRev1(vector<int>& v) {
        return mergeSort(v, 0, N);
    }

    int mergeSort(vector<int>& v, int lo, int hi) {
        if (lo >= hi - 1) return 0;
        int mid = (lo + hi) / 2;
        int ret = mergeSort(v, lo, mid);
        ret += mergeSort(v, mid, hi);

        int p = lo, q = mid, k = lo;
        while (p < mid && q < hi) {
            if (v[p] <= v[q]) {
                tmp[k++] = v[p++];
            } else {
                tmp[k++] = v[q++];
                ret += mid - p;
            }
        }
        while (p < mid) {
            tmp[k++] = v[p++];
        }
        while (q < hi) {
            tmp[k++] = v[q++];
        }
        for (int i = lo; i < hi; i++) {
            v[i] = tmp[i];
        }
        return ret;
    }

    int64_t countRev2(const vector<PII> &v) {
        vector<int> v2(N);
        for (int i = 0; i < N; i++) {
            v2[i] = v[i].first;
        }

        int64_t ret = 0;
        for (const PII &p: v) {
            int pos = p.first;
            int x = p.second;
            if (x > pos) {
                ret += x - pos - 1;
                ret -= upper_bound(v2.begin(), v2.end(), x-1) -
                    upper_bound(v2.begin(), v2.end(), pos);
            } else {
                ret += pos - x - 1;
                ret -= upper_bound(v2.begin(), v2.end(), pos-1) -
                    upper_bound(v2.begin(), v2.end(), x);
            }
        }
        return ret;
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
