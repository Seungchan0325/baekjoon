#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x, b;
    cin >> x >> b;
    vector<int> v;
    bool isneg = false;

    if(b > 0 && x < 0) x = -x, isneg = true;

    while(x != 0) {
        if(x % b < 0) {
            if(b < 0) {
                v.emplace_back(-b + x % b);
                x += b;
                x /= b;
            } else {
                v.emplace_back(b + x % b);
                x -= b;
                x /= b;
            }
        } else {
            v.emplace_back(x % b);
            x /= b;
        }
    }

    if(v.empty()) v.push_back(0);

    if(isneg) cout << "-";
    for(int i=(int)v.size()-1; i >= 0; i--) {
        cout << v[i];
    }
}