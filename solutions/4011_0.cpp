#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void print(auto a)
{
    cout << "--- enter print(a) ---\n";
    for(int i = 1; i < a.size(); i++) {
        for(int j = 1; j < a[i].size(); j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "--- exit print(a) ---\n";
}

struct Solver {
    int m, n, k;
    vector<vector<int>> a;
    vector<vector<ll>> sum;
    vector<vector<ll>> rmx;
    vector<vector<ll>> cmx;

    Solver(vector<vector<int>> a, int k) : a(a), k(k)
    {
        m = ssize(a) - 1;
        n = ssize(a[0]) - 1;
        sum.resize(m+1, vector<ll>(n+1));
        rmx.resize(m+1, vector<ll>(n+1, -1e15));
        cmx.resize(m+1, vector<ll>(n+1, -1e15));
    }

    ll solve()
    {
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + a[i][j];
            }
        }
        for(int i = k; i <= m; i++) {
            for(int j = k; j <= n; j++) {
                rmx[i][j] = max(rmx[i][j-1], sum[i][j] - sum[i-k][j] - sum[i][j-k] + sum[i-k][j-k]);
            }
        }
        for(int j = k; j <= n; j++) {
            for(int i = k; i <= m; i++) {
                cmx[i][j] = max(cmx[i-1][j], sum[i][j] - sum[i-k][j] - sum[i][j-k] + sum[i-k][j-k]);
            }
        }

        // cout << format("[Debug] parallel() = {}\n", parallel());
        // cout << format("[Debug] orthogonal() = {}\n", orthogonal());
        ll ans = max(parallel(), orthogonal());

        return ans;
    }

    ll parallel()
    {
        ll ans = -1e15;
        vector<ll> mx1(m+2, -1e15), mx2(m+2, -1e15);
        for(int i = 1; i <= m; i++) mx1[i] = max(rmx[i][n], mx1[i-1]);
        for(int i = m; i >= 1; i--) mx2[i] = max(rmx[i][n], mx2[i+1]);

        for(int i = 1; i <= m; i++) {
            ll mx = -1e15;
            for(int j = i; j <= m; j++) {
                mx = max(rmx[j][n], mx);
                if(i-k >= 0 && j+k <= m)
                    ans = max(ans, mx + mx1[i-k] + mx2[j+k]);
            }
        }
        return ans;
    }

    ll orthogonal()
    {
        ll ans = -1e15;
        vector<vector<ll>> mx1(m+2, vector<ll>(n+2, -1e15));
        vector<vector<ll>> mx2(m+2, vector<ll>(n+2, -1e15));
        for(int i = k; i <= m; i++) {
            for(int j = k; j <= n; j++) {
                mx1[i][j] = max({mx1[i-1][j], mx1[i][j-1], sum[i][j] - sum[i-k][j] - sum[i][j-k] + sum[i-k][j-k]});
            }
        }

        for(int i = m; i >= k; i--) {
            for(int j = k; j <= n; j++) {
                mx2[i][j] = max({mx2[i+1][j], mx2[i][j-1], sum[i][j] - sum[i-k][j] - sum[i][j-k] + sum[i-k][j-k]});
            }
        }

        ll mx = -1e15;
        for(int j = n; j >= 1; j--) {
            mx = max(mx, cmx[m][j]);
            for(int i = 1; i <= m; i++) {
                if(j-k >= 0 && i+k <= m)
                    ans = max(ans, mx + mx1[i][j-k] + mx2[i+k][j-k]);
            }
        }
        return ans;
    }
};

vector<vector<int>> rotate(vector<vector<int>> a)
{
    int m = ssize(a) - 1;
    int n = ssize(a[0]) - 1;
    vector<vector<int>> b(n+1, vector<int>(m+1));

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            b[j][i] = a[m-i+1][j];
        }
    }

    return b;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int m, n, k;
    cin >> m >> n >> k;
    vector<vector<int>> a(m+1, vector<int>(n+1));
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    ll ans = -1e15;
    for(int i = 0; i < 4; i++) {
        // print(a);
        ans = max(ans, Solver(a, k).solve());
        a = rotate(a);
    }
    cout << ans;
}