// https://www.luogu.org/problemnew/show/P4041
// [AHOI2014/JSOI2014]奇怪的计算器

#include <bits/stdc++.h>
using namespace std;

struct Data {
    int l, r, id;
    int64_t a, b;
    int64_t evalLeft() const {
        return a*l + b;
    }
    int64_t evalRight() const {
        return a*r + b;
    }
};

struct Item {
    int l;
    int64_t a, b;
    int64_t eval(int x) const {
        return a*x + b;
    }
};

const int MAXN = 100010;
int N, L, R;
int Q;
int64_t sa[MAXN], sb[MAXN];

void add(deque<Data> &data, int id, int a, int b) {
    sa[id] = sa[id-1] + a;
    sb[id] = sb[id-1] + b;
    if (a > 0 || b > 0) {
        while (!data.empty()) {
            auto &d = data.front();
            d.a += (sa[id] - sa[d.id]);
            d.b += (sb[id] - sb[d.id]);
            d.id = id;
            if (d.evalLeft() <= R) break;
            data.pop_front();
        }
        if (data.empty()) {
            data.push_front({L, R, id, 0, R});
        } else {
            auto &d = data.front();
            if (d.evalRight() <= R) {
                if (d.r < R) data.push_front({d.r+1, R, id, 0, R});
            } else {
                int64_t x = (1LL*R - d.b)/d.a;
                d.r = min(int64_t(R), x);
                if (x < R) {
                    data.push_front({int(x+1), R, id, 0, R});
                }
            }
        }
    } else {
        while (!data.empty()) {
            auto &d = data.back();
            d.a += (sa[id] - sa[d.id]);
            d.b += (sb[id] - sb[d.id]);
            d.id = id;
            if (d.evalRight() >= L) break;
            data.pop_back();
        }
        if (data.empty()) {
            data.push_back({L, R, id, 0, L});
        } else {
            auto &d = data.back();
            if (d.evalLeft() >= L) {
                if (d.l > L) data.push_back({L, d.l-1, id, 0, L});
            } else {
                int64_t x = (1LL*L - d.b + d.a - 1) / d.a;
                d.l = max(int64_t(L), x);
                if (x > L) {
                    data.push_back({L, int(x-1), id, 0, L});
                }
            }
        }
    }
}

void mul(deque<Data> &data, int id, int c) {
    sa[id] = sa[id-1];
    sb[id] = sb[id-1];
    if (c == 1) return;
    deque<Data> tmp;
    for (auto &d: data) {
        d.a += (sa[id] - sa[d.id]);
        d.b += (sb[id] - sb[d.id]);
        d.id = id;
        d.a *= c;
        d.b *= c;
        int64_t left = d.evalLeft();
        int64_t right = d.evalRight();
        if (right < L) {
            d.a = 0;
            d.b = L;
            tmp.push_back(d);
            continue;
        }
        if (left > R) {
            d.a = 0;
            d.b = R;
            tmp.push_back(d);
            continue;
        }
        if (left < L) {
            int64_t x = (1LL*L - d.b + d.a - 1) / d.a;
            tmp.push_back({int(x), d.r, id, d.a, d.b});
            tmp.push_back({d.l, int(x-1), id, 0, L});
        } else if (right > R) {
            int64_t x = (1LL*R - d.b) / d.a;
            tmp.push_back({int(x+1), d.r, id, 0, R});
            tmp.push_back({d.l, int(x), id, d.a, d.b});
        } else {
            tmp.push_back(d);
        }
    }
    swap(data, tmp);
}

void print(const deque<Data> &data) {
    printf("===\n");
    for (const auto &d: data) {
        printf("%d %d %d %ld %ld\n", d.l, d.r, d.id, d.a, d.b);
    }
}

int main() {
    scanf("%d%d%d", &N, &L, &R);
    deque<Data> data;
    data.push_front({L, R, 0, 1, 0});
    char cmd[5];
    for (int i = 1; i <= N; i++) {
        scanf("%s", cmd);
        int a = 0, b = 0;
        if (cmd[0] == '+') {
            scanf("%d", &b);
            add(data, i, 0, b);
        } else if (cmd[0] == '-') {
            scanf("%d", &b);
            add(data, i, 0, -b);
        } else if (cmd[0] == '*') {
            scanf("%d", &a);
            mul(data, i, a);
        } else {
            scanf("%d", &a);
            add(data, i, a, 0);
        }
    }

    vector<Item> items;
    for (const auto &d: data) {
        Item item;
        item.l = d.l;
        item.a = d.a + sa[N] - sa[d.id];
        item.b = d.b + sb[N] - sb[d.id];
        items.push_back(item);
    }
    reverse(items.begin(), items.end());

    scanf("%d", &Q);
    const int len = items.size();
    for (int i = 0; i < Q; i++) {
        int x;
        scanf("%d", &x);
        if (items[len-1].l <= x) {
            printf("%ld\n", items[len-1].eval(x));
            continue;
        }
        int lo = 0, hi = len-1;
        while (lo < hi-1) {
            int mid = (lo + hi) / 2;
            if (items[mid].l <= x) lo = mid;
            else hi = mid;
        }
        printf("%ld\n", items[lo].eval(x));
    }

    return 0;
}
