#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10101;

int N, I, H, R, ans[MAXN];

int main()
{
    cin >> N >> I >> H >> R;
    vector<pair<int, int>> v;
    while(R--) {
        int A, B;
        cin >> A >> B;
        if(A > B) swap(A, B);
        v.emplace_back(A, B);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(auto [l, r] : v) {
        if(l == r) continue;
        ans[l+1]--;
        ans[r]++;
    }
    ans[0] = H;
    for(int i = 1; i <= N; i++) {
        ans[i] += ans[i-1];
        cout << ans[i] << "\n";
    }
}