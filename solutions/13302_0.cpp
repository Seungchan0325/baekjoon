#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN = 105;

bool days[MAXN];
int n, m, cache[MAXN][45];

int min_cost(int day, int coupones) {
    if(day >= n) return 0;

    int& ret = cache[day][coupones];
    if(ret != -1) return ret;

    if(days[day]) return ret = min_cost(day+1, coupones);

    ret = INF;
    if(coupones >= 3) ret = min(min_cost(day + 1, coupones - 3), ret);
    ret = min(min_cost(day + 1, coupones) + 10000, ret);
    ret = min(min_cost(day + 3, coupones + 1) + 25000, ret);
    ret = min(min_cost(day + 5, coupones + 2) + 37000, ret);

    return ret;
}

int main() {
    cin>>n>>m;
    for(int i = 0; i < m; i++) {
        int a; cin>>a; a--;
        days[a] = true;
    }

    memset(cache, -1, sizeof(cache));
    int result = min_cost(0, 0);

    cout<<result;
}