#include <iostream>
#include <memory.h>

using namespace std;

int n;
int p[1001];
int cache[1001];

int LargestAmount(int num) {
    if(num == 0) return 0;
    int& ret = cache[num];
    if(ret != -1) return ret;

    for(int i=1; i<=num; i++) {
        ret = max(LargestAmount(num-i)+p[i], ret);
    }

    return ret;
}

int main() {
    memset(cache, -1, sizeof(cache));

    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>p[i];
    
    int result = LargestAmount(n);

    cout<<result<<endl;
}