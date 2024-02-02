#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int day, cnt = 0;
    cin >> day;
    for(int i = 0; i < 5; i++) {
        int num;
        cin >> num;
        if(day % 10 == num % 10) cnt++;
    }
    cout << cnt;
}