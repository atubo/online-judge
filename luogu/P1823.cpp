// https://www.luogu.org/problem/show?pid=1823
// 音乐会的等待

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int64_t>;

int main() {
    int N;
    scanf("%d", &N);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    vector<PII> B;
    for (int i = 0; i < N; i++) {
        if (!B.empty() && B.back().first == A[i]) {
            B.back().second++;
        } else {
            B.push_back(make_pair(A[i], 1LL));
        }
    }

    stack<PII> s;
    int ret = 0;
    for (const PII& p: B) {
        int x = p.first;
        int64_t cntx = p.second;
        ret += cntx * (cntx-1) / 2;
        while (!s.empty() && s.top().first < x) {
            int64_t cnty = s.top().second;
            s.pop();
            ret += cnty;
        }
        if (!s.empty()) {
            int y = s.top().first;
            int64_t cnty = s.top().second;
            if (y == x) {
                ret += cntx * cnty;
                s.pop();
                if (!s.empty()) ret += cntx;
                s.push(make_pair(y, cntx + cnty));
            } else {
                ret += cntx;
                s.push(make_pair(x, cntx));
            }
        } else {
            s.push(make_pair(x, cntx));
        }
    }
    printf("%d\n", ret);

    return 0;
}
