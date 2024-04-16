#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

vector<int> lis(const vector<int>& arr) {
    vector<int> v;
    v.push_back(-1);

    vector<int> pos(arr.size());
    for(int i=0; i<arr.size(); i++) {
        if(v.back() < arr[i]) {
            v.push_back(arr[i]);
            pos[i] = v.size() - 1;
        } else {
            auto it = lower_bound(v.begin(), v.end(), arr[i]);
            *it = arr[i];
            pos[i] = it - v.begin();
        }
    }

    vector<int> ret;
    int last = v.size() - 1;
    for(int i = arr.size() - 1; i >= 0; i--) {
        if(last == pos[i]) {
            last--;
            ret.push_back(arr[i]);
        }
    }

    reverse(ret.begin(), ret.end());

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin>>n;
    vector<int> v(n);
    for(auto& i : v) cin >> i;
    auto result = lis(v);

    cout << result.size() << "\n";
    for(auto i : result) cout << i << " ";
}