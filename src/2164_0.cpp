#include <iostream>
#include <queue>

using namespace std;

int main(){
    int n;
    cin >> n;

    queue<int> que;
    for(int i = 0; i < n; i++)
        que.push(i+1);
    
    int i;
    bool Pop=true;
    while(!que.empty()){
        if(Pop){
            i = que.front(); que.pop();
            Pop=false;
        }else{
            i = que.front(); que.pop();
            que.push(i);
            Pop=true;
        }
    }
    cout << i << endl;
}