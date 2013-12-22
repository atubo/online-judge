#include <algorithm>
#include <iostream>
#include <set>
#include <map>

using namespace std;

class ArrayPosCmp {
public:
    ArrayPosCmp(int* a_): a(a_) {}
    
    bool operator () (int i, int j) const {
        if (a[i] < a[j]) return true;
        if (a[i] > a[j]) return false;
        return i < j;
    }
private:
    int* a;
};

int main()
{
    int N;
    cin >> N;
    int a[N];
    int pos[N];
    bool visited[N];
    for (int i = 0; i < N; i++) {
        cin >> a[i];
        pos[i] = i;
        visited[i] = false;
    }

    sort(pos, pos + N, ArrayPosCmp(a));

    map<int, set<int> > pairs;
    for (int i = 0; i < N; i++) {
        int j = pos[i];
        if (visited[j]) continue;
        int l = j;
        int r = j;
        while (l >= 0 && a[l] % a[j] == 0) {
            visited[l] = true;
            l--;
        }
        l++;
        while (r < N && a[r] % a[j] == 0) {
            visited[r] = true;
            r++;
        }
        r--;
        pairs[r-l].insert(l);
    }

    map<int, set<int> >::reverse_iterator it = pairs.rbegin();
    set<int>& posSet = it->second;
    printf("%d %d\n", posSet.size(), it->first);
    for (int l: posSet) {
        printf("%d ", l + 1);
    }
    printf("\n");

    return 0;
}

