#include <bits/stdc++.h>

using namespace std;

int arr[(int)1e6+1];
int main() {
    stack<pair<int, int>> s;
    int n; cin>>n;
    bool flag = false;
    s.push({0, 1e6});
    int prev = 0;
    for(int i=0; i<=n; i++) {
        int v; 
        if(i < n) cin>>v;
        if(i == n) v = 0;

        if(v - prev > 1) flag = true;
        prev = v;

        if(s.top().first > v) {
            int p = s.top().first;
            while(p > v) {
                int a = 1;
                stack<int> ss;
                while(s.top().first == p) {
                    //arr[s.top().second] = a++;
                    ss.push(s.top().second);
                    s.pop();
                }
                while(ss.size()) {
                    arr[ss.top()] = a++; ss.pop();
                }
                p = s.top().first;
            }
        }
        s.push({v, i});
    }

    if(flag)
        cout<<-1;
    else
        for(int i=0; i<n; i++) cout<<arr[i]<<" ";
}
Unknown problem. sumbmit number: 62472169