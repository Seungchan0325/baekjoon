#include <bits/stdc++.h>

using namespace std;

struct _comp {
    bool operator()(string& a, string& b) {
        return (a + b) > (b + a);
    }
};

int n;
priority_queue<string, vector<string>, _comp> pq;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n;
    for(int i=0; i<n; i++) {
        string tmp; cin>>tmp;
        pq.push(tmp);
    }

    while(!pq.empty()) {
        string top = pq.top(); pq.pop();
        cout<<top[0];
        top.erase(top.begin());
        if(!top.empty())
            pq.push(top);
    }
}