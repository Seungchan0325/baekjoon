#include <iostream>
#include <algorithm>
#include <memory.h>

using namespace std;

int n, m, profits[21][301];
int cache[21][301], invested[21];
int trace[21][301];

int LargestProfits(int company, int money) {
    if(money == 0 || company == m) return 0;

    int& ret = cache[company][money];
    if(ret != -1) return ret;

    for(int cost=0; 0<=money-cost; cost++) {
        int result = LargestProfits(company+1, money-cost)+profits[company][cost];
        if(ret <= result) {
            ret = result;
            trace[company][money] = cost;
        }
    }

    return ret;
}

void reconstruct(int company, int money) {
    if(money == 0 || company == m) return;

    int max_profit = -1, max_profit_cost = -1;
    for(int i=0; i<=money; i++) {
        if(max_profit <= cache[company][money]) {
            max_profit = cache[company][money];
            max_profit_cost = trace[company][money];
        }
    }

    invested[company] = max_profit_cost;
    reconstruct(company+1, money-max_profit_cost);
}

int main() {
    memset(cache, -1, sizeof(cache));
    int cost, tmp;
    cin>>n>>m;
    for(int i=0; i<n; i++) {
        cin>>cost;
        for(int j=0; j<m; j++) {
            cin>>tmp;
            profits[j][cost] = tmp;
        }
    }

    int result = LargestProfits(0, n);
    reconstruct(0, n);

    cout<<result<<endl;
    for(int i=0; i<m; i++)
        cout<<invested[i]<<" ";
}