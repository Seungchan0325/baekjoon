#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 100;

int n, m;
vector<pair<int, int>> trash;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int is_trash;
            cin >> is_trash;
            if(is_trash) trash.emplace_back(i, j);
        }
    }

    vector<int> v;
    for(int i = 0; i < trash.size(); i++) {
        int max_idx = -1;
        for(int j = 0; j < v.size(); j++) {
            if(v[j] <= trash[i].second && (max_idx == -1 || v[max_idx] < v[j])) {
                max_idx = j;
            }
        }

        if(0 <= max_idx) v[max_idx] = trash[i].second;
        else v.push_back(trash[i].second);
    }
    cout << v.size();
}