// https://www.lintcode.com/problem/integer-to-english-words/description
// 1305. Integer to English Words


#include <bits/stdc++.h>
using namespace std;
#include "../utils/BinaryTree.h"
#include "../utils/Graph.h"
#include "../utils/LinkedList.h"
#include "../utils/Util.h"

class Solution {
    const static int BILLION = 1000000000;
    const static int MILLION = 1000000;
    const static int THOUSAND = 1000;
    const static int HUNDRED = 100;
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        return parse(num);
    }

    string parse(int num) {
        vector<string> TENS = {"", "", "Twenty", "Thirty", "Forty",
            "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        vector<string> LITERAL = {"", "One", "Two", "Three", "Four",
            "Five", "Six", "Seven", "Eight", "Nine", "Ten",
            "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
            "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

        string ret;
        if (num >= BILLION) {
            ret = parse(num/BILLION) + " Billion";
            if (num % BILLION != 0) {
                ret += " " + parse(num%BILLION);
            }
        } else if (num >= MILLION) {
            ret = parse(num/MILLION) + " Million";
            if (num % MILLION != 0) {
                ret += " " + parse(num % MILLION);
            }
        } else if (num >= THOUSAND) {
            ret = parse(num/THOUSAND) + " Thousand";
            if (num % THOUSAND != 0) {
                ret += " " + parse(num % THOUSAND);
            }
        } else if (num >= HUNDRED) {
            ret = parse(num/HUNDRED) + " Hundred";
            if (num % HUNDRED != 0) {
                ret += " " + parse(num % HUNDRED);
            }
        } else if (num >= 20) {
            ret = TENS[num/10];
            if (num % 10 != 0) {
                ret += " " + parse(num % 10);
            }
        } else {
            ret = LITERAL[num];
        }
        return ret;
    }
};

int main() {
    Solution solution;
    int n;
    cin >> n;
    cout << solution.numberToWords(n) << endl;
    return 0;
}
