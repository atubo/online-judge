#include <iostream>
#include <queue>
#include <cassert>
#include <cstdio>
#include <cstdint>
using namespace std;

struct Event {
    Event() {}
    Event(int64_t t_, int window_, int id_):
        t(t_), window(window_), id(id_) {}
    int64_t t;
    int window;
    int id;
    bool operator < (const Event& other) const {
        if (t > other.t) return true;
        if (t < other.t) return false;
        if (window > other.window) return true;
        if (window < other.window) return false;
        return (id > other.id);
    }
};

int main()
{
    vector<deque<int> > waiting(3);
    int oSize[3] = {0};
    int K[3];
    cin >> K[0] >> K[1] >> K[2];
    int T[3];
    cin >> T[0] >> T[1] >> T[2];
    priority_queue<Event> queue;

    int N;
    cin >> N;
    int c[N];
    for (int i = 0; i < N; i++) {
        cin >> c[i];
        queue.push(Event(c[i], -1, i));
    }

    int64_t result = 0;
    int64_t tc = 0 ;
    while (!queue.empty()) {
        const Event& e = queue.top();
        tc = e.t;
        int window = e.window;
        int id = e.id;
        queue.pop();
        // ready to serve new customer
        if (window >= 0) {
            assert(oSize[window] > 0);
            if (waiting[window].size() > 0) {
                int ncId = waiting[window].front();
                waiting[window].pop_front();
                queue.push(Event(tc + T[window], window, ncId));
            } else {
                oSize[window]--;
            }
        }

        // customer goes to the next window
        window++;
        if (window < 3) {
            if (oSize[window] < K[window]) {
                oSize[window]++;
                queue.push(Event(tc + T[window], window, id));
            } else {
                waiting[window].push_back(id);
            }
        } else {
            result = max(result, tc - c[id]);
        }
    }

    cout << result << endl;

    return 0;
}
