#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    int count_ones = 0;
    for(int i = 0; i < n; i++)
    {
        int inp;
        cin >> inp;
        count_ones += inp;
    }

    if(n < 2 * count_ones) cout << "Junhee is cute!";
    else cout << "Junhee is not cute!";
}