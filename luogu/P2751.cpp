// https://www.luogu.org/problem/show?pid=2751
// [USACO4.2]工序安排Job Processing

#include <bits/stdc++.h>
using namespace std;

int N;

vector<int> process(const vector<int>& a) {
    vector<int> finish(N);
    int M = a.size();
    vector<int> aEnd(M);
    for (int i = 0; i < N; i++) {
        int first = INT_MAX, p = -1;
        for (int j = 0; j < M; j++) {
            if (aEnd[j] + a[j] < first) {
                first = aEnd[j] + a[j];
                p = j;
            }
        }
        finish[i] = aEnd[p] = first;
    }
    return finish;
}

int main() {
    int M1, M2;
    scanf("%d %d %d", &N, &M1, &M2);
    vector<int> a(M1);
    for (int i = 0; i < M1; i++) {
        scanf("%d", &a[i]);
    }
    auto aDone = process(a);

    vector<int> b(M2);
    for (int i = 0; i < M2; i++) {
        scanf("%d", &b[i]);
    }
    auto bDone = process(b);

    sort(aDone.begin(), aDone.end());
    sort(bDone.begin(), bDone.end());

    int ret = -1;
    for (int i = 0; i < N; i++) {
        ret = max(ret, aDone[i] + bDone[N-1-i]);
    }

    printf("%d %d\n", aDone[N-1], ret);
    return 0;
}
