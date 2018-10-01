// https://www.luogu.org/problemnew/show/P3620
// [APIO/CTSC 2007]数据备份

#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
struct IterCmp {
    bool operator() (const list<int>::iterator &it1,
                     const list<int>::iterator &it2) const {
        return *it1 > *it2;
    }
};
using PQ = __gnu_pbds::priority_queue<list<int>::iterator, IterCmp>;
using PQIter = PQ::point_iterator;
using ListIter = list<int>::iterator;

namespace std {
template<>
    struct hash<ListIter> {
        size_t operator()(const ListIter &it) const noexcept {
            return size_t(&(*it)) & (0xFFFFFFFF);
        }
    };
}

const int MAXN = 100010;
int N, K;

ListIter remove(const ListIter &it, list<int> &spaces,
            PQ &pq, unordered_map<ListIter, PQIter> &pq_itermap) {
    auto pq_iter = pq_itermap.at(it);
    pq.erase(pq_iter);
    pq_itermap.erase(it);
    return spaces.erase(it);
}

int main() {

    scanf("%d%d", &N, &K);
    list<int> spaces;
    PQ pq;
    unordered_map<ListIter, PQIter> pq_itermap;
    int last;
    scanf("%d", &last);
    for (int i = 1; i < N; i++) {
        int s;
        scanf("%d", &s);
        int d = s - last;
        auto it = spaces.insert(spaces.end(), d);
        pq_itermap[it] = pq.push(it);
        last = s;
    }

    int ans = 0;
    while (K) {
        auto it = pq.top();
        auto tmp = it;
        ans += *it;
        if (it == spaces.begin()) {
            auto next = it;
            next++;
            remove(it, spaces, pq, pq_itermap);
            if (next != spaces.end()) {
                remove(next, spaces, pq, pq_itermap);
            }
        } else if (++tmp == spaces.end()) {
            auto prev = it;
            prev--;
            remove(it, spaces, pq, pq_itermap);
            remove(prev, spaces, pq, pq_itermap);
        } else {
            auto prev = it, next = it;
            prev--; next++;
            int s = *prev + *next - *it;
            remove(it, spaces, pq, pq_itermap);
            remove(next,spaces, pq, pq_itermap);
            *prev = s;
            auto pq_it = pq_itermap.at(prev);
            pq.modify(pq_it, prev);
        }

        K--;
    }

    printf("%d", ans);

    return 0;
}
