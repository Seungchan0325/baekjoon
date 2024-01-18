#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a, b;
    int l = 0, r = 0;
    //scanf("%d %d", &a, &b);
    cin>>a>>b;
    
    while(true) {
        if      (a == 1) { r+=b-1; break; } 
        else if (b == 1) { l+=a-1; break; }
        if(a < b)   r+=b/a, b%=a;
        else        l+=a/b, a%=b;
    }

    //printf("%d %d\n", l, r);
    cout<<l<<" "<<r<<"\n";
}