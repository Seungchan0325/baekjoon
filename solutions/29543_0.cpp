#include <bits/stdc++.h>

using namespace std;

string ans[100] = {
    "9",
    "99",
    "989",
    "9889",
    "97679",
    "976679",
    "9643469",
    "96433469",
};

int main()
{
    int l;
    cin >> l;

    if(l <= 8) cout << ans[l-1];
    else cout << "-1";
}