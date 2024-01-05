#include <bits/stdc++.h>

using namespace std;

int n, q, arr[100005], psum[100005];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; i++) cin >> arr[i];
    for(int i = 1; i <= n - 1; i++) {
        if(arr[i + 1] < arr[i]) psum[i] = 1;
    }
    for(int i = 1; i <= n; i++) {
        psum[i] += psum[i - 1];
    }
    cin >> q;
    while(q--) {
        int x, y;
        cin >> x >> y;
        int result = psum[y - 1] - psum[x - 1];
        cout << result << "\n";
    }
}