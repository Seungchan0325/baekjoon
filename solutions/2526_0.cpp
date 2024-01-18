#include <iostream>
#include <vector>

using namespace std;

int n, p, ans;
int visited[1000000];

inline int operate(int a) {
    return (a*n)%p;
}

void search() {
    int cur = n, index = 0;
    bool stop_flag = false;

    while(true) {
        int i = operate(cur);

        if(visited[i] != 0) {
            ans = index - visited[i];
            break;
        }

        visited[i] = index;
        index++;
        cur = i;
    }
}

int main() {
    cin >> n >> p;

    search();

    cout << ans; 
}