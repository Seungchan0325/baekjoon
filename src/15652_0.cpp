#include <bits/stdc++.h>

using namespace std;

int n, m;

void f(vector<int> v) {
    if(v.size() == m) {
        for(int i : v)
            cout << i << " ";
        cout << "\n";
        return;
    }
    int start = 1;
    if(!v.empty()) start = v.back();
    for(int i = start; i <= n; i++) {
        v.push_back(i);
        f(v);
        v.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    f(vector<int>());
}