#include <bits/stdc++.h>

using namespace std;

const int INF = 1<<15;

string s[3];
short cache[200][200][200][1<<3];

short compute_score(int pos[3], int bit)
{
    int max_cnt = 0;
    int cnt[7] = {0,};
    for(int i = 0; i < 3; i++) {
        if((bit & (1<<i)) || s[i].size() <= pos[i]) continue;
        max_cnt = max(++cnt[s[i][pos[i]]-'A'], max_cnt);
    }
    if(max_cnt == 3) return 3;
    else if(__builtin_popcount(bit) == 1 && max_cnt == 2) return 1;
    else return 0;
}

short dp(int pos[3], int bit)
{
    if(pos[0] == s[0].size() && pos[1] == s[1].size() && pos[2] == s[2].size()) return 0;
    if(pos[0] > s[0].size() || pos[1] > s[1].size() || pos[2] > s[2].size()) return -INF;

    short& ret = cache[pos[0]][pos[1]][pos[2]][bit];
    if(ret != -1) return ret;

    ret = -INF;
    for(int nbit = 0; nbit < (1<<3); nbit++) {
        if(nbit & bit) continue;
        short score = compute_score(pos, nbit);
        for(int i = 0; i < 3; i++) {
            if(!(nbit & (1<<i))) {
                pos[i]++;
            }
        }
        ret = max((short)(dp(pos, nbit) + score), ret);
        for(int i = 0; i < 3; i++) {
            if(!(nbit & (1<<i))) {
                pos[i]--;
            }
        }
    }
    return ret;
}

void restruct(int pos[3], int bit)
{
    if(pos[0] == s[0].size() && pos[1] == s[1].size() && pos[2] == s[2].size()) return;
    if(pos[0] > s[0].size() || pos[1] > s[1].size() || pos[2] > s[2].size()) {
        assert(0);
    }
    for(int nbit = 0; nbit < (1<<3); nbit++) {
        if(nbit & bit) continue;
        int npos[3] = {0,};
        memcpy(npos, pos, sizeof(npos));
        for(int i = 0; i < 3; i++) {
            if(!(nbit & (1<<i))) {
                npos[i]++;
            }
        }
        if(dp(npos, nbit) + compute_score(pos, nbit) == dp(pos, bit)) {
            for(int i = 0; i < 3; i++) {
                cout << ((nbit & (1<<i)) ? ('&') : s[i][pos[i]]);
            }
            cout << "\t" << compute_score(pos, nbit);
            cout << "\n";
            restruct(npos, nbit);
            return;
        }
    }
    assert(0);
}

int main()
{
    for(int i = 0; i < 3; i++)
        cin >> s[i];
    memset(cache, -1, sizeof(cache));
    int tmp[3] = {0, 0, 0};
    int result = max(dp(tmp, 0), (short)-1);
    // cout << "\n";
    // restruct(tmp, 0);
    cout << result;
}