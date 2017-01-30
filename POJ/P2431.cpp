// http://poj.org/problem?id=2431
// Expedition

#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

class Solution {
private:
    vector<PII> A;
    int N, L, P;
public:
    Solution() {
        scanf("%d", &N);
        A.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &A[i].first, &A[i].second);
        }
        scanf("%d %d", &L, &P);
        for (int i = 0; i < N; i++) {
            A[i].first = L - A[i].first;
        }
    }

    int solve() {
        A.push_back(make_pair(L, 0));
        sort(A.begin(), A.end());
        int p = -1;
        for (int i = 0; i < (int)A.size(); i++) {
            if (p < 0 || A[p].first != A[i].first) {
                A[++p] = A[i];
            } else {
                A[p].second += A[i].second;
            }
        }
        A.erase(A.begin() + p + 1, A.end());
        priority_queue<PII> pq;
        int last = 0;
        int g = P;
        int ans = 0;
        for (int i = 0; i < (int)A.size(); i++) {
            g -= A[i].first - last;
            while (g < 0) {
                if (pq.empty()) return -1;
                g += pq.top().first;
                pq.pop();
                ans++;
            }
            pq.push(make_pair(A[i].second, A[i].first));
            last = A[i].first;
        }

        return ans;
    }
};

int main() {
    Solution solution;
    printf("%d\n", solution.solve());
    return 0;
}
