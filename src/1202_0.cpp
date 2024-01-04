#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int INF = 98654321;

int n, k, c[300005];
pii jewels[300005];
priority_queue<int, vector<int>, less<int>> pq;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>k;
    for(int i = 0; i < n; i++) cin>>jewels[i].first>>jewels[i].second;
    for(int i = 0; i < k; i++) cin>>c[i];

    sort(jewels, jewels + n);
    sort(c, c + k);
    
    int last = 0;
    long long sum = 0;
    for(int i = 0; i < k; i++) {
        while(last < n && jewels[last].first <= c[i]) {
            pq.push(jewels[last].second);
            last++;
        }
        if(!pq.empty()) {
            sum += pq.top();
            pq.pop();
        }
    }

    cout<<sum;
}