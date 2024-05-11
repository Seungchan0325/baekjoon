#include <bits/stdc++.h>

using namespace std;

using ll = long long;

bool vi[1000005];
ll N, X;

int main()
{
    cin >> N >> X;

    vector<int> v;
    vi[N] = true;
    v.push_back(N);
    for(int i = 1; i < N - 1; i++) {
        if(N - 1 - i <= X) {
            v.push_back(i);
            X -= N - 1 - i;
            vi[i] = true;
        }
    }
    v.push_back(N-1);
    vi[N-1] = true;

    for(int i = N; i >= 1; i--) {
        if(!vi[i]) v.push_back(i);
    }

    if(X != 0) {
        cout << -1;
        return 0;
    }

    for(int i : v) cout << i << " ";
}