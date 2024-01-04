#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int k;
int n=0;
vector<int> v;
vector<bool> result;

void fun(int sum, int idx){
    if(idx == k){
        if(sum > 0 && sum < n)
            result[sum] = true;
        return;
    }
    fun(sum+v[idx], idx+1);
    fun(sum, idx+1);
    fun(sum-v[idx], idx+1);
}

int main(){
    cin >> k;
    v.resize(k);
    for(auto& i : v){
        cin >> i;
        n += i;
    }
    result.resize(n);
    fun(0,0);
    result[0] = true;
    n=0;
    for(auto i : result){
        n += !i;
    }
    cout << n;
}