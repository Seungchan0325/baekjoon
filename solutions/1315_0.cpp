#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int N, STR[MAXN], INT[MAXN], PNT[MAXN], cache[MAXN][MAXN][MAXN][MAXN];
vector<int> vs, vi;

int dp(int i0, int j0, int i1, int j1)
{
    int& ret = cache[i0][j0][i1][j1];
    if(ret != -1) return ret;
    int pnt = 0;
    ret = 0;
    for(int k = 1; k <= N; k++) {
        if(STR[k] <= vs[i0] || INT[k] <= vi[j0]) {
            pnt += PNT[k];
        } else if(STR[k] <= vs[i1] || INT[k] <= vi[j1]) {
            pnt += PNT[k];
            ret++;
        }
    }

    pnt -= vs[i1] - 1;
    pnt -= vi[j1] - 1;

    int cand = 0;
    if(i1 + 1 < vs.size() && pnt >= vs[i1+1] - vs[i1]) {
        cand = max(cand, dp(i1, j1, i1+1, j1));
    }

    if(j1 + 1 < vi.size() && pnt >= vi[j1+1] - vi[j1]) {
        cand = max(cand, dp(i1, j1, i1, j1+1));
    }

    ret += cand;

    return ret;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> STR[i] >> INT[i] >> PNT[i];
        vs.push_back(STR[i]);
        vi.push_back(INT[i]);
    }

    vs.push_back(0);
    vi.push_back(0);
    vs.push_back(1);
    vi.push_back(1);

    sort(vs.begin(), vs.end());
    vs.erase(unique(vs.begin(), vs.end()), vs.end());
    sort(vi.begin(), vi.end());
    vi.erase(unique(vi.begin(), vi.end()), vi.end());

    assert(vi[0] == 0 && vi[1] == 1 && vs[0] == 0 && vs[1] == 1);

    memset(cache, -1, sizeof(cache));
    int result = dp(0, 0, 1, 1);
    cout << result;
}