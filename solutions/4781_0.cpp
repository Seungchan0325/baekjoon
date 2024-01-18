#include <iostream>
#include <memory.h>

using namespace std;

int n, m, calories[5001], costs[5001];
int cache[10001];

int LargestCalorie(int money) {
    if(money == 0) return 0;

    int& ret = cache[money];
    if(ret != -1) return ret;

    ret = 0;

    for(int i=0; i<n; i++)
        if(money-costs[i] >= 0)
            ret = max(LargestCalorie(money-costs[i])+calories[i], ret);
    
    return ret;
}

int main() {
    float tmp;
    while(true) {
        memset(cache, -1, sizeof(cache));
        cin>>n>>tmp;
        m = tmp*100.0+0.5;
        if(!n && !m) break;

        for(int i=0; i<n; i++) {
            cin>>calories[i]>>tmp;
            costs[i] = tmp*100.0+0.5;
        }

        int result = LargestCalorie(m);

        cout<<result<<endl;
    }
}