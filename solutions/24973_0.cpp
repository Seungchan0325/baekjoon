#include <bits/stdc++.h>

using namespace std;

const int MAXN = 303030;

bool U[MAXN], D[MAXN];
int n, p[MAXN], prv[MAXN];
char UD[MAXN];

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> p[i];
    for(int i = 0; i < n-1; i++) {
        cin >> UD[i];
        if(UD[i] == 'U') U[i] = true;
        if(UD[i] == 'D') D[i] = true;

        if(i && UD[i] == UD[i-1]) prv[i] = prv[i-1];
        else prv[i] = i;
    }

    vector<int> v;
    for(int i = 1; i <= n; i++) {
        int j = ssize(v) - 1;
        if(v.empty() || (U[j] && v.back() < p[i]) || (D[j] && v.back() > p[i])) v.push_back(p[i]);
        else {
            if(U[j]) *lower_bound(v.begin()+prv[j], v.end(), p[i]) = p[i];
            if(D[j]) *lower_bound(v.begin()+prv[j], v.end(), p[i], greater<>()) = p[i];
        }
    }
    cout << ssize(v) - 1;
}