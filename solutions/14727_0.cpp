#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;

    long long result = 0;
    stack<pair<int, int>> s;
    for(int i = 0; i < n; i++) {
        int height;
        int cnt = 0;

        cin >> height;

        while(!s.empty() && height <= s.top().first) {
            cnt += s.top().second;
            result = max((long long)s.top().first * cnt, result);
            s.pop();
        }
        s.emplace(height, cnt + 1);
    }
    int height;
    int cnt = 0;
    while(!s.empty()) {
        height = s.top().first;
        cnt += s.top().second;
        result = max((long long)height * cnt, result);
        s.pop();
    }

    cout << result;
}