#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<int> a(20);
    iota(a.begin(), a.end(), 1);
    for(int i = 0; i < 10; i++) {
        int l, r;
        cin >> l >> r;
        reverse(a.begin()+l-1, a.begin()+r);
    }
    for(auto i : a) cout << i << " ";
}
