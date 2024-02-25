#include <bits/stdc++.h>

using namespace std;

using llint = long long int;

const int MAXN = 100005;

int N, cnt[35][2];

int main()
{
    cin >> N;
    llint ans = 0;
    for(int i = 1; i <= N; ++i) {
        int A; cin >> A;
        for(int j = 0; j < 32; ++j) {
            if(A & (1<<j)) {
                swap(cnt[j][0], cnt[j][1]);
                cnt[j][1]++;
                ans += (1LL<<j) * cnt[j][1];
            } else {
                ++cnt[j][0];
                ans += (1LL<<j) * cnt[j][1];
            }
        }
    }
    cout << ans;
}