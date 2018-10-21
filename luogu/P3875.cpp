// https://www.luogu.org/problemnew/show/P3875
// [TJOI2010]被污染的河流

#include <bits/stdc++.h>
using namespace std;

// note it's 1-indexed
class SegmentTree {
    int N;
    int64_t *val, *lazy;

public:
    SegmentTree(int N_): N(N_) {
        val = new int64_t[4*N]{};
        lazy = new int64_t[4*N]{};
    }

    ~SegmentTree() {
        delete[] val;
        delete[] lazy;
    }

    void update(int t, int a, int b) {
        update(1, t, 1, N, a, b);
    }

    // query range sum in [a, b]
    int64_t query(int a, int b) {
        return query(1, a, b, 1, N);
    }

private:
    void update(int k, int t, int l, int r, int a, int b) {
        if (a <= l && r <= b) {
            lazy[k] += t;
            pushup(k, l, r);
            return;
        }

        int mid = (l + r) / 2;
        if (a <= mid) update(2*k, t, l, mid, a, b);
        if (mid < b)  update(2*k+1, t, mid+1, r, a, b);
        pushup(k, l, r);
    }

    void pushup(int k, int l, int r) {
        if (lazy[k]) val[k] = r - l + 1;
        else if (l == r) val[k] = lazy[k] ? 1: 0;
        else val[k] = val[2*k] + val[2*k+1];
    }

    // query range sum in [a, b], current node is [L, R]
    int64_t query(int k, int a, int b, int L, int R) {
        if (!k) return 0;
        if (b < L || a > R) return 0;
        if (a <= L && R <= b) return val[k];
        int64_t sum = 0;
        int mid = (L + R) / 2;
        if (a <= mid) sum += query(2*k, a, b, L, mid);
        if (mid < b)  sum += query(2*k+1, a, b, mid+1, R);
        return sum;
    }
};

const int MAXL = 100010;

struct Event {
    int s, e, h, t;
    bool operator < (const Event &other) const {
        if (h < other.h) return true;
        if (h > other.h) return false;
        if (t < other.t) return true;
        if (t > other.t) return false;
        if (s < other.s) return true;
        if (s > other.s) return false;
        return e < other.e;
    }
};

int N;

int main() {
    scanf("%d", &N);
    vector<Event> events;
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        if (x1 == x2) {
            events.push_back(Event{x1, x1+1, y1+1, 1});
            events.push_back(Event{x1, x1+1, y2+1, -1});
        } else {
            events.push_back(Event{x1+1, x2, y1, 1});
            events.push_back(Event{x1+1, x2, y1+2, -1});
        }
    }
    sort(events.begin(), events.end());

    SegmentTree st(MAXL);
    int last = -1;
    int64_t ans = 0;
    int id = 0;
    for (const auto &e: events) {
        id++;
        if (last == -1) last = e.h;
        ans += 1LL* (e.h - last) * st.query(1, MAXL);

        st.update(e.t, e.s, e.e);
        last = e.h;
    }
    printf("%ld\n", ans);
    return 0;
}
