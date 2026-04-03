#include <iostream>
#include <algorithm>

using namespace std;

using ll = long long;

const int MAXK = 101010;

ll N, M, K, xs[MAXK];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> K;
    for(int i = 0; i < K; i++) {
        cin >> xs[i];
    }
    if(N == 1) {
        ll x = 0;
        for(int i = 1; i < M; i++) {
            if(binary_search(xs, xs+K, 2*i)) {
                cout << 2*i << "\n";
                return 0;
            }
        }
        cout << "0\n";
        return 0;
    }
    ll x = 0;
    for(int i = 1; i <= M; i++) {
        if(i == M) {
            x = x + 2*N-1;
            break;
        }
        ll y = x+2*N;
        while(y > x && binary_search(xs, xs+K, y)) {
            y -= 2;
        }
        if(y == x) {
            x += 2*N;
            break;
        }
        x = y;
    }
    cout << x << "\n";
}
