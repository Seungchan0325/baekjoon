#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>

using namespace std;

const int MAXL = 21;
const int MAXN = 1<<MAXL;

int L, Q, tox[MAXN], ldp[MAXN], rdp[MAXN];
char S[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> L >> Q;
    for(int i = 0; i < 1<<L; i++) {
        char c; cin >> c;
        tox[i] = c - '0';
    }
    for(int i = 0; i < 1<<L; i++) ldp[i] = rdp[i] = tox[i];
    for(int i = 0; i < L; i++) {
        for(int j = 0; j < 1<<L; j++) {
            if(j&(1<<i)) ldp[j] += ldp[j^(1<<i)];
        }
        for(int j = (1<<L)-1; j >= 0; j--) {
            if(~j&(1<<i)) rdp[j] += rdp[j^(1<<i)];
        }
    }
    
    while(Q--) {
        cin >> S;
        reverse(S, S+L);
        vector<int> zeros, ones, noinfo;
        for(int i = 0; i < L; i++) {
            if(S[i] == '0') zeros.push_back(i);
            else if(S[i] == '1') ones.push_back(i);
            else if(S[i] == '?') noinfo.push_back(i);
        }

        int ans = 0;
        if(noinfo.size() == min({zeros.size(), ones.size(), noinfo.size()})) {
            // cout << "noinfo\n";
            int mask = 0;
            for(int j = 0; j < L; j++) {
                if(S[j] == '1') mask |= 1<<j;
            }
            for(int bit = 0; bit < 1<<noinfo.size(); bit++) {
                int i = mask;
                for(int j = 0; j < noinfo.size(); j++) {
                    if(bit&(1<<j)) i |= 1<<noinfo[j];
                }
                ans += tox[i];
            }
        } else if(zeros.size() == min({zeros.size(), ones.size(), noinfo.size()})) {
            // cout << "zeros\n";
            int mask = 0;
            for(int j = 0; j < L; j++) {
                if(S[j] == '1') mask |= 1<<j;
            }
            for(int bit = 0; bit < 1<<zeros.size(); bit++) {
                int i = mask;
                for(int j = 0; j < zeros.size(); j++) {
                    if(bit&(1<<j)) i |= 1<<zeros[j];
                }
                if(popcount((unsigned)bit)&1) ans -= rdp[i];
                else ans += rdp[i];
            }
        } else if(ones.size() == min({zeros.size(), ones.size(), noinfo.size()})) {
            // cout << "ones\n";
            int mask = 0;
            for(int j = 0; j < L; j++) {
                if(S[j] == '?') mask |= 1<<j;
           }
            for(int bit = 0; bit < 1<<ones.size(); bit++) {
                int i = mask;
                for(int j = 0; j < ones.size(); j++) {
                    if(~bit&(1<<j)) i |= 1<<ones[j];
                }
                if(popcount((unsigned)bit)&1) ans -= ldp[i];
                else ans += ldp[i];
            }
        }
        cout << ans << "\n";
    }
}