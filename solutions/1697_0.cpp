#include <limits>
#include <iostream>
#include <utility>
#include <queue>

using namespace std;

int n, k, min_cost = numeric_limits<int>::max();
bool visited[100001] = {0};

bool check(int a) {
    if(a < 0 || a > 100000 || visited[a])
        return false;
    return true;
}

int main() {
    cin >> n >> k;

    queue<pair<int, int>> que;
    que.push({n, 0});
    visited[n] = true;

    while(!que.empty()) {
        auto f = que.front(); que.pop();
        auto pos = f.first,
             t = f.second;
        int a[] = {pos * 2, pos + 1, pos - 1};

        if(pos == k) {
            min_cost = t;
            break;
        }
        
        for(auto& i : a) {
            if(!check(i)) continue;

            visited[i] = true;
            que.push({i, t + 1});
        }
    }

    cout << min_cost << endl;
}