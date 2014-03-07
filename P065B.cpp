#include <vector>
#include <string>
#include <iostream>
using namespace std;

string modify(const string& prev, const string& curr) {
    string result = curr;
    for (int i = 0; i < 4; i++) {
        char c1 = prev[i];
        char c2 = curr[i];
        if (c2 == c1) continue;
        if (c2 > c1) {
            if (curr.substr(i+1) >= prev.substr(i+1)) {
                result[i] = c1;
            } else if (c2 > c1 + 1) {
                result[i] = c1 + 1;
            } else {
                for (int j = i+1; j < 4; j++) {
                    if (curr[j] != '0') {
                        result[j] = '0';
                        break;
                    }
                }
            }
            break;
        } else {
            if (curr.substr(i+1) >= prev.substr(i+1)) {
                result[i] = c1;
            } else if (c1 < '9') {
                result[i] = c1 + 1;
            } else {
                result[i] = '0';
                for (int j = i-1; j >= 0; j--) {
                    if (result[j] == '9') {
                        result[j] = '0';
                    } else {
                        result[j] = result[j] + 1;
                        break;
                    }
                }
            }
            break;
        }
    }

    if (result < "1000" || result > "2011") {
        result = "";
    }

    return result;
}

int main() {
    int n;
    cin >> n;
    vector<string> harry;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        harry.push_back(s);
    }

    vector<string> ron;
    string prev = "1000";
    bool solvable = true;
    for (int i = 0; i < n; i++) {
        string s = modify(prev, harry[i]);
        if (s.empty()) {
            solvable = false;
            break;
        }
        ron.push_back(s);
        prev = s;
    }

    if (solvable) {
        for (int i = 0; i < n; i++) {
            cout << ron[i] << endl;
        }
    } else {
        cout << "No solution" << endl;
    }

    return 0;
}

