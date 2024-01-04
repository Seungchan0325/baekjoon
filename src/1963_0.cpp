#include <iostream>
#include <memory.h>
#include <queue>

using namespace std;

string n, m;
bool is_prime[10000];
bool visited[10000];

void make_prime() {
    memset(is_prime, 1, sizeof(is_prime));
    for(int i=2; i<=9999; i++) {
        if(!is_prime[i]) continue;
        for(int j=i*i; j<=9999; j+=i) {
            is_prime[j] = false;
        }
    }
}

int solve() {
    int ret = 0;
    queue<string> que;
    que.push(n);
    visited[stoi(n)] = true;

    while(!que.empty()) {
        int q_size = que.size();
        for(int i=0; i<q_size; i++) {
            auto top = que.front(); que.pop();
            
            if(top == m) return ret;

            for(int j=0; j<4; j++) {
                for(char c='0'; c<='9'; c++) {
                    if(j == 0 && c == '0') continue;

                    auto next = top; next[j] = c;

                    if(!visited[stoi(next)] && is_prime[stoi(next)])
                        que.push(next);
                        visited[stoi(next)] = true;
                    }
            }
        }
        ret++;
    }

    return -1;
}

int main() {
    int tc;
    cin>>tc;
    make_prime();
    while(tc--) {
        cin>>n>>m;
        memset(visited, 0, sizeof(visited));

        int result = solve();

        if(result != -1)
            cout<<result<<endl;
        else
            cout<<"Impossible"<<endl;
    }
}