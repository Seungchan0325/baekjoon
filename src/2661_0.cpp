#include <bits/stdc++.h>

using namespace std;

bool is_good_sequence(vector<int> s) {
    for(int i=0; i<s.size(); i++)
        for(int j=i+1; j<s.size(); j++) {
            int len = j - i;
            if(len + j - 1 >= s.size()) continue;

            if(vector<int>(s.begin() + i, s.begin() + i + len) == vector<int>(s.begin() + j, s.begin() + j + len))
                return false;
        }
    
    return true;
}

vector<int> ans;
void f(int n, vector<int> s) {
    if(s.size() == n) {
        ans = min(s, ans);
        return;
    }

    if(s > ans) return;

    for(int i=1; i<=3; i++) {
        s.push_back(i);
        if(is_good_sequence(s))
            f(n, s);
        s.pop_back();
    }
}

int main() {
    int n; cin>>n;
    ans = {4};
    f(n, vector<int>());
    for(int i : ans) cout<<i;
}