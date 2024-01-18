#include <bits/stdc++.h>

using namespace std;

int n, m, table[9][9];

bool is_square_number(long long num)
{
    for(long long i = 0; i * i <= num; i++)
    {
        if(i * i == num) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < m; c++)
        {
            char ch;
            cin >> ch;
            table[r][c] = ch - '0';
        }
    }

    long long ans = -1;
    for(int dr = -n; dr < n; dr++)
    {
        for(int dc = -m; dc <= m; dc++)
        {
            if(dr == 0 && dc == 0) continue;
            for(int sr = 0; sr <= n; sr++)
            {
                for(int sc = 0; sc < m; sc++)
                {
                    int r = sr;
                    int c = sc;
                    long long cand = 0;
                    while(0 <= r && r < n && 0 <= c && c < m)
                    {
                        cand = 10 * cand + table[r][c];
                        if(is_square_number(cand)) ans = max(cand, ans);
                        r += dr;
                        c += dc;
                    }
                }
            }
        }
    }
    cout << ans;
}