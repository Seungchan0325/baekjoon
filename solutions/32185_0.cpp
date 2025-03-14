#include <bits/stdc++.h>

using namespace std;

int N, M, s0;

int main()
{
    cin >> N >> M;
    vector<pair<int, int>> a;
    for(int i = 0; i <= N; i++) {
        int v, s, p;
        cin >> v >> s >> p;
        if(i == 0) s0 = v + s + p;
        else if(v + s + p <= s0)
            a.emplace_back(v + s + p, i);
    }
    sort(a.begin(), a.end(), greater<>());
    cout << "0 ";
    for(int i = 0; i + 1 < M && i < a.size(); i++)
        cout << a[i].second << " ";
}