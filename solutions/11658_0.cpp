#include <bits/stdc++.h>

using namespace std;

using llint = long long;

const int MAXN = 1100;

int N, M;
llint tree[MAXN][MAXN], table[MAXN][MAXN];

void update(int y, int x, int d)
{
    for(int i = y; i <= N; i += (i & -i))
        for(int j = x; j <= N; j += (j & -j))
            tree[i][j] += d;
}

llint query(int y, int x)
{
    llint ret = 0;
    for(int i = y; i > 0; i -= (i & -i))
        for(int j = x; j > 0; j -= (j & -j))
            ret += tree[i][j];
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cin >> table[i][j];
            update(i, j, table[i][j]);
        }
    }

    while(M--) {
        int w;
        cin >> w;
        if(w == 0) {
            int x, y, c;
            cin >> y >> x >> c;
            update(y, x, c - table[y][x]);
            table[y][x] = c;
        } else {
            int x1, y1, x2, y2;
            cin >> y1 >> x1 >> y2 >> x2;

            llint result = query(y2, x2);
            result -= query(y2, x1-1);
            result -= query(y1-1, x2);
            result += query(y1-1, x1-1);

            cout << result << "\n";
        }
    }
}