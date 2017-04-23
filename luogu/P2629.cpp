// https://www.luogu.org/problem/show?pid=2629
// 好消息，坏消息

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010;
int A[MAXN], ps[2*MAXN];
int N;

void add(deque<int> &dq, int i) {
    while (!dq.empty() && ps[dq.back()] >= ps[i]) dq.pop_back();
    dq.push_back(i);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        ps[i] = ps[i-1] + A[i];
    }
    for (int i = 1; i <= N; i++) {
        ps[N+i] = ps[N+i-1] + A[i];
    }
    deque<int> dq;
    for (int i = 1; i < N; i++) {
        add(dq, i);
    }

    int ret = 0;
    for (int i = N; i < 2*N; i++) {
        add(dq, i);
        while (dq.front() <= i - N) dq.pop_front();
        if (ps[dq.front()] >= ps[i-N]) ret++;
    }
    printf("%d\n", ret);
    return 0;
}
