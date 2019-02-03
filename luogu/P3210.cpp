// https://www.luogu.org/problemnew/show/P3210
// [HNOI2010]取石头游戏

#include <bits/stdc++.h>
using namespace std;

struct Data {
    int64_t x;
    int idx, side;
    bool operator < (const Data &other) const {
        if (x != other.x) return x < other.x;
        return idx < other.x;
    }
};

const int MAXN = 1000010;
int N;
int A[MAXN];
int64_t tot;
bool isStack[MAXN];
int64_t storage[MAXN];

struct Deque {
    int l, r;
    int size() const {
        return r - l;
    }
    
    void push_back(int64_t x) {
        storage[r++] = x;
    }

    int64_t operator [](int x) const {
        return storage[x+l];
    }

    int64_t back() const {
        return storage[r-1];
    }

    void pop_back() {
        r--;
    }

    int64_t front() const {
        return storage[l];
    }

    void pop_front() {
        l++;
    }

    bool empty() const {
        return l == r;
    }
};

vector<Deque> dqs;

Deque build(int p, int q) {
    Deque ret{p, p};

    for (int i = p; i < q; i++) {
        ret.push_back(A[i]);
        while (ret.size() >= 3 &&
               ret[ret.size()-2] >= ret[ret.size()-1] &&
               ret[ret.size()-2] >= ret[ret.size()-3]) {
            int sz = ret.size();
            int64_t x = ret[sz-1] + ret[sz-3] - ret[sz-2];
            ret.pop_back();
            ret.pop_back();
            ret.pop_back();
            ret.push_back(x);
        }
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        tot += A[i];
    }
    int64_t res = 0;
    int p = 0;
    priority_queue<Data> pq;
    while (true) {
        while (p < N && A[p] == 0) p++;
        if (p == N) break;
        int q = p + 1;
        while (q < N && A[q] != 0) q++;
        auto dq = build(p, q);
        int sz = dqs.size();
        if (p == 0) {
            while (dq.size() >= 2 && dq[0] >= dq[1]) {
                int64_t x = dq.front();
                dq.pop_front();
                int64_t y = dq.front();
                dq.pop_front();
                res += y - x;
            }
            if (!dq.empty()) {
                pq.push({dq.back(), sz, 1});
                dqs.push_back(dq);
                isStack[sz] = true;
            }
        } else if (q == N) {
            while (dq.size() >= 2 && dq[dq.size()-1] >= dq[dq.size()-2]) {
                int64_t x = dq.back();
                dq.pop_back();
                int64_t y = dq.back();
                dq.pop_back();
                res += y - x;
            }
            if (!dq.empty()) {
                pq.push({dq.front(), sz, 0});
                dqs.push_back(dq);
                isStack[sz] = true;
            }
        } else {
            pq.push({dq.front(), sz, 0});
            if (dq.size() > 1) pq.push({dq.back(), sz, 1});
            dqs.push_back(dq);
        }

        p = q;
    }

    int64_t ans[2] = {0, 0};
    int round = 0;
    while (!pq.empty()) {
        auto data = pq.top();
        pq.pop();
        ans[(round++)%2] += data.x;
        int idx = data.idx;
        int side = data.side;
        if (side == 0) {
            dqs[idx].pop_front();
            if (dqs[idx].empty()) continue;
            if (dqs[idx].size() >= 2 || isStack[idx]) {
                pq.push({dqs[idx].front(), idx, 0});
            }
        } else {
            dqs[idx].pop_back();
            if (dqs[idx].empty()) continue;
            if (dqs[idx].size() >= 2 || isStack[idx]) {
                pq.push({dqs[idx].back(), idx, 1});
            }
        }
    }
    int64_t d = ans[0] - ans[1];
    if (round & 1) d -= res;
    else d += res;
    int64_t x0 = (tot + d) / 2;
    int64_t x1 = (tot - d) / 2;
    printf("%ld %ld\n", x0, x1);

    return 0;
}
