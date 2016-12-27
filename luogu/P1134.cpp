#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    int ans = 1;
    int power5 = 0, power2 = 0;
    for (int i = 1; i <= N; i++) {
        int a = i;
        while (a % 5 == 0) {
            power5++;
            a /= 5;
        }
        while (a % 2 == 0) {
            power2++;
            a /= 2;
        }
        ans = (ans * a) % 10;
    }
    for (int i = 0; i < (power2 - power5); i++) {
        ans = (ans * 2) % 10;
    }
    cout << ans << endl;
    return 0;
}
