#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll n, k, q;
vector<int> que[2000];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    bool is_correct_state = true;
    cin>>n>>k>>q;
    for(int i=0; i<n; i++) {
        for(int j=0; j<k; j++) {
            int inp; cin>>inp; inp--;
            if(inp != i) {
                que[i].push_back(inp);
                is_correct_state = false;
            }
        }
    }

    ll min_q = 0;
    bool flag = true;
    while(flag && !is_correct_state) {
        flag = false;
        for(int i=0; i<n; i++) {
            if(que[i].empty()) que[i].push_back(i);
            if((i+1)%n != que[i].back())
                que[(i+1)%n].push_back(que[i].back());
            que[i].pop_back();
            if(!que[i].empty()) flag = true;
        }
        min_q++;
    }

    //cout<<min_q<<"\n";
    bool is_possible = q >= min_q;
    cout<<(int)is_possible;
}