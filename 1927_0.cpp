#include <iostream>
#include <queue>

#define endl '\n'

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    priority_queue<int, vector<int>, greater<int>> pq;
    cin>>n;
    for(int i=0; i<n;i++) {
        int tmp;
        cin>>tmp;
        if(tmp>0) {
            pq.push(tmp);
        }else {
            if(pq.empty()) {
                cout<<0<<endl;
                continue;
            }
            cout<<pq.top()<<endl; pq.pop();
        }
    }
}