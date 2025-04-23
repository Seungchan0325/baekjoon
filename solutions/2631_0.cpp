#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& i : a) cin >> i;

    vector<int> lis;
    for(auto i : a) {
        if(lis.empty() || lis.back() < i) lis.push_back(i);
        else *lower_bound(lis.begin(), lis.end(), i) = i;
    }
    cout << n - ssize(lis) << "\n";
}