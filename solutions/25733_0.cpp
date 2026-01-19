#include <bits/stdc++.h>

using namespace std;

const int MAXN = 202020;

int N, A[MAXN], R[MAXN];
bool done;
set<int> s;

void dfs(int i)
{
    if(done) return;
    if(i == N+1) {
        for(int i = 1; i <= N; i++) cout << A[i] << " ";
        done = true;
        return;
    }

    if(A[i] != -1) return dfs(i+1);

    for(int j = *s.begin(); j <= N; j = *s.upper_bound(j)) {
        bool ok = true;
        if(i > 1 && A[i-1] != -1 && abs(A[i-1]-j) == 1) ok = false;
        if(i < N && A[i+1] != -1 && abs(A[i+1]-j) == 1) ok = false;
        if(ok) {
            s.erase(j);
            A[i] = j;
            dfs(i+1);
            A[i] = -1;
            s.insert(j);
            if(done) break;
        }
    }
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) cin >> A[i];
    int cnt = 0;
    for(int i = 1; i <= N; i++) {
        if(A[i] != -1) R[A[i]] = 1;
    }
    for(int i = 1; i <= N; i++) {
        if(!R[i]) s.insert(i);
    }
    s.insert(N+1);
    dfs(1);
    if(!done) cout << "-1\n";
}