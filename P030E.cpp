#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class KMP {
public:
    KMP(const string& str):f(str.length(), 0) {
        int t = 0;
        f[0] = 0;

        // prefix function
        for (int s = 1; s < (int)str.length(); s++) {
            while (t > 0 && str[s] != str[t]) {
                t = f[t-1];
            }
            if (str[s] == str[t]) {
                t++;
            }
            f[s] = t;
        }
    }

    int operator[](int i) const {
        return f[i];
    }

private:
    vector<int> f;
};



class LongestPalindromicSubstr
{
public:
    LongestPalindromicSubstr(const string& seq_)
        :seq(seq_) {}
    pair<int, int> getLPSubstr() const {
        if (seq.size() == 0) {
            return make_pair(0, 0);
        }
        vector<int> l = getLengthArray(seq);
        vector<int>::const_iterator it = max_element(l.begin(),
                                                     l.end());
        int pos = it - l.begin();
        return make_pair(pos/2-l[pos]/2, l[pos]);
    }

    static vector<int> getLengthArray(const string& seq) {
        int seqLen = seq.length();
        vector<int> l;
        int i = 0;
        int parLen = 0;
        while (i < seqLen) {
START_OF_WHILE:
            if (i > parLen && seq[i - parLen - 1] == seq[i]) {
                parLen += 2;
                i++;
                continue;
            }
            l.push_back(parLen);

            int s = l.size() - 2;
            int e = s - parLen;
            for (int j = s; j > e; j--) {
                int d = j - e - 1;
                if (l[j] == d) {
                    parLen = d;
                    goto START_OF_WHILE;
                }
                l.push_back(min(d, l[j]));
            }
            parLen = 1;
            i++;
        }
        l.push_back(parLen);
        int lLen = l.size();
        int s = lLen - 2;
        int e = s - (2 * seqLen + 1 - lLen);
        for (int j = s; j > e; j--) {
            int d = j - e - 1;
            l.push_back(min(d, l[j]));
        }

        return l;
    }

private:
    const string& seq;
};

int main()
{
    string s;
    cin >> s;
    int n = s.length();
    string sRev(s);
    reverse(sRev.begin(), sRev.end());
    KMP kmp(sRev);
    
    int maxPos[n];
    int maxLen[n];
    maxPos[0] = -1;
    maxLen[0] = 0;
    int t = 0;
    for (int i = 0; i < n; i++) {
        while (t > 0 && s[i] != sRev[t]) {
            t = kmp[t-1];
        }
        if (s[i] == sRev[t]) {
            ++t;
        }
        if (i == 0 || t > maxLen[i-1]) {
            maxLen[i] = t;
            maxPos[i] = i - t + 1;
        } else {
            maxLen[i] = maxLen[i-1];
            maxPos[i] = maxPos[i-1];
        }
    }

    vector<int> v = LongestPalindromicSubstr::getLengthArray(s);
    int radius[n];
    for (int i = 0; i < n; i++) {
        radius[i] = v[2*i+1]/2;
    }

    int maxPos1 = -1, maxPos2 = 0;
    int maxLen1 = 0, maxLen2 = 1;
    int maxTotalLength = 1;
    for (int i = 1; i < n; i++) {
        int len1 = 0, pos1 = -1;
        int left = i - radius[i];
        if (left > 0) {
            len1 = min(maxLen[left-1], n-1-(i+radius[i]));
            pos1 = maxPos[left-1];
        }
        int totalLength = len1 * 2 + 2 * radius[i] + 1;
        if (totalLength > maxTotalLength) {
            maxPos1 = pos1;
            maxPos2 = left;
            maxLen1 = len1;
            maxLen2 = 2 * radius[i] + 1;
            maxTotalLength = totalLength;
        }
    }

    if (maxLen1 > 0) {
        printf("3\n");
        printf("%d %d\n", maxPos1+1, maxLen1);
        printf("%d %d\n", maxPos2+1, maxLen2);
        printf("%d %d\n", n-maxLen1+1, maxLen1);
    } else {
        printf("1\n");
        printf("%d %d\n", maxPos2+1, maxLen2);
    }

    return 0;
}
