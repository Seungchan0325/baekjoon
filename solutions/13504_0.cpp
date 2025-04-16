#include <bits/stdc++.h>

using namespace std;

int DnC(vector<int> v0, vector<int> v1, int depth)
{
    if(v0.size() == 1 && v1.size() == 1) return v0[0] ^ v1[0];
    if(v0.empty() && v1.empty()) return 0;
    if(depth == -1) return 0;
    vector<int> s0, s1, t0, t1;
    for(auto i : v0) {
        if(i&(1<<depth)) s1.push_back(i);
        else s0.push_back(i);
    }
    for(auto i : v1) {
        if(i&(1<<depth)) t1.push_back(i);
        else t0.push_back(i);
    }
    if((s0.empty() || t1.empty()) && (s1.empty() || t0.empty())) return DnC(v0, v1, depth-1);
    return max(DnC(s0, t1, depth-1), DnC(s1, t0, depth-1));
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
        vector<int> v;
        v.reserve(n+1);
        v.push_back(0);
        for(auto i : a) {
            v.push_back(v.back() ^ i);
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        int ans = DnC(v, v, 31);
        cout << ans << "\n";
    }
}