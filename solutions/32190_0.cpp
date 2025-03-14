#include <bits/stdc++.h>

using namespace std;

int N;

int main()
{
    cin >> N;
    if(N == 1) {
        cout << "1 1";
    } else if(N == 2) {
        cout << "1 2 1 2";
    } else if(N&1) {
        deque<int> dq = {2, 1, 2, 3, 1, 3};
        for(int i = 4; i <= N; i++) dq.push_front(i);
        for(int i = 4; i < N; i+=2) dq.push_back(i+1), dq.push_back(i);
        for(int i : dq) cout << i << " ";
    } else {
        deque<int> dq = {1, 2, 1, 2};
        for(int i = 3; i <= N; i++) dq.push_front(i);
        for(int i = 3; i < N; i+=2) dq.push_back(i+1), dq.push_back(i);
        for(int i : dq) cout << i << " ";
    }
}