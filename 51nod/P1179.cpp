// https://www.51nod.com/onlineJudge/questionCode.html#!problemId=1179
// 1179 最大的最大公约数

#include <bits/stdc++.h>
using namespace std;

int main() {
    const int MAXS = 1000000;
    int N;
    scanf("%d", &N);
    vector<int> S(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &S[i]);
    }

    vector<int> freq(MAXS+1);
    for (int i = 1; i <= 1000; i++) {
        for (int x: S) {
            if (i * i > x) continue;
            if (i * i == x) {
                freq[i]++;
            } else if (x % i == 0) {
                freq[i]++;
                freq[x/i]++;
            }
        }
    }

    int ans = 1;
    for (int i = 2; i <= MAXS; i++) {
        if (freq[i] >= 2) ans = i;
    }

    printf("%d\n", ans);
    return 0;
}

