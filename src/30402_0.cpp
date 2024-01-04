#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    char c;
    for(int i = 0; i < 15; i++) for(int j = 0; j < 15; j++) {
            cin >> c;
            if(c == 'w') {
                cout << "chunbae";
                return 0;
            } else if(c == 'b') {
                cout << "nabi";
                return 0;
            } else if(c == 'g') {
                cout << "yeongcheol";
                return 0;
            }
    }
}