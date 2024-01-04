#include <bits/stdc++.h>

using namespace std;

using ll = long long;

bool old_visited[250005];
bool visited[250005];
ll sum = 0;
ll n, c[250005];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> c[i];
        if(c[i] != 0) {
            sum += c[i];
            old_visited[i] = true;
        }
    }
    memcpy(visited, old_visited, sizeof(visited));
    ll ans1 = 0;
    for(int i = 0; i < n; i++) {
        if(visited[i] == false) {
            ans1 += 1;
            visited[(n+i-1)%n] = true;
            visited[(i+1)%n] = true;
        }
    }

    memcpy(visited, old_visited, sizeof(visited));
    ll ans2 = 0;
    for(int i = 1; i <= n; i++) {
        int idx = i%n;
        if(visited[idx] == false) {
            ans2 += 1;
            visited[(n+idx-1)%n] = true;
            visited[(idx+1)%n] = true;
        }
    }

    cout << sum + max(ans1, ans2);
}