// https://www.luogu.org/problem/show?pid=3602
// Koishi Loves Segments

#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
typedef pair<PII, int> TIII;

TIII make_tuple(int x, int y, int z) {
    return make_pair(make_pair(x, y), z);
}

void tie(TIII t, int& x, int& y, int& z) {
    x = t.first.first;
    y = t.first.second;
    z = t.second;
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

using namespace __gnu_pbds;
typedef __gnu_pbds::priority_queue<PII> PQ;
typedef PQ::point_iterator PQIter;

class Solution {
private:
    int N, M;
    vector<PII> seg;
    vector<PII> kp;
public:
    Solution() {
        scanf("%d %d", &N, &M);
        seg.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &seg[i].first, &seg[i].second);
        }
        kp.resize(M);
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &kp[i].first, &kp[i].second);
        }
    }

    void solve() {
        sort(kp.begin(), kp.end());
        int p = 0;
        for (int q = 0; q < M; q++) {
            if (kp[p].first != kp[q].first) {
                kp[++p] = kp[q];
            }
        }
        kp.erase(kp.begin() + p + 1, kp.end());
        M = p + 1;

        vector<TIII> pts;
        for (int i = 0; i < N; i++) {
            pts.push_back(make_tuple(seg[i].first, 0, i));
            pts.push_back(make_tuple(seg[i].second, 2, i));
        }

        for (int i = 0; i < M; i++) {
            pts.push_back(make_tuple(kp[i].first, 1, kp[i].second));
        }

        sort(pts.begin(), pts.end());

        int ans = 0;
        map<int, PQIter> idToIter;
        PQ pq;
        for (int i = 0; i < (int)pts.size(); i++) {
            int x, type, id;
            tie(pts[i], x, type, id);

            if (type == 0) {
                // left end
                PQIter it = pq.push(make_pair(seg[id].second, id));
                idToIter.insert(make_pair(id, it));
            } else if (type == 2) {
                // right end
                if (idToIter.count(id) == 0) continue;
                PQIter it = idToIter[id];
                pq.erase(it);
                idToIter.erase(id);
            } else {
                while ((int)idToIter.size() > id) {
                    PII t = pq.top();
                    int sid = t.second;
                    pq.pop();
                    assert(idToIter.count(sid) > 0);
                    idToIter.erase(sid);
                    ans++;
                }
            }
        }

        printf("%d\n", N-ans);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
