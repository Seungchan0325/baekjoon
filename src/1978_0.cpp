#include <iostream>
#include <vector>

using namespace std;

bool isPrime(int x){
    if(x == 1)return false;
    for(int i = 2; i < x; i++) {
        if(x % i == 0)return false;
    }
    return true;
}

int main(){
    int n;
    cin >> n;
    
    vector<int> v(n);
    while(n--){
        cin >> v[n];
    }

    int answer = 0;
    for(auto& v : v){
        answer += isPrime(v);
    }
    cout << answer << endl;
}