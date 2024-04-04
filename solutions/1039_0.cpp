#include <bits/stdc++.h>

using namespace std;

bool visited[10000005];

string N;
int K;

int main()
{
    cin >> N;
    cin >> K;

    queue<string> q;
    q.push(N);

    for(int i = 0; i < K; i++) {
        memset(visited, 0, sizeof(visited));
        int sz = q.size();
        for(int j = 0; j < sz; j++) {
            auto s = q.front(); q.pop();
            for(int a = 0; a < N.size(); a++) {
                for(int b = a + 1; b < N.size(); b++) {
                    swap(s[a], s[b]);
                    int toi = stoi(s);
                    if(s.front() != '0' && !visited[toi]) {
                        visited[toi] = true;
                        q.push(s);
                    }
                    swap(s[a], s[b]);
                }
            }
        }
    }

    int idx = -1;
    for(int i = 0; i <= 1000000; i++) {
        if(visited[i]) {
            idx = i;
        }
    }

    cout << idx;
}