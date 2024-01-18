#include <bits/stdc++.h>

using namespace std;

const int INF = 987654321;
const int MAXN  = 2005;

int n;
string str;

int cache[MAXN];
int PelindromeDivision(int start) {
    if(start == n) return 0;
    int& ret = cache[start];
    if(ret != -1) return ret;

    ret = INF;

    vector<int> mem;
    for(int end = start+1; end <= n; end++) {
        bool flag = true;
        int l = start;
        int r = end - 1;
        while(l < r) {
            if(str[l] != str[r]) {
                flag = false;
                break;
            }
            l++; r--;
        }
        
        if(flag)
            ret = min(ret, PelindromeDivision(end) + 1);
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(cache, -1, sizeof(cache));
    cin >> str;
    n = str.size();

    int result = PelindromeDivision(0);
    cout << result;
}