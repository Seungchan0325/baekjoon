#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include <cmath>
#include <memory.h>

using namespace std;

int t, a, b, chk[10000];
string ans;

int d(int r) {
    return (2*r) % 10000;
}

int s(int r) {
    return (r + 99999) % 10000;
}

int l(int r) {
    return (r % 1000) * 10 + r / 1000;
}

int r(int r) {
    return r / 10 + (r % 10) * 1000;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>t;
    while(t--) {
        cin>>a>>b;

        memset(chk, 0, sizeof(chk));
        queue<pair<int, string>> q;
        q.push({a, ""});
        chk[a] = true;
        while(!q.empty()) {
            int re = q.front().first; 
            string command = q.front().second;
            q.pop();

            if(re == b) {
                ans = command;
                break;
            }

            int nd;
            nd = d(re);
            if(!chk[nd]) q.push({nd, command + "D"});
            chk[nd] = true;
            nd = s(re);
            if(!chk[nd]) q.push({nd, command + "S"});
            chk[nd] = true;
            nd = l(re);
            if(!chk[nd]) q.push({nd, command + "L"});
            chk[nd] = true;
            nd = r(re);
            if(!chk[nd]) q.push({nd, command + "R"});
            chk[nd] = true;
        }
        cout<<ans<<"\n";
    }
}