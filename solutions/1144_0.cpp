#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10;

int N, M, A[MAXN][MAXN];
map<vector<int>, int> cache[MAXN][MAXN];

vector<int> normalize(vector<int> v)
{
    int n = v.size();
    int idx[10] = {0, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int j = 1;
    for(auto i : v) {
        if(idx[i] == -1) idx[i] = j++;
    }
    vector<int> vv = v;
    for(auto& i : vv) {
        i = idx[i];
    }
    return vv;
}

int dp(int i, int j, vector<int> state)
{
    if(i > N) {
        state.erase(remove(state.begin(), state.end(), 0), state.end());
        sort(state.begin(), state.end());
        state.erase(unique(state.begin(), state.end()), state.end());
        if(state.size() <= 1) return 0;
        else return 1e9;
    }
    if(j > M) return dp(i+1, 1, state);
    state = normalize(state);
    if(cache[i][j].count(state)) return cache[i][j][state];

    int& ret = cache[i][j][state];
    ret = 1e9;
    int num = *max_element(state.begin(), state.end());

    if(state[0] == 0 || find(state.begin()+1, state.end(), state[0]) != state.end()) {
        auto nstate = state;
        nstate.erase(nstate.begin());
        nstate.push_back(0);
        ret = min(ret, dp(i, j+1, nstate));
    }

    auto nstate = state;
    int up = state[0];
    int left = -1;
    if(j > 1) left = state.back();
    if(left > 0) {
        nstate.push_back(left);
        if(up > 0) replace(nstate.begin(), nstate.end(), up, left);
    } else if(up > 0) {
        nstate.push_back(up);
    } else {
        nstate.push_back(num+1);
    }
    nstate.erase(nstate.begin());
    ret = min(ret, dp(i, j+1, nstate) + A[i][j]);

    state.erase(remove(state.begin(), state.end(), 0), state.end());
    sort(state.begin(), state.end());
    state.erase(unique(state.begin(), state.end()), state.end());
    if(state.size() <= 1) ret = min(ret, 0);
    
    return ret;
}

int main()
{
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> A[i][j];
        }
    }
    int ans = dp(1, 1, vector<int>(M, 0));
    cout << ans << "\n";
    // for(int i = 1; i <= N; i++) {
    //     for(int j = 1; j <= M; j++) {
    //         cout << i << " " << j << "\n";
    //         for(auto [key, v] : cache[i][j]) {
    //             cout << "[";
    //             for(auto k : key) cout << k << " ";
    //             cout << "] " << v << "\n";
    //         }
    //     }
    // }
}