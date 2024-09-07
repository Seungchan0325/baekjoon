#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, Q;
string s;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> s;
    N = s.size();
    bitset<MAXN> bit[26];
    for(int i = 0; i < N; i++) {
        bit[s[i]-'a'].set(i);
    }

    cin >> Q;
    while(Q--) {
        string op;
        cin >> op;
        char s = op.front();
        char e = op.back();
        int len = stoi(op.substr(1, op.size()-2)) + 1;

        cout << (bit[s-'a'] & (bit[e-'a'] >> len)).count() << "\n";
    }
}