// https://www.luogu.org/problem/show?pid=1160
// 队列安排
#include <cstdio>
#include <list>
#include <map>
using namespace std;

int main() {
    typedef list<int>::iterator Iter;
    int N;
    scanf("%d", &N);

    map<int, Iter> iterTable;
    list<int> q;
    q.push_back(1);
    iterTable[1] = q.begin();
    int k, p;
    for (int i = 2; i <= N; i++) {
        scanf("%d %d", &k, &p);
        Iter it = iterTable.at(k);
        if (p == 0) {
            iterTable[i] = q.insert(it, i);
        } else {
            Iter it2 = it;
            it2++;
            iterTable[i] = q.insert(it2, i);
        }
    }

    int M;
    scanf("%d", &M);
    while (M--) {
        scanf("%d", &k);
        if (iterTable.count(k) > 0) {
            q.erase(iterTable.at(k));
            iterTable.erase(k);
        }
    }
    for (Iter it = q.begin(); it != q.end(); it++) {
        printf("%d ", *it);
    }
    printf("\n");
    return 0;
}
