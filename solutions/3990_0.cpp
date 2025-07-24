#include <bits/stdc++.h>

using namespace std;

double f(int up, int down, int h)
{
    if(up == down) return max(0, h - down);
    if(up < down) swap(up, down);
    if(h < down) return 0;
    if(h > up) return h - up + (up - down) / 2.0;
    return (h - down) * (h - down) / 2.0 / (up - down);
}

const int MAXN = 101010;
const int MAXH = 1000;

int N, M, A[MAXN];
double area[MAXH+1];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 0; i < N; i++) cin >> A[i];

    for(int i = 1; i < N; i++) {
        for(int j = 0; j <= MAXH; j++) {
            area[j] += f(A[i-1], A[i], j);
        }
    }
    cout << fixed << setprecision(3);
    while(M--) {
        char c; cin >> c;

        if(c == 'Q') {
            int h; cin >> h;
            cout << area[h] << "\n";
        } else {
            int x, h; cin >> x >> h;
            for(int i = max(x, 1); i < min(x+2, N); i++) {
                for(int j = 0; j <= MAXH; j++) {
                    area[j] -= f(A[i-1], A[i], j);
                }
            }
            A[x] = h;
            for(int i = max(x, 1); i < min(x+2, N); i++) {
                for(int j = 0; j <= MAXH; j++) {
                    area[j] += f(A[i-1], A[i], j);
                }
            }
        }
    }
}