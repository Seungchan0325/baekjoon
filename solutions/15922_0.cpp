#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;

int main()
{
    int N;
    cin >> N;
    int ans = 0;
    int py = -INF;
    while(N--) {
        int x, y;
        cin >> x >> y;
        if(py < x) {
            ans += (y - x);
            py = y;
        } else {
            if(py < y) {
                ans += (y - py);
                py = y;
            }
        }
    }
    cout << ans;
}