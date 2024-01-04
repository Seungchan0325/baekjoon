#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int n;
int points[MAXN];
int dp1[MAXN], dp2[MAXN];
vector<int> tree[MAXN];
priority_queue<int, vector<int>, greater<>> pq;

void dp(int node, int parent) {
    dp1[node] = points[node];
    dp2[node] = 0;

    for(auto ch : tree[node]) {
        if(ch == parent) continue;

        dp(ch, node);
        dp1[node] += max(dp2[ch], 0);
        dp2[node] += max({dp1[ch], dp2[ch], 0});
    }
}

void restruct(int node, int parent, bool included) {
    if(included) pq.push(node);
    for(auto ch : tree[node]) {
        if(ch == parent) continue;

        if(included) {
            if(0 < dp2[ch])
                restruct(ch, node, false);
        } else {
            if(max({dp1[ch], dp2[ch], 0}) == 0) continue;

            if(dp1[ch] > dp2[ch]) restruct(ch, node, true);
            else restruct(ch, node, false);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> points[i];
    }
    for(int i = 2; i <= n; i++) {
        int boss; cin >> boss;
        tree[boss].push_back(i);
    }

    dp(1, -1);

    cout << dp1[1] << " " << dp2[1] << "\n";
    restruct(1, -1, true);
    while(!pq.empty()) {
        cout << pq.top() << " "; pq.pop(); 
    }
    cout << "-1 \n";

    restruct(1, -1, false);
    while(!pq.empty()) {
        cout << pq.top() << " "; pq.pop(); 
    }
    cout << "-1 \n";
}