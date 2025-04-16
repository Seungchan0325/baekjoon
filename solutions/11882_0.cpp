#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int n, l[MAXN], r[MAXN], t[MAXN];
string s;

int main()
{
    cin >> n;
    cin >> s;
    for(int i = 0; i < n; i++) {
        if(s[i] == '?') {
            cin >> l[i] >> r[i];
        }
    }

    int p = 0;
    long long ans = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') p++, t[i] = 1;
        else if(s[i] == ')') p--, t[i] = 0;
        else {
            p--;
            ans += r[i];
            t[i] = 0;
            pq.emplace(l[i] - r[i], i);
        }
        if(p < 0) {
            t[pq.top().second] = 1;
            ans += pq.top().first; pq.pop();
            p += 2;
        }
    }
    cout << ans << "\n";
    for(int i = 0; i < n; i++) {
        if(t[i] == 1) cout << '(';
        else cout << ')';
    }
}