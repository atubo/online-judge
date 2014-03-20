#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <cmath>
#include <map>
using namespace std;

struct Operation {
    Operation(int type_ = 0, int value_ = 0): type(type_), value(value_) {}
    int type;
    int value;
};

class Segment {
public:
    Segment(int N): values(N, 0) {
        resetSum();
        size = 0;
    }

    void add(int offset, int x) {
        assert(values[offset] == 0);
        values[offset] = x;
        resetSum();
        getSum();
        size++;
    }

    void remove(int offset, int x) {
        assert(values[offset] > 0);
        values[offset] = 0;
        resetSum();
        getSum();
        size--;
    }

    vector<int> values;
    int64_t sum[5];
    int size;

private:
    void resetSum() {
        for (int i = 0; i < 5; i++) {
            sum[i] = 0;
        }
    }
    void getSum() {
        int offset = 0;
        for (int x: values) {
            if (x > 0) {
                sum[offset] += x;
                offset = (offset + 1) % 5;
            }
        }
    }

};

int64_t getSum(const vector<Segment>& seg)
{
    int64_t result = 0;
    int offset = 0;
    for (Segment s: seg) {
        result += s.sum[(7-offset)%5];
        offset = (offset + s.size) % 5;
    }
    return result;
}

int main()
{
    int Nop;
    cin >> Nop;
    set<int> values;
    vector<Operation> ops;
    for (int i = 0; i < Nop; i++) {
        string opstr;
        int x;
        cin >> opstr;
        switch (opstr[0]) {
            case 'a':
                cin >> x;
                ops.push_back(Operation(0, x));
                values.insert(x);
                break;
            case 'd':
                cin >> x;
                ops.push_back(Operation(1, x));
                break;
            case 's':
                ops.push_back(Operation(2, 0));
                break;
            default:
                assert(0);
                break;
        }
    }

    if (values.size() == 0) {
        cout << 0 << endl;
        return 0;
    }
    int N = sqrt(values.size());
    int M = values.size()/N;
    if (values.size() % N != 0) ++M;

    vector<Segment> seg;
    for (int i = 0; i < M; i++) {
        seg.push_back(Segment(N));
    }

    map<int, int> x2id;
    int i = 0;
    for (set<int>::const_iterator it = values.begin();
         it != values.end(); it++, i++) {
        x2id[*it] = i;
    }

    for (i = 0; i < Nop; i++) {
        switch (ops[i].type) {
            case 0:
            case 1:
                {
                    int x = ops[i].value;
                    int id = x2id[x];
                    int segId = id / N;
                    int offset = id % N;
                    if (ops[i].type == 0) {
                        seg[segId].add(offset, x);
                    } else {
                        seg[segId].remove(offset, x);
                    }
                    break;
                }
            case 2:
                {
                    int64_t result = getSum(seg);
                    cout << result << endl;
                    break;
                }
            default:
                assert(0);
                break;
        }
    }

    return 0;
}

