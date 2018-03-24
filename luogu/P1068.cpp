// https://www.luogu.org/problemnew/show/P1068
// 分数线划定

#include <bits/stdc++.h>
using namespace std;

struct Candidate {
    int id;
    int score;
    bool operator < (const Candidate &other) const {
        if (score > other.score) return true;
        if (score < other.score) return false;
        return id < other.id;
    }
};

int N, M;
Candidate candidates[5010];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        int k, s;
        scanf("%d%d", &k, &s);
        candidates[i] = {k, s};
    }
    sort(candidates, candidates + N);
    int threshold = candidates[int(M*1.5)-1].score;
    Candidate *endp = upper_bound(candidates, candidates + N,
                                  Candidate{INT_MAX, threshold});
    printf("%d %d\n", threshold, endp - candidates);
    for (int i = 0; i < endp-candidates; i++) {
        printf("%d %d\n", candidates[i].id, candidates[i].score);
    }
    return 0;
}
