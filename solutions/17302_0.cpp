#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;

int N, M;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);


    cin >> N >> M;
    cout << "1\n";
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            char c;
            cin >> c;
            int adj = 0;
            if(i > 1) adj++;
            if(i < N) adj++;
            if(j > 1) adj++;
            if(j < M) adj++;

            int p = 0;
            if(c == 'W') p = 0;
            else p = 1;

            p += adj;
            p %= 2;

            if(p) cout << "3";
            else cout << "2";
        }
        cout << "\n";
    }
}