#include <bits/stdc++.h>

using namespace std;

int N;
string s;

bool check(int x)
{
    vector<int> J, O, I;
    for(int i = 0; i < N; i++) {
        if(s[i] == 'J') J.push_back(i);
        else if(s[i] == 'O') O.push_back(i);
        else if(s[i] == 'I') I.push_back(i);
        else assert(0);
    }

    vector<int> v;

    for(int i = O.size() - 1; i >= 0; i--) {
        if(v.size() == x) break;
        if(I.empty() || I.back() < O[i]) continue;
        I.pop_back();
        v.push_back(O[i]);
    }

    if(v.size() < x) return false;

    reverse(v.begin(), v.end());

    int cnt = 0;
    vector<int> merged(I.size() + J.size());
    merge(I.begin(), I.end(),
          J.begin(), J.end(),
          merged.begin());

    int idx = 0;
    for(auto o : v) {
        if(idx < merged.size() && merged[idx] < o) {
            idx++;
            cnt++;
        }
    }

    return x <= cnt;
}

int main()
{
    cin >> N;
    cin >> s;

    int lo = 0, hi = N/3 + 1;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(check(mid)) lo = mid;
        else hi = mid;
    }

    cout << lo;
}