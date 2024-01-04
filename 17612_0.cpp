#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

//id, w
using user = pair<int, int>;
//id, end time, counter idx
using counter = pair<user, int>;

struct cmp {
    bool operator()(counter a, counter b) {
        if(a.first.second == b.first.second) {
            return a.second < b.second;
        }
        return a.first.second > b.first.second;
    }
};

int N, K, cnt;
long long ans, my_time;
queue<user> line;
priority_queue<int, vector<int>, greater<int>> off_counters;
priority_queue<counter, vector<counter>, cmp> counters;

void push() {
    while(counters.size() < K && !line.empty()) {
        auto user = line.front(); line.pop();
        user.second += my_time;
        int counter_idx = off_counters.top(); off_counters.pop();
        counter customer = {user, counter_idx};
        counters.push(customer);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>N>>K;
    for(int i=0; i<N; i++) {
        user a;
        cin>>a.first>>a.second;
        line.push(a);
    }
    for(int i=0; i<K; i++) off_counters.push(i);
    push();
    while(!counters.empty()) {
        auto top = counters.top(); counters.pop();
        //printf("%d\t%d\t%d\n", top.first.first, top.first.second, top.second);

        off_counters.push(top.second);

        cnt++;
        ans += (long long)top.first.first * (long long)cnt;
        my_time = top.first.second;

        if(!counters.empty())
            if(top.first.second != counters.top().first.second)
                push();
        if(counters.empty()) push();
        if(K <= 1) push();
    }
    cout<<ans<<"\n";
}
