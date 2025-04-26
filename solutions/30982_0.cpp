#include <bits/stdc++.h>

using namespace std;

bool solve(int N, int M, int T, vector<int> Q, int P)
{
    if(M < 0) return false;
    for(int l = 0; l <= P; l++) {
        int t = 2 * (P - l);
        if(t > T) continue;
        int r = P + (T - t);

        bitset<1010*101> s;
        s.set(0);
        for(int i = l; i <= r; i++) {
            s |= (s<<Q[i]);
        }

        if(s.test(M)) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N, M, T, P;
    cin >> N >> M >> T;
    vector<int> Q(N);
    for(int i = 0; i < N; i++) cin >> Q[i];
    cin >> P; P--;
    M -= Q[P];
    Q[P] = 0;

    if(solve(N, M, T, Q, P)) {
        cout << "YES\n";
        return 0;
    }

    P = N - P - 1;
    reverse(Q.begin(), Q.end());
    if(solve(N, M, T, Q, P)) {
        cout << "YES\n";
        return 0;
    }
    
    cout << "NO\n";
    return 0;
}