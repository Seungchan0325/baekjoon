#include <bits/stdc++.h>
using namespace std;

bool isValid(int N, const vector<int>& Q) {
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (Q[i] == Q[j]) return false;
            if (abs(Q[i] - Q[j]) == abs(i - j)) return false;
        }
    }
    return true;
}

vector<int> solve(int N) {
    vector<int> evens, odds;
    evens.reserve((N+1)/2);
    odds.reserve((N+1)/2);

    for (int i = 2; i <= N; i += 2) evens.push_back(i);
    for (int i = 1; i <= N; i += 2) odds.push_back(i);

    int r = N % 6;
    if (r == 2) {
        swap(odds[0], odds[1]);
        int x = odds[2];
        odds.erase(odds.begin() + 2);
        odds.push_back(x);
    } else if (r == 3) {
        int x = evens.front();
        evens.erase(evens.begin());
        evens.push_back(x);
        for (int k = 0; k < 2; ++k) {
            int y = odds.front();
            odds.erase(odds.begin());
            odds.push_back(y);
        }
    }

    vector<int> Q;
    Q.reserve(N);
    Q.insert(Q.end(), evens.begin(), evens.end());
    Q.insert(Q.end(), odds.begin(), odds.end());
    return Q;
}

int main() {
    int N;
    cin >> N;

    auto Q = solve(N);
    for (int x : Q) cout << x << "\n";
}
