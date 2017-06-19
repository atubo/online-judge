// https://www.luogu.org/problem/show?pid=3407
// 散步

#include <bits/stdc++.h>
using namespace std;

struct Person {
    int64_t x0, xt;
    int dir;
    bool meet;

    Person() {
        x0 = xt = 0;
        dir = 0;
        meet = false;
    }
};

int N, Q;
int64_t T;

int main() {
    scanf("%d%lld%d", &N, &T, &Q);
    vector<Person> persons(N);
    for (int i = 0; i < N; i++) {
        scanf("%lld%d", &persons[i].x0, &persons[i].dir);
    }

    int p = 0;
    while (p < N && persons[p].dir == 2) p++;
    while (true) {
        while (p < N && persons[p].dir == 1) p++;
        if (p == N) break;
        int64_t x = (persons[p].x0 + persons[p-1].x0) / 2;
        for (int q = p-1; persons[q].dir == 1; q--) {
            persons[q].xt = x;
            persons[q].meet = true;
        }
        while (p < N && persons[p].dir == 2) {
            persons[p].xt = x;
            persons[p].meet = true;
            p++;
        }
    }

    for (int i = 0; i < Q; i++) {
        scanf("%d", &p);
        p--;
        if (!persons[p].meet || abs(persons[p].xt - persons[p].x0) > T) {
            printf("%lld\n", persons[p].x0 + T * (3 - persons[p].dir*2));
        } else {
            printf("%lld\n", persons[p].xt);
        }
    }

    return 0;
}
