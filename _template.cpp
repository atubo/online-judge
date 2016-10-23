#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

#define READ_ARRAY(N, A) \
    for (int i = 0; i < N; i++) {\
        cin >> A[i];\
    }

template <typename T>
void printVector(const vector<T>& A) {
    for (const T& x: A) {
        cout << x << " ";
    }
    cout << endl;
}

