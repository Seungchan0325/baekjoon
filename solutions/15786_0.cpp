#include <bits/stdc++.h>

using namespace std;

int N, M;
string s;

int main()
{
    cin >> N >> M;
    cin >> s;
    while(M--) {
        string ss;
        cin >> ss;

        int idx = 0;
        for(char c : ss) {
            if(c == s[idx] && idx < N) idx++;
        }

        if(idx == N) cout << "true\n";
        else cout << "false\n";
    }
}