#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

using ll = long long;

const int MAX_K = 100;
int K, N, primaries[MAX_K];
priority_queue<ll, vector<ll>, greater<ll>> pq;

int main() {
    scanf("%d %d", &K, &N);
    for(int i=0; i<K; i++) {
        scanf("%d", primaries+i);
        pq.push(primaries[i]);
    }

    for(int i=0; i<N-1; i++) {
        ll top = pq.top();
        pq.pop();

        for(int j=0; j<K; j++) {
            pq.push(top * primaries[j]);

            if(top % primaries[j] == 0) break;
        }
    }

    printf("%d\n", pq.top());
}