#include <bits/stdc++.h>

using namespace std;

bool knight(string prv, string now)
{
    return abs(prv[0] - now[0]) + abs(prv[1] - now[1]) != 3 || abs(prv[0] - now[0]) >= 3 || abs(prv[1] - now[1]) >= 3;
}

int main()
{
    vector<string> v;
    string s;
    while(cin >> s) {
        v.push_back(s);
    }

    bool isvalid = true;
    if(knight(v.front(), v.back())) isvalid = false;

    for(int i = 1; i < v.size(); i++) {
        if(knight(v[i-1], v[i])) isvalid = false;
    }

    sort(v.begin(), v.end());
    if(unique(v.begin(), v.end()) != v.end()) isvalid = false;

    cout << (const char*)(isvalid ? "Valid" : "Invalid");
}