#include <bits/stdc++.h>

using namespace std;

int N, M;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    vector<pair<int, int>> LP(N);
    for(int i = 0; i < N; i++) {
        cin >> LP[i].first >> LP[i].second;
    }
    vector<int> t(M);
    for(auto& i : t) cin >> i;
    sort(t.begin(), t.end(), greater<>());
    sort(LP.begin(), LP.end(), greater<>());

    long long ans = 0;
    int sum = 0;
    int j = 0;
    priority_queue<int> pq;
    for(int i = 0; i < M; i++) {
        while(pq.size() <= sum) {
            pq.push(LP[j].second);
            j++;
        }
        ans += pq.top();
        pq.pop();
        sum += t[i]-1;
    }
    cout << ans;
}