// http://poj.org/problem?id=2823
// Sliding Window

#include <cstdio>
using namespace std;

const int MAXN = 1000010;
int A[MAXN], maxr[MAXN], minr[MAXN];
int N, K;
int maxq[MAXN], minq[MAXN];
int headmax, tailmax, headmin, tailmin;

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    int pos = 0;
    for (int i = 0; i < N; i++) {
        while (headmax != tailmax && A[maxq[tailmax-1]] <= A[i]) tailmax--;
        maxq[tailmax++] = i;
        while (headmin != tailmin && A[minq[tailmin-1]] >= A[i]) tailmin--;
        minq[tailmin++] = i;

        while (i - maxq[headmax] >= K) headmax++;
        while (i - minq[headmin] >= K) headmin++;


        if (i >= K-1) {
            maxr[pos] = A[maxq[headmax]];
            minr[pos] = A[minq[headmin]];
            pos++;
        }
    }

    for (int i = 0; i < N-K+1; i++) {
        printf("%d ", minr[i]);
    }
    printf("\n");
    for (int i = 0; i < N-K+1; i++) {
        printf("%d ", maxr[i]);
    }
    printf("\n");
    return 0;
}
