#include <bits/stdc++.h>

using namespace std;

const int MAXN = 101010;

int N, K, A[MAXN];

int main()
{
    cin >> N >> K;
    for(int i = 1; i <= N; i++) cin >> A[i];
    vector<int> v;
    priority_queue<int> pq;
    int i = 1;
    while(v.size() < N) {
        while(pq.size() <= K && i <= N) {
            pq.push(-A[i++]);
        }
        v.push_back(-pq.top()); pq.pop();
    }
    for(auto i : v) cout << i << " ";
}