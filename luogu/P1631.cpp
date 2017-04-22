// https://www.luogu.org/problem/show?pid=1631
// 序列合并

#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

const int MAXN = 100010;
int A[MAXN], B[MAXN], pos[MAXN];
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &B[i]);
    }

    priority_queue<PII, vector<PII>, greater<PII>> pq;
    for (int i = 0; i < N; i++) {
        pq.push(make_pair(A[i]+B[0], i));
    }

    for (int k = 0; k < N; k++) {
        int s, i;
        tie(s, i) = pq.top();
        printf("%d ", s);
        pq.pop();
        int j = pos[i];
        if (j < N-1) {
            pq.push(make_pair(A[i]+B[j+1], i));
            pos[i]++;
        }
    }
    printf("\n");
    return 0;
}
