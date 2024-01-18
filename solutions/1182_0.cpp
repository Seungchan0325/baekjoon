#include <iostream>
#include <vector>

using namespace std;

vector<int> vec;
int cnt=0;
int n, s;
bool flag = false;

void f(int idx, int sum){
    if(idx==vec.size()){
        if(sum==s)
            cnt++;
        
        return;
    }
    f(idx+1, sum);
    f(idx+1, sum+vec[idx]);
}

int main(){
    cin >> n >> s;
    vec.resize(n);
    for(auto& i : vec){
        cin >> i;
    }
    f(0, 0);
    if(s == 0){
        cnt--;
    }
    cout << cnt << endl;
}