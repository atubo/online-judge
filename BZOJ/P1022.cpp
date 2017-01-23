// http://www.lydsy.com/JudgeOnline/problem.php?id=1022
// [SHOI2008]小约翰的游戏John

#include <iostream>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        int xt = 0;
        bool lt = false;
        for (int i = 0; i < N; i++) {
            int x;
            cin >> x;
            if (x > 1) lt = true;
            xt ^= x;
        }

        if ((xt > 0 && lt) || (xt == 0 && !lt)) {
            cout << "John" << endl;
        } else {
            cout << "Brother" << endl;
        }
    }
    return 0;
}
