#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);

    int n;
    cin >> n;
    priority_queue<int> pg1;
    priority_queue<int, vector<int>, greater<int>> pg2;
    
    int cur;
    for(int i = 0; i < n; i++) {
        cin >> cur;
        
        if(pg1.size() <= pg2.size()) {
            pg1.push(cur);
        }else {
            pg2.push(cur);
        }

        if(pg1.size() > 0 && pg2.size() > 0 && pg1.top() > pg2.top()) {
            int tmp1 = pg1.top(),
                tmp2 = pg2.top();

            pg1.pop(); pg2.pop();

            pg1.push(tmp2);
            pg2.push(tmp1);
        }

        cout << pg1.top() << "\n";
    }
}