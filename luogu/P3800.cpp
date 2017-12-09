// https://www.luogu.org/problemnew/show/P3800
// Power收集

#include <bits/stdc++.h>
using namespace std;

int N, M, K, T;

using PII = pair<int, int>;

int main() {
    scanf("%d%d%d%d", &N, &M, &K, &T);
    T = min(M-1, T);
    vector<vector<PII>> points(N);
    for (int i = 0; i < K; i++) {
        int x, y, v;
        scanf("%d%d%d", &x, &y, &v);
        x--; y--;
        points[x].push_back(make_pair(y, v));
    }

    int j, v;
    vector<int> dpPrev(M), dpCurr(M);

    // first row
    for (int i = 0; i < (int)points[0].size(); i++) {
        tie(j, v) = points[0][i];
        dpPrev[j] = v;
    }

    for (int r = 1; r < N; r++) {
        vector<int> line(M);
        for (int i = 0; i < (int)points[r].size(); i++) {
            tie(j, v) = points[r][i];
            line[j] = v;
        }
        deque<int> dq;
        for (int i = 0; i <= T; i++) {
            while (!dq.empty() && dpPrev[dq.front()] <= dpPrev[i]) dq.pop_front();
            dq.push_front(i);
        }
        dpCurr[0] = dpPrev[dq.back()] + line[0];
        for (int c = 1; c < M; c++) {
            while (!dq.empty() && dq.back() < c-T) dq.pop_back();
            if (c+T < M) {
                while (!dq.empty() && dpPrev[dq.front()] <= dpPrev[c+T]) {
                    dq.pop_front();
                }
                dq.push_front(c+T);
            }
            dpCurr[c] = dpPrev[dq.back()] + line[c];
        }
        swap(dpPrev, dpCurr);
    }
    int ret = *max_element(dpPrev.begin(), dpPrev.end());
    printf("%d\n", ret);
    return 0;
}
