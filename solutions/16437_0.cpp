#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

int N;
vector<ll> sheeps;
vector<vector<int>> connected;

ll dfs(int cur) {
    ll ans = sheeps[cur];
    for (auto &i : connected[cur])
        ans += dfs(i);
            
    return max(ans, (ll)0);
}

int main() {
    cin >> N;
    sheeps.resize(N);
    connected.resize(N);
    for (int i = 1; i < N; i++) {
        char t;
        ll a, p;
        cin >> t >> a >> p;
        
        if (t == 'W')
            sheeps[i] = -a;
        else if(t == 'S')
            sheeps[i] = a;
            
        p--;
            
        connected[p].push_back(i);
    }
    
    cout << dfs(0) << endl;
}