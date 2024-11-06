#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll M1 = 325;
const ll P1 = 99999611;
const ll M2 = 645;
const ll P2 = 99999773;
const ll M3 = 532;
const ll P3 = 99999323;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    cin >> n;
    char c;
    ll h1 = 0, h2 = 0, h3 = 0;
    ll rh1 = 0, rh2 = 0, rh3 = 0;
    ll p1 = 1, p2 = 1, p3 = 1;
    // char buf[1<<20];
    while(cin >> c) {
        // for(int i = 0; i < m; i++) {
        //     c = buf[i];
            if(c == '\n') break;
            h1 = (h1 * M1 + c) % P1;
            h2 = (h2 * M2 + c) % P2;
            h3 = (h3 * M3 + c) % P3;
            rh1 = (rh1 + p1 * c) % P1;
            rh2 = (rh2 + p2 * c) % P2;
            rh3 = (rh3 + p3 * c) % P3;
            p1 = p1 * M1 % P1;
            p2 = p2 * M2 % P2;
            p3 = p3 * M3 % P3;
        // }
    }
    if(h1 == rh1 && h2 == rh2 && h3 == rh3) cout << "TAK";
    else cout << "NIE";
}