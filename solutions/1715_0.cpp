#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX_N = 100000;
int N;

int main() {
    int tmp;
    priority_queue<int, vector<int>, greater<int>> pq;
    scanf("%d", &N);
    for(int i=0; i<N; i++) {
        scanf("%d", &tmp);
        pq.push(tmp);
    }

    int ans = 0;
    while(pq.size() > 1) {
        int top1 = pq.top(); pq.pop();
        int top2 = pq.top(); pq.pop();
        ans += top1 + top2;
        pq.push(top1 + top2);
    }

    printf("%d\n", ans);
}