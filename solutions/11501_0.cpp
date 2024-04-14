#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        vector<int> v(N);
        priority_queue<pair<int, int>> pq;
        for(int i = 0; i < N; i++) {
            int x;
            cin >> x;
            v[i] = x;
            pq.emplace(x, i);
        }

        ll ans = 0;
        for(int i = 0; i < N; i++) {
            while(pq.size() && pq.top().second <= i) pq.pop();
            if(v[i] < pq.top().first) ans += pq.top().first - v[i];
        }

        cout << ans << "\n";
    }
}