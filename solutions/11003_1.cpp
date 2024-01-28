#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, l;
    cin >> n >> l;
    deque<pair<int, int>> q;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        while(!q.empty() && q.front().second < i - l + 1) q.pop_front();
        while(!q.empty() && x <= q.back().first) q.pop_back();
        q.emplace_back(x, i);
        cout << q.front().first << " ";
    }
}