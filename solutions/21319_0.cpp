#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 5;
const int MAXN = 200005;

int N, A[MAXN];

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    vector<int> ans;

    int mx = 0;
    for(int i = N; i >= 1; i--) {
        if(A[i-1] < A[i] && A[i] + i - 1 > mx) {
            ans.push_back(i);
        }
        mx = max(mx - 1, A[i]);
    }

    reverse(ans.begin(), ans.end());
    for(auto i : ans) cout << i << " ";
    if(ans.empty()) cout << -1;
}