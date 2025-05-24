#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;
const int MAXA = 5050505;

bool sieve[MAXA];
int n, a[MAXN], mn;

int main()
{
    for(int i = 2; i < MAXA; i++) {
        for(int j = i+i; j < MAXA; j += i) {
            sieve[j] = true;
        }
    }
    vector<int> v[4];
    for(int i = 1; i < MAXA; i++) if(!sieve[i]) v[i%4].push_back(i);
    int t;
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 1; i <= n; i++) cin >> a[i];
        int mnj = 1e9;
        int mnji = -1;
        int mnn = 1e9;
        int mnni = -1;
        for(int i = 1; i <= n; i++) {
            if(a[i] % 4 == 0) tie(mnn, mnni) = min(pair(mnn, mnni), pair(a[i]/4+1, i));
            else {
                auto& vv = v[a[i]%4];
                int idx = upper_bound(vv.begin(), vv.end(), a[i]) - vv.begin() - 1;
                int turns = 2 * (a[i] / 4) - 2 * (vv[idx] / 4) + 1;
                tie(mnj, mnji) = min(pair(mnj, mnji), pair((turns+1)/2, i));
            }
        }
        if(pair(mnj, mnji) < pair(mnn, mnni)) goto John;
        else goto Nhoj;

        John:; cout << "Farmer John\n"; continue;
        Nhoj:; cout << "Farmer Nhoj\n"; continue;
    }
}