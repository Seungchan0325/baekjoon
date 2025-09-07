#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int N, A[MAXN], cache[MAXN][MAXN];

int dp(int i, int j)
{
    if(i < j) swap(i, j);
    if(i == N) {
        return A[N] - A[j];
    }
    int& ret = cache[i][j];
    if(ret != -1) return ret;
    ret = 1e9;
    ret = min(max(A[i+1]-A[i], dp(i+1, j)), max(A[i+1]-A[j], dp(i, i+1)));
    return ret;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    sort(A+1, A+N+1);
    memset(cache, -1, sizeof(cache));

    vector<int> front, back;
    int i = 1;
    int j = 1;
    front.push_back(A[i]);
    back.push_back(A[j]);
    int mx = 0;
    for(int k = 1; k < N; k++) {
        if((i >= j && dp(1, 1) == max({dp(i+1, j), mx, A[i+1]-A[i]})) || (i < j && dp(1, 1) == max({dp(j+1, j), mx, A[j+1]-A[i]}))) {
            front.push_back(A[max(i, j)+1]);
            mx = max(front.end()[-1] - front.end()[-2], mx);
            if(i >= j) i++;
            else i = j+1;
        } else {
            back.push_back(A[max(i, j)+1]);
            mx = max(back.end()[-1] - back.end()[-2], mx);
            if(i <= j) j++;
            else j = i+1;
        }
    }

    reverse(back.begin(), back.end());
    front.insert(front.end(), back.begin(), back.end());
    front.pop_back();
    for(auto i : front) cout << i << " ";
}