#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3005;

double cache[MAXN][MAXN];

double dp(int i, int j)
{
    if(i == 0 && j == 0) return 0;

    double& ret = cache[i][j];
    if(ret != INFINITY) return ret;

    ret = 1;
    if(i > 0) ret += i * dp(i-1, j+1);
    if(j > 0) ret += j * dp(i, j-1);
    ret /= (i + j);
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    for(int i = 0; i < MAXN; i++) for(int j = 0; j < MAXN; j++) cache[i][j] = INFINITY;
    int t; cin >> t;
    while(t--) {
        int N, K;
        cin >> N >> K;
        map<int, int> m;
        for(int i = 0; i < K; i++) {
            int a; cin >> a;
            m[a]++;
        }
        
        int i = 0;
        int j = 0;
        int k = 0;

        for(auto [key, item] : m) {
            if(item >= 2) k++;
            else if(item == 1) j++;
        }

        i = N - j - k;

        cout << fixed << setprecision(10) << N * dp(i, j) << "\n";
    }
}