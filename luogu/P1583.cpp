// https://www.luogu.org/problemnew/show/P1583
// 魔法照片

#include <bits/stdc++.h>
using namespace std;

struct Person {
    int id;
    int w;
    bool operator < (const Person &other) const {
        if (w > other.w) return true;
        if (w < other.w) return false;
        return id < other.id;
    }
};

const int MAXN = 20010;
int N, K;
Person persons[MAXN];
int E[10];

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < 10; i++) {
        scanf("%d", &E[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &persons[i].w);
        persons[i].id = i + 1;
    }
    sort(persons, persons + N);
    for (int i = 0; i < N; i++) {
        persons[i].w += E[i%10];
    }
    sort(persons, persons + N);
    for (int i = 0; i < K; i++) {
        printf("%d ", persons[i].id);
    }
    return 0;
}
