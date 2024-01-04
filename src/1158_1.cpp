#include <iostream>
#include <queue>

using namespace std;

int main(){
    int n, k;
    queue<int> que;
    queue<int> result;
    cin >> n >> k;

    for(int i = 0; i < n; i++)
        que.push(i+1);
    
    while(!que.empty()){
        for(int i = 0; i < k-1; i++){
            int tmp = que.front(); que.pop(); que.push(tmp);
        }
        result.push(que.front()); que.pop();
    }

    cout << '<';
    for(int i = 0; i < n; i++){
        cout << result.front(); result.pop();
        if(!result.empty())
            cout << ", ";
    }
    cout << '>';
}