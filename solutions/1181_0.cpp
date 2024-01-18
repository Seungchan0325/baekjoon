#include <bits/stdc++.h>

using namespace std;

bool cmp(const string& a, const string& b) {
    if(a.size() == b.size())
        return a < b;
    return a.size() < b.size();
}

bool cmp2(const string& a, const string& b) {
    return a == b;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin>>n;
    vector<string> inp(n);
    for(auto& i : inp) cin>>i;

    sort(inp.begin(), inp.end(), cmp);
    inp.erase(unique(inp.begin(), inp.end(), cmp2), inp.end());
    for(auto i : inp) cout<<i<<"\n";
}