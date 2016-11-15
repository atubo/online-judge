#include <iostream>
#include <cinttypes>

using namespace std;

int64_t xorUpto(int64_t n)
{
    // 2n xor (2n+1) has only the last digit 1
    if (n == 0) return 0;
    int64_t x = ((n+1)/2) % 2;
    if (n % 2 == 0) x = n | x;
    return x;
}

int main()
{
    int n;
    cin >> n;
    int64_t result = 0;
    for (int i = 0; i < n; i++) {
        int64_t x, m;
        cin >> x >> m;
        result ^= (xorUpto(x-1) ^ xorUpto(x+m-1));
    }
    cout << (result == 0 ? "bolik" : "tolik") << endl;
}
