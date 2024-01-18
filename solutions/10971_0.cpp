#include <iostream>
#include <algorithm>

using namespace std;

using ll = long long;

const int MAX_N = 10;

int N, W[MAX_N][MAX_N], route[MAX_N];

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &W[i][j]);

    for (int i = 0; i < N; i++)
        route[i] = i;

    ll ans=987654321;
    do
    {
        ll cost=0;
        for(int i=0; i<N; i++) {
            int cur = route[i];
            int next = route[(i+1)%N];

            if(W[cur][next] == 0) {
                cost = 987654321;
                break;
            }
            cost += W[cur][next];
        }
        ans=min(cost, ans);
    } while(next_permutation(route, route+N));
    printf("%lld\n", ans);
}