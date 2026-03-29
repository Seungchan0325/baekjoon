#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    string S;
    cin >> N >> S;
    string s;
    for(int i = 0; i < N; i++) {
        if(s.size() >= 1 && s.back() == S[i]) s.pop_back();
        else if(s.size() >= 2 && s.end()[-2] == S[i]) s.pop_back(), s.pop_back();
        else s.push_back(S[i]);
    }
    if(s.empty()) cout << "-1\n";
    else cout << s << "\n";
}
