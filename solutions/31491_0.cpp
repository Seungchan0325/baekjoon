#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, P, cnt[MAXN];

int main()
{
    cin >> N >> P;
    for(int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        cnt[a]++;
        cnt[b]++;
    }

    int leaves = 0;
    for(int i = 0; i < N; i++) {
        if(cnt[i] == 1) {
            leaves++;
        }
    }

    int ans = 2 * (P / leaves);
    for(int i = 1; i <= 2 && i <= P % leaves; i++) {
        ans++;
    }
    cout << ans;
}