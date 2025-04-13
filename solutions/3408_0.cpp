#include <bits/stdc++.h>

using namespace std;

bool DnC(int s, int e, vector<int>& a, vector<int>& p, vector<int>& n)
{
    if(s >= e) return true;
    int l = s;
    int r = e;
    int m = -1;
    while(l <= r) {
        if(p[l] < s && e < n[l]) m = l;
        if(p[r] < s && e < n[r]) m = r;
        if(m != -1) break;
        l++; r--;
    }
    if(m == -1) return false;
    return DnC(s, m-1, a, p, n) && DnC(m+1, e, a, p, n);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(auto& i : a) cin >> i;
        auto v = a;
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        for(auto& i : a) i = lower_bound(v.begin(), v.end(), i) - v.begin();

        vector<int> lst(n, -1), l(n), r(n);
        for(int i = 0; i < n; i++) {
            l[i] = lst[a[i]];
            lst[a[i]] = i;
        }
        lst = vector<int>(n, n);
        for(int i = n-1; i >= 0; i--) {
            r[i] = lst[a[i]];
            lst[a[i]] = i;
        }

        if(DnC(0, n-1, a, l, r)) cout << "non-boring\n";
        else cout << "boring\n";
    }
}