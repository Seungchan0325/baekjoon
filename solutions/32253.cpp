#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

bool vst[MAXN];
int N, K;
string s;

int main()
{
    cin >> N >> K;
    cin >> s;
    s = ' ' + s;

    vector<int> v;
    for(int i = 1; i < N; i++) {
        if(s[i] != s[i+1]) v.push_back(i);
    }

    vector<pair<int, int>> ans;
    vector<int> remains;

    if(v.size() == 0) {
        cout << "0";
        return 0;
    }

    int j = v.size() / 2;
    for(int i = 0; i < v.size(); i++) {
        if(vst[i]) continue;
        while(j < v.size() && (v[j] - v[i] < K || vst[j])) {
            j++;
        }
        if(j < v.size()) {
            vst[i] = true;
            vst[j] = true;
            ans.emplace_back(v[i]+1, v[j]);
            j++;
        } else {
        }
    }

    for(int i = 0; i < v.size(); i++) {
        if(!vst[i]) remains.push_back(v[i]);
    }
    
    for(auto i : remains) {
        if(i < K && N - i < K) {
            cout << "-1";
            return 0;
        }
        if(i >= K) ans.emplace_back(1, i);
        else ans.emplace_back(i+1, N);
    }

    cout << ans.size() << "\n";
    for(auto [i, j] : ans) cout << i << " " << j << "\n";
}