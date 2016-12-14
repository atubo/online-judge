// https://www.luogu.org/problem/show?pid=1462
// 通往奥格瑞玛的道路
#include <queue>
#include <vector>
#include <inttypes.h>
using namespace std;
typedef pair<int64_t,int> PII;  // pair = (dist, vertex)

vector<int> FI;

class FastDijkstra {
public:
    static const int64_t INF;


    FastDijkstra(const vector<vector<PII> >& edges_, int s_, int t_):
        edges(edges_), s(s_), t(t_), N(edges.size()),
        dist(N, INF), dad(N, -1)
    {
        //solve();
    }

    const vector<int64_t>& getDist() const {
        return dist;
    }

    const vector<int>& getDad() const {
        return dad;
    }

    void solve(int th) {
        // use priority queue in which top element has the "smallest" priority
        priority_queue<PII, vector<PII>, greater<PII> > Q;
        Q.push (make_pair (0, s));
        dist[s] = 0;
        while (!Q.empty()){
            PII p = Q.top();
            if (p.second == t) break;
            Q.pop();

            int here = p.second;
            for (vector<PII>::const_iterator it=edges[here].begin();
                 it!=edges[here].end(); it++){
                if (FI[it->second] > th) continue;
                if (dist[here] + it->first < dist[it->second]){
                    dist[it->second] = dist[here] + it->first;
                    dad[it->second] = here;
                    Q.push (make_pair (dist[it->second], it->second));
                }
            }
        }
    }

private:
    const vector<vector<PII> >& edges;
    const int s;
    const int t;
    const int N;
    vector<int64_t> dist;
    vector<int> dad;
};

const int64_t FastDijkstra::INF = 0x7FFFFFFFFFFFFFFF;

#include <cstdio>

class Solution {
private:
    int N, M;
    int64_t B;
    vector<vector<PII> > edges;
public:
    Solution() {
        scanf("%d %d %lld", &N, &M, &B);
        FI.resize(N);
        edges.resize(N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &FI[i]);
        }
        int a, b, c;
        for (int i = 0; i < M; i++) {
            scanf("%d %d %d", &a, &b, &c);
            a--; b--;
            edges[a].push_back(make_pair(c, b));
            edges[b].push_back(make_pair(c, a));
        }
    }

    bool feasible(int th) {
        if (th < FI[0]) return false;
        FastDijkstra dijkstra(edges, 0, N-1);
        dijkstra.solve(th);
        return (dijkstra.getDist()[N-1] < B);
    }


    void solve() {
        int hi = 1000000001;
        if (!feasible(hi)) {
            printf("AFK\n");
            return;
        }
        int lo = 0;
        while (lo < hi-1) {
            int mid = (lo + hi) / 2;
            if (feasible(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        printf("%d\n", hi);
    }
};

int main() {
    Solution solution;
    solution.solve();
    return 0;
}
