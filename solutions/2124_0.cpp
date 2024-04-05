#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD = 1e18;
const int MAXA = 25;

int A, B, C;

ll cache[200000][MAXA];

int toi(vector<int>& s)
{
    int ret = 0;
    for(auto i : s) {
        ret *= C+1;
        ret += i;
    }
    return ret;
}

ll dp(vector<int> s, int x);

ll P(int idx, int prv, const vector<int>& s, vector<int> m, int x)
{
    if(idx == s.size()) {
        return dp(m, x);
    }

    ll ret = 0;
    for(int c = s[idx]; c <= C && c <= prv; c++) {
        m.push_back(c);
        ret += P(idx+1, c, s, m, x);
        ret %= MOD;
        m.pop_back();
    }

    return ret;
}

ll dp(vector<int> s, int x)
{
    if(x == 1) return 1;

    ll& ret = cache[toi(s)][x];
    if(ret != -1) return ret;

    ret = P(0, C, s, {}, x - 1);

    return ret;
}

int main()
{
    cin >> A >> B >> C;

    memset(cache, -1, sizeof(cache));

    ll result = P(0, C, vector<int>(B, 0), {}, A);

    cout << result;
}