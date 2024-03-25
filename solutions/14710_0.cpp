#include <bits/stdc++.h>

using namespace std;

int h, m, t1, t2;

int main()
{
    cin >> t1 >> t2;
    m = 2 * (t1 % (360 / 12));
    if(t2 % (360 / 60) == 0 && m == t2 / (360 / 60)) cout << "O";
    else cout << "X";
}