#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, d;
    cin >> n >> d;
    vector<int> v(n);
    for(auto&i:v) cin >> i;
    sort(v.begin(), v.end());

    int cnt = 0;
    for(int i = 0; i < n;) {
        int j;
        for(j = i; j < n && v[j]-v[i] <= d; j++);
        i = j;
        cnt++;
    }
    cout << cnt << "\n";
}