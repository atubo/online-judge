// http://www.spoj.com/problems/CLONE/
// CLONE - Find the Clones

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20010;
int N, M;
char line[22];
int cnt[MAXN];

int64_t hash_dna() {
    int64_t ans = 0;
    for (int i = 0; i < M; i++) {
        int x;
        switch (line[i]) {
            case 'A':
                x = 0;
                break;
            case 'C':
                x = 1;
                break;
            case 'G':
                x = 2;
                break;
            case 'T':
                x = 3;
                break;
        }
        ans = 4 * ans + x;
    }
    return ans;
}

int main() {
    while (scanf("%d%d", &N, &M) && N != 0) {
        memset(cnt, 0, sizeof(cnt));
        map<int64_t, int> tally;
        for (int i = 0; i < N; i++) {
            scanf("%s", line);
            tally[hash_dna()]++;
        }
        for (const auto &t: tally) {
            cnt[t.second-1]++;
        }
        for (int i = 0; i < N; i++) {
            printf("%d\n", cnt[i]);
        }
    }

    return 0;
}
