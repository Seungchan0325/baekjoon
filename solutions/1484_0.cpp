#include <bits/stdc++.h>

using namespace std;

int main()
{
    int G;
    cin >> G;
    bool exist = false;;
    long long s = 1, e = 1;
    while(true) {
        if(e*e - s*s == G) {
            cout << e << "\n";
            exist = true;
        }
        if(e - s == 1 && e*e - s*s > G) break;
        if(e*e - s*s < G) e++;
        else s++;
    }
    if(!exist) cout << -1;
}