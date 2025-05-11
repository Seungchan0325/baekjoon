#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505050;

int N, A, B, DAB[2], D[MAXN][2];

int main()
{
    memset(D, -1, sizeof(D));
    cin >> N >> A >> B >> DAB[0] >> DAB[1]; A--; B--;
    queue<pair<int, int>> q;
    q.emplace(A, 0);
    D[A][0] = 0;
    while(!q.empty()) {
        auto [i, t] = q.front(); q.pop();
        if(i == B) {
            cout << D[i][t] << "\n";
            return 0;
        }
        if(D[(i+DAB[t])%N][t^1] == -1) {
            D[(i+DAB[t])%N][t^1] = D[i][t] + 1;
            q.emplace((i+DAB[t])%N, t^1);
        }
        if(D[(i-DAB[t]+N)%N][t^1] == -1) {
            D[(i-DAB[t]+N)%N][t^1] = D[i][t] + 1;
            q.emplace((i-DAB[t]+N)%N, t^1);
        }
    }
    cout << "Evil Galazy\n";
}