#include <bits/stdc++.h>

using namespace std;

int main() {
    int min1 = 2001;
    int a; cin >> a;
    min1 = min(a, min1);
    cin >> a;
    min1 = min(a, min1);
    cin >> a;
    min1 = min(a, min1);
    
    int min2 = 2001;
    cin >> a;
    min2 = min(a, min2);
    cin >> a;
    min2 = min(a, min2);
    
    cout << min1 + min2 - 50;
}