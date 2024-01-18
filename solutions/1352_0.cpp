#include <bits/stdc++.h>

using namespace std;

vector<int> v;

bool f(int s, int sum, int n) {
    if(sum == n) return true;
    if(n < sum) return false;

    for(int next = sum + 1; next > s; next--)
        if(f(next, sum + next, n)) {
            v.push_back(next);
            return true;
        }
    
    return false;
}

int main() {
    int n; cin >> n;

    if(f(1, 1, n)) {
        v.push_back(1);
        char next_char = 'A';
        queue<char> q;
        for(int i = 1; i <= n; i++) {
            if(i == v.back()) {
                cout << next_char;
                v.pop_back();
                for(int j = 0; j < i-1; j++) q.push(next_char);
                next_char++;
            } else {
                cout << q.front(); q.pop();
            }
        }
    } else {
        cout << -1;
    }
}