#include <bits/stdc++.h>

using namespace std;

int di[] = {0, 1, -1, 0};
int dj[] = {1, 0, 0, -1};

int N, M, A[202020];
bool done;

int idx(int i, int j)
{
    return (i-1)*M+(j-1);
}

bool inrange(int x, int n)
{
    return 1 <= x && x <= n;
}

void print()
{
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cout << A[idx(i, j)] << " ";
        }
        cout << "\n";
    }
}

bool chk(int i, int j, int k)
{
    for(int d = 0; d < 4; d++) {
        int ni = i + di[d];
        int nj = j + dj[d];
        if(!inrange(ni, N) || !inrange(nj, M)) continue;
        if(A[idx(ni, nj)] == k) return false;
    }
    return true;
}

void dfs(int i, int j)
{
    if(done) return;
    if(j == M+1) return dfs(i+1, 1);
    if(i == N+1) {
        print();
        done = true;
        return;
    }

    if(A[idx(i, j)]) return dfs(i, j+1);

    for(int k = 1; k <= 4; k++) {
        if(chk(i, j, k)) {
            A[idx(i, j)] = k;
            dfs(i, j+1);
            if(done) break;
        }
    }
    A[idx(i, j)] = 0;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T; cin >> T;
    while(T--) {
        cin >> N >> M;
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= M; j++) {
                cin >> A[idx(i, j)];
            }
        }
        done = false;
        dfs(1, 1);
        assert(done == true);
    }
}