#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int N, ans[MAXN], color = 1;

int main()
{
    cin >> N;

    ans[1] = color++;
    for(int i = 2; i <= N; i++) {
        if(ans[i] != 0) continue;
        ans[i] = color;
        for(int j = i+i; j <= N; j+=i) {
            ans[j] = color;
        }
        color++;
    }

    cout << color - 1 << "\n";
    for(int i = 1; i <= N; i++) {
        cout << ans[i] << " ";
    }
}