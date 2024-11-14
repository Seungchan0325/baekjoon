#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXM = 10000005;

int N, M, K, T, X[MAXN], Y[MAXN], s[MAXM];

int main()
{
    cin >> N >> M >> K >> T;
    for(int i = 1; i <= N; i++) {
        cin >> X[i] >> Y[i];
        s[X[i]]++;
        s[Y[i]]--;
    }
    for(int i = 1; i <= M; i++) s[i] += s[i-1];

    int ans = 0;
    int r = -1;
    int k = 0;
    int cnt = 0;
    int j = -1;
    for(int i = 0; i < M; i++) {
        while(j+1 < M) {
            if(s[j+1]) {
                if(cnt) k++;
                cnt = 0;
            } else {
                if(k == K) break;
                cnt++;
                if(cnt == T) {
                    k++;
                    cnt = 0;
                }
            }
            j++;
        }

        ans = max(ans, j - i + 1);

        r = max(r, i);
        while(r < j+1 && !s[r]) {
            r++;
        }
        if(!s[i]) {
            if(r > j) {
                if(cnt == 0) {
                    k--;
                    cnt = T-1;
                } else {
                    cnt--;
                }
            }
            else if((r - i) % T == 1 || T == 1) {
                k--;
            }
        }
    }

    cout << ans;
}