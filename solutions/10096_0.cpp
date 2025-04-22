#include <bits/stdc++.h>

using namespace std;

int matched(string a, string b)
{
    if(a.size() > b.size()) swap(a, b);
    int m = 0;
    for(auto c : b) {
        if(a[m] == c) m++;
    }
    return m;
}

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    if(~n&1) {
        cout << "NOT POSSIBLE\n";
        return 0;
    }

    string a, b;

    a = s.substr(0, n/2);
    b = s.substr(n/2+1);
    if(matched(a, b) == a.size()) {
        cout << a << "\n";
        return 0;
    }

    int c = 0;
    a = s.substr(0, n/2);
    b = s.substr(n/2);
    if(matched(a, b) == a.size()) c++;
    a = s.substr(0, n/2+1);
    b = s.substr(n/2+1);
    if(matched(a, b) == b.size()) c++;

    if(c >= 2) {
        cout << "NOT UNIQUE\n";
        return 0;
    }

    a = s.substr(0, n/2);
    b = s.substr(n/2);
    if(matched(a, b) == a.size()) {
        cout << a << "\n";
        return 0;
    }
    a = s.substr(0, n/2+1);
    b = s.substr(n/2+1);
    if(matched(a, b) == b.size()) {
        cout << b << "\n";
        return 0;
    }
    cout << "NOT POSSIBLE\n";
    return 0;
}