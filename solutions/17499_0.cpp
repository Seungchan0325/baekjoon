#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int N, Q, a[MAXN], init;

int main()
{
    cin >> N >> Q;
    
    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }

    while(Q--) {
        int t;
        cin >> t;
        
        if(t == 1) {
            int i, x;
            cin >> i >> x;
            a[(init + i - 1 + N) % N] += x;
        } else if(t == 2) {
            int s;
            cin >> s;
            init = (init - s + N) % N;
        } else {
            int s;
            cin >> s;
            init = (init + s + N) % N;
        }
    }

    for(int i = 0; i < N; i++) {
        cout << a[(init + i + N) % N] << " ";
    }
}