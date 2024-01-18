#include <iostream>
#include <memory.h>

using namespace std;

const int INF = 987654321;

int n, k, coins[100];
int cache[100001];

int f(int value) {
    if(value < 0) return INF;

    int& ret = cache[value];
    if(ret != -1) return ret;

    ret = INF;
    for(int i=0; i<n; i++)
        ret = min(ret, f(value-coins[i])+1);

    return ret;
}

int main() {
    memset(cache, -1, sizeof(cache));
    cache[0] = 0;
    
    cin>>n>>k;
    for(int i=0; i<n; i++)
        cin>>coins[i];
    
    int result = f(k);

    if(result != INF)
        cout<<result<<endl;
    else
        cout<<-1<<endl;
}