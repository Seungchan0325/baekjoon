#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int k = 2000;
    vector<int> v(k);
    for(int i = k/2; i < k; i++) v[i] = 1;
    for(int i = k/2-1; i >= 0; i--) v[i] = k/2;
    cout << k << "\n";
    for(int i : v) cout << i << " ";
}