#include <bits/stdc++.h>

using namespace std;

bool chk[256];
string x, y, w;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin>>t;
    while(t--) {
        cin>>x>>y>>w;

        int x_first = -1, x_last;
        int y_first = -1, y_last;
        for(int i=0; i<x.size(); i++)
            if(w[0] == x[i])  {
                if(x_first < 0) x_first = i;
                x_last = i;
            }

        for(int i=0; i<y.size(); i++)
            if(w[0] == y[i])  {
                if(y_first < 0) y_first = i;
                y_last = i;
            }

        memset(chk, 0, sizeof(chk));
        bool flag = false;
        for(int i=0; i<x_first; i++) chk[x[i]] = true;
        for(int i=0; i<y_first; i++) flag |= chk[y[i]];
        for(int i=0; i<y_last; i++) flag |= chk[y[i]];

        for(int i=x_first; i<x_last; i++) chk[x[i]] = true;
        for(int i=0; i<y_first; i++) flag |= chk[y[i]];
        for(int i=0; i<y_last; i++) flag |= chk[y[i]];

        memset(chk, 0, sizeof(chk));
        for(int i=x_last+1; i<x.size(); i++) chk[x[i]] = true;
        for(int i=y_last+1; i<y.size(); i++) flag |= chk[y[i]];
        for(int i=y_first+1; i<y.size(); i++) flag |= chk[y[i]];

        for(int i=x_first+1; i<x.size(); i++) chk[x[i]] = true;
        for(int i=y_last+1; i<y.size(); i++) flag |= chk[y[i]];
        for(int i=y_first+1; i<y.size(); i++) flag |= chk[y[i]];

        cout<<(int)flag<<"\n";
    }
}