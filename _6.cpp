#include <bits/stdc++.h>

using namespace std;

int n, cnt[26];
string s;

int main()
{
    cin >> n;
    cin.ignore();
    getline(cin, s);

    for(char c : s)
    {
        if('a' <= c && c <= 'z')
        {
            cnt[c - 'a']++;
        }
    }

    cout << *max_element(cnt, cnt + 26);
}
Unknown problem. sumbmit number: 70423210