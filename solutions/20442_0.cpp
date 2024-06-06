#include <bits/stdc++.h>

using namespace std;

int N;
string s;
vector<int> v;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> s;
    N = s.size();

    for(int i = 0; i < N; i++) {
        if(s[i] == 'R') {
            v.push_back(i);
        }
    }

    int ans = 0;
    int lo = 0, lcnt = 0;
    int hi = N-1, hcnt = 0;
    while(lo <= hi) {
        while(lo < N && s[lo] == 'K') {
            lo++;
            lcnt++;
        }

        while(0 <= hi && s[hi] == 'K') {
            hi--;
            hcnt++;
        }

        if(lo > hi) break;

        int cand = 2*min(lcnt, hcnt) + (upper_bound(v.begin(), v.end(), hi) - lower_bound(v.begin(), v.end(), lo));
        ans = max(cand, ans);

        if(lcnt < hcnt) {
            lo++;
        } else {
            hi--;
        }
    }

    cout << ans;
}