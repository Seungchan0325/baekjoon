#include <iostream>

using namespace std;

#define MIN(x, y) ((x) < (y) ? (x) : (y))

typedef long long int ll;

int readint() {
    register int ret = -1, tmp = -1;
    while(1) {
        tmp = getchar();
        if(tmp == ' ' || tmp == '\n')
            if(ret == -1) continue;
            else break;

        ret = tmp;
    }
    return ret - '0';
}


ll k[2] = {0, 0}, ans[2] = {0, 0}, n, a;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin>>n;
    for(int i=0; i<n; i++) {
        //a = readint() & 1;
        cin>>a; a &= 1;
        ans[a] += k[a ^ 1];
        k[a]++;
    }

    //printf("%lld\n", MIN(ans[0], ans[1]));
    cout<<MIN(ans[0], ans[1]);
}