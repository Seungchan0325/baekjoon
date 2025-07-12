#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, Q, C, c[MAXN], a[MAXN], h[MAXN], b[MAXN], cnt[MAXN], fix[MAXN];

int main()
{
    int t; cin >> t;
    while(t--) {
        bool fail = false;
        cin >> N >> Q >> C;
        for(int i = 1; i <= N; i++) {
            cin >> c[i]; b[i] = 0;
            fix[i] = 1;
            if(c[i] == 0) c[i] = 1, fix[i] = 0;
        }
        for(int i = 1; i <= Q; i++) {
            cin >> a[i] >> h[i];
            b[a[i]] = h[i];
        }

        int j = 1;
        for(int i = 1; i <= N; i = j) {
            if(b[i] == 0) {
                j++;
                continue;
            }
            j = i;
            while(j < b[i]) {
                if(b[j] && b[j] != b[i]) fail = true;
                b[j] = b[i];
                j++;
            }
        }

        int mxbef = 0;
        for(int i = 1; i <= N;) {
            mxbef = max(mxbef, c[i]);
            if(b[i] == 0) {
                i++;
                continue;
            }
            int mxaft = *max_element(c+i, c+b[i]);
            if(mxaft > mxbef) {
                bool assigned = false;
                for(int j = i; j >= 1; j--) {
                    if(b[j] != 0 && b[j] < b[i]) fail = true;
                    if(fix[j]) continue;
                    c[j] = mxaft;
                    assigned = true;
                    break;
                }
                if(!assigned) fail = true;
                mxbef = mxaft;
            }
            if(!fix[b[i]]) {
                c[b[i]] = mxbef+1;
            } else if(c[b[i]] <= mxbef) fail = true;
            i = b[i];
        }

        for(int i = 1; i <= N; i++) if(c[i] > C) fail = true;

        if(fail) cout << "-1\n";
        else {
            for(int i = 1; i <= N; i++) cout << c[i] << " ";
            cout << "\n";
        }
    }
}