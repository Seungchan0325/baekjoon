#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
vector<int> v;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i++)
        v.push_back(i);
    do{
        for(auto& i : v){
            cout << i << ' ';
        }
        cout << '\n';
    }while(next_permutation(v.begin(), v.end()));
}