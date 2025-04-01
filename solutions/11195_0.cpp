#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    cin >> s;
    map<char, int> m;
    for(auto c : s) m[c]++;
    int c = 0;
    for(auto [k, i] : m) if(i&1) c++;
    cout << max(c-1, 0) << "\n";
}