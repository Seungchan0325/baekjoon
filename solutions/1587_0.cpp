#include <bits/stdc++.h>

using namespace std;

int nA, nB, M;
pair<int, int> edges[55];

int main()
{
    cin >> nA >> nB;
    cin >> M;
    for(int i = 0; i < M; i++) {
        cin >> edges[i].first >> edges[i].second;
    }

    int ans = -1;
    if((nA & 1) && (nB & 1)) {
        for(int i = 0; i < M; i++) {
            if((edges[i].first & 1) && (edges[i].second & 1)) {
                ans = nA / 2 + nB / 2 + 1;
                break;
            }
        }
        if(ans == -1) {
            ans = nA / 2 + nB / 2;
        }
    } else {
        ans = nA / 2 + nB / 2;
    }

    cout << ans;
}