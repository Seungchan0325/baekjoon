#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int n, cnt=0;

bool is_can(vector<int>& v, int n){
    int nPos=v.size();
    for(int i=0; i<v.size(); i++){
        if(abs(i-nPos)==abs(v[i]-n) || v[i]==n){
            return false;
        }
    }
    return true;
}
    
void f(int idx, vector<int> pos){
    if(idx == n){
        cnt++;
        return;
    }
    
    for(int i=0; i<n; i++){
        if(is_can(pos, i)){
            vector<int> temp=pos;
            temp.push_back(i);
            f(idx+1, temp);
        }
    }
}

int main(){
    cin >> n;
    f(0, vector<int>());
    cout << cnt;
}