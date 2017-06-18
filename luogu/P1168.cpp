// https://www.luogu.org/problem/show?pid=1168
// 中位数

#include <bits/stdc++.h>
using namespace std;

using MinHeap = priority_queue<int, vector<int>, greater<int>>;
using MaxHeap = priority_queue<int>;

int N;
int A[100010];

void swapTop(MinHeap &minHeap, MaxHeap &maxHeap) {
    int x = minHeap.top();
    int y = maxHeap.top();

    minHeap.pop();
    maxHeap.pop();

    maxHeap.push(x);
    minHeap.push(y);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }

    MinHeap minHeap;
    MaxHeap maxHeap;

    printf("%d\n", A[1]);
    minHeap.push(A[1]);
    for (int i = 2; i < N; i += 2) {
        maxHeap.push(A[i]);
        minHeap.push(A[i+1]);
        if (minHeap.top() < maxHeap.top()) {
            swapTop(minHeap, maxHeap);
        }
        printf("%d\n", minHeap.top());
    }
    return 0;
}
