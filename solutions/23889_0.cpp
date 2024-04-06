#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, M, K, x[MAXN], s[MAXN];

int main()
{
    cin >> N >> M >> K;
    for(int i = 1; i <= N; i++) {
        cin >> x[i];
    }
    for(int i = 0; i < K; i++) {
        cin >> s[i];
    }
    s[K] = N+1;

    vector<pair<int, int>> v;
    for(int i = 0; i < K; i++) {
        int sum = 0;
        for(int j = s[i]; j < s[i+1]; j++) {
            sum += x[j];
        }

        v.emplace_back(sum, s[i]);
    }

    sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b) {
        if(a.first != b.first) return a.first > b.first;
        return a.second < b.second;
    });

    vector<int> ans;
    for(int i = 0; i < M; i++) {
        ans.push_back(v[i].second);
    }
    sort(ans.begin(), ans.end());
    for(auto i : ans) cout << i << "\n";
}