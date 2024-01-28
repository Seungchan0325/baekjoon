#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5000005;

int n, l;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    cin >> n >> l;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pq.emplace(x, i);

        while(!pq.empty() && pq.top().second < i - l + 1) pq.pop();
        cout << pq.top().first << " ";
    }
}