#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3005;

int N, psum[MAXN][MAXN], DP[MAXN];

vector<int> ans;

void restruct(int i)
{
    if(i == 0) return;

    int w = 0;
    for(int j = i; j >= 1; j--) {
        w += psum[j][i] + (i-j) - 3*(psum[j][i] - psum[j][j-1]);
        if(DP[i] == DP[j-1] + w) {
            ans.push_back(i - j + 1);
            restruct(j - 1);
            return;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i = 1; i <= N; i++) {
        while(true) {
            int j; cin >> j;
            if(j == 0) break;
            psum[i][j]++;
        }

        for(int j = 1; j <= N; j++) {
            psum[i][j] += psum[i][j-1];
        }
    }

    memset(DP, 0x7F, sizeof(DP));

    DP[0] = 0;
    for(int i = 1; i <= N; i++) {
        int w = 0;
        for(int j = i; j >= 1; j--) {
            w += psum[j][i] + (i-j) - 3*(psum[j][i] - psum[j][j-1]);
            DP[i] = min(DP[i], DP[j-1] + w);
        }
    }

    cout << DP[N] << "\n";

    restruct(N);
    cout << ans.size() << " ";
    reverse(ans.begin(), ans.end());
    for(auto i : ans) cout << i << " ";
}