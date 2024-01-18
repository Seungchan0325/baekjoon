#include <iostream>

using namespace std;

#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef long long int ll;

ll k[2] = {0, 0}, ans[2] = {0, 0}, n, a;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin>>n;

    register ll m = (n + 7) / 8;
    switch(n % 8) {
        case 0: do {    cin>>a; a &= 1; ans[a] += k[a^1]; k[a]++;
        case 7:         cin>>a; a &= 1; ans[a] += k[a^1]; k[a]++;
        case 6:         cin>>a; a &= 1; ans[a] += k[a^1]; k[a]++;
        case 5:         cin>>a; a &= 1; ans[a] += k[a^1]; k[a]++;
        case 4:         cin>>a; a &= 1; ans[a] += k[a^1]; k[a]++;
        case 3:         cin>>a; a &= 1; ans[a] += k[a^1]; k[a]++;
        case 2:         cin>>a; a &= 1; ans[a] += k[a^1]; k[a]++;
        case 1:         cin>>a; a &= 1; ans[a] += k[a^1]; k[a]++;
        } while(--m>0);
    }

    cout<<MIN(ans[0], ans[1]);
}