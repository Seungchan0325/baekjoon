#include <bits/stdc++.h>

using namespace std;

const int dirr[] = {0, 0, 1, -1};
const int dirc[] = {1, -1, 0, 0};

int n;
bool visited[5][5];
vector<pair<int, int>> pieces;

// test 0 <= i < x
bool in_range(int i, int x) {
    return 0 <= i && i < x;
}

int dfs(int r, int c, vector<pair<int, int>> dst) {
    dst.emplace_back(r, c);
    if(dst.size() == n) {
        int ret = 1e8;
        sort(dst.begin(), dst.end());
        do {
            int sum = 0;
            for(int i = 0; i < n; i++) {
                sum += abs(pieces[i].first - dst[i].first) + abs(pieces[i].second - dst[i].second);
            }
            ret = min(sum, ret);
        } while(next_permutation(dst.begin(), dst.end()));
        return ret;
    }

    int ret = 1e8;
    for(auto [r, c] : dst) {
        for(int i = 0; i < 4; i++) {
            int nr = r + dirr[i];
            int nc = c + dirc[i];
            if(!in_range(nr, 5) || !in_range(nc, 5) || visited[nr][nc]) continue;

            visited[nr][nc] = true;
            ret = min(dfs(nr, nc, dst), ret);
            visited[nr][nc] = false;
        }
    }

    return ret;
}

int main() {
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++) {
            char c; cin >> c;
            if(c == '*') pieces.emplace_back(i, j);
        }
    n = pieces.size();

    int result = 1e8;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++) {
            visited[i][j] = true;
            result = min(dfs(i, j, {}), result);
            visited[i][j] = false;
        }

    cout << result << "\n";
}