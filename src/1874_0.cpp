#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;
    queue<int> q;
    stack<int> st;
    vector<int> v(n);

    for(auto& i : v) cin >> i;
    for(int i = 1; i <= n; i++) q.push(i);

    st.push(q.front());
    q.pop();

    int point = 0;
    vector<char> ans;
    ans.push_back('+');
    while(true) {
        if(point >= n) break;
        if(st.empty()) {
            if(q.empty()) {
                goto FAILED;
            }
            else if(q.front() > v[point]){
                goto FAILED;
            }
            else{
                goto PUSH;
            }
        }
        if(v[point] > st.top()) {
PUSH:       
            if(q.empty()) goto FAILED;
            st.push(q.front());
            q.pop();
            ans.push_back('+');
        } else {
            point++;
            st.pop();
            ans.push_back('-');
        }
    }

    for(auto& i : ans) cout << i << '\n';
    return 0;
FAILED:
{
    cout << "NO\n";
    return 0;
}
}