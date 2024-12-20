#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    queue<int> v[2];
    int cnt[3] = {};
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if(a%3 == 0) v[0].push(a);
        else v[1].push(a);
        cnt[a%3]++;
    }
    if((int)v[0].size() - (int)v[1].size() > 1) {
        cout << "-1";
        return 0;
    }

    if(cnt[0] == 0 && cnt[1] != 0 && cnt[2] != 0) {
        cout << "-1";
        return 0;
    }

    deque<int> dq;
    int idx = 0;
    while(v[0].size()) {
        dq.push_back(v[idx].front()); v[idx].pop();
        idx ^= 1;
    }
    while(v[1].size()) {
        if(v[1].front() % 3 == 1) {
            dq.push_back(v[1].front());
        } else {
            dq.push_front(v[1].front());
        }
        v[1].pop();
    }
    for(int i = 0; i < dq.size(); i++) {
        cout << dq[i] << " ";
    }
}