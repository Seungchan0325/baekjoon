#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;

void print(vector<int>& b){
    for(auto& i : b){
        cout << i << ' ';
    }
}

void f(int idx, vector<int> v, vector<bool> c){
    if(idx == n){
        print(v);
        cout << '\n';
    }

    for(int i=0; i<n; i++){
        if(!c[i]){
            vector<int> temp1(v);
            vector<bool> temp2(c);
            temp1.push_back(i+1);
            temp2[i]=true;
            f(idx+1, temp1, temp2);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    f(0,vector<int>(),vector<bool>(n));
}