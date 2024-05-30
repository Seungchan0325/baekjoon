#include <bits/stdc++.h>

using namespace std;

int main()
{
    int X;
    string s;
    cin >> X;
    cin >> s;

    int sum = 0;
    for(int i = 0; i < s.size() - 1; i++) {
        if(s[i] != s[i+1]) {
            i++;
            continue;
        }

        if(s[i] == 'W') sum--;
        else sum++;

        if(abs(sum) > X) {
            cout << i;
            return 0;
        }
    }

    if(s.back() == 'W') sum--;
    else sum++;
    if(abs(sum) > X) {
        cout << s.size() - 1;
    } else {
        cout << s.size();
    }
}