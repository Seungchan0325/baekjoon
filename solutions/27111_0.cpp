#include <bits/stdc++.h>

using namespace std;

int n;

int main()
{
    cin >> n;
    set<int> s;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if(b) {
            if(s.count(a)) ans++;
            s.insert(a);
        } else {
            if(!s.count(a)) ans++;
            s.erase(a);
        }
    }
    ans += s.size();    
    cout << ans;
}