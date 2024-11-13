#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, M, K, A, B;
bool used[4*MAXN];

int main()
{
    cin >> N >> M >> K;
    for(int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        used[a] = used[b] = true;
    }

    cin >> A >> B;
    used[A] = used[B] = true;

    vector<int> v;
    for(int i = 1; i <= 4*N; i++) {
        if(!used[i]) v.push_back(i%K);
    }
    sort(v.begin(), v.end());

    int diff = abs(A%K-B%K);

    int mn = 1e9;
    int ans = 0;
    int j = 1;
    int l = -1, r = 0;
    for(int i = 0; i < v.size(); i++) {
        while(j < v.size() && v[j]-v[i] <= diff) j++;

        if(l == -1) l = j;
        else if(l == i) l++, r++;
        r = max(r+1, j);
        if(j == v.size() || r == v.size()) break;
        ans++;
    }
    
    ans = min(ans, M-1);
    cout << ans;
}