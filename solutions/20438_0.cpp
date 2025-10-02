#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5050;

int N, K, Q, M, S[MAXN];
bool sleeping[MAXN], attend[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> K >> Q >> M;
    for(int i = 1; i <= K; i++) {
        int x; cin >> x; sleeping[x] = true;
    }
    for(int i = 1; i <= Q; i++) {
        int x; cin >> x;
        if(sleeping[x] || attend[x]) continue;
        for(int j = x; j <= N+2; j += x) {
            attend[j] = true;
        }
    }
    for(int i = 3; i <= N+2; i++) {
        S[i] += S[i-1] + (attend[i] == false || sleeping[i] == true);
    }

    while(M--) {
        int s, e; cin >> s >> e;
        cout << S[e] - S[s-1] << "\n";
    }
}