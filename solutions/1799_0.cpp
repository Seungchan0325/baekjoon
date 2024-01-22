#include <bits/stdc++.h>

using namespace std;

int n, ans, max_idx, board[10][10];
vector<pair<int, int>> pos;

void solve(int idx)
{
    if(idx == max_idx) {
        ans = max((int)pos.size(), ans);
        return;
    }

    int r = max(idx - n + 1, 0);
    int c = min(idx, n - 1);
    while(r < n && 0 <= c) {
        if(board[r][c] == 1) {
            bool is_possible = true;
            for(auto [pr, pc] : pos) {
                if(pr != -1 && abs(pr - r) == abs(pc - c)) {
                    is_possible = false;
                    break;
                }
            }
            if(is_possible && max_idx - idx + pos.size() > ans) {
                pos.emplace_back(r, c);
                solve(idx + 1);
                pos.pop_back();
            }
        }
        r++;
        c--;
    }
    solve(idx + 1);

    return;
}

int main()
{
    cin >> n;
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < n; c++) {
            cin >> board[r][c];
        }
    }

    max_idx = 2 * n - 1;

    solve(0);
    cout << ans;
}