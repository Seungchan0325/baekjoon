#include <bits/stdc++.h>

using namespace std;

int main()
{
    int k;
    cin >> k;
    vector<string> v(k);
    for(auto& i : v) cin >> i;
    sort(v.begin(), v.end(), [](string& a, string& b){
        return a + b > b + a;
    });
    if(v[0][0] == '0') cout << '0';
    else for(auto& i : v) cout << i;
}