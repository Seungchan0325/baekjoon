#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

int N, M, S[MAXN], A[MAXN], cache[MAXN][MAXN];
vector<pair<int, int>> v;

int lcs(int n, int m)
{
    int& ret = cache[n][m];
    if(ret != -1) return ret;

    ret = 0;
    for(int i = n + 1; i <= N; i++) {
        if(n == 0 || S[n] < S[i]) {
            auto it = upper_bound(v.begin(), v.end(), make_pair(S[i], m));
            if(it == v.end() || it->first != S[i]) continue;
            assert(it->second > m);
            ret = max(ret, lcs(i, it->second) + 1);
        }
    }

    return ret;
}

void restruct(int n, int m)
{
    for(int i = n + 1; i <= N; i++) {
        if(n == 0 || S[n] < S[i]) {
            auto it = upper_bound(v.begin(), v.end(), make_pair(S[i], m));
            if(it == v.end() || it->first != S[i]) continue;
            assert(it->second > m);
            if(lcs(n, m) == lcs(i, it->second) + 1) {
                cout << S[i] << " ";
                restruct(i, it->second);
                return;
            }
        }
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> S[i];
    cin >> M;
    for(int i = 1; i <= M; i++) {
        cin >> A[i];
        v.emplace_back(A[i], i);
    }

    sort(v.begin(), v.end());

    memset(cache, -1, sizeof(cache));
    int result = lcs(0, 0);
    cout << result << "\n";
    restruct(0, 0);
}