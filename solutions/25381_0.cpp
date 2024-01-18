#include <bits/stdc++.h>

using namespace std;

const int MAX = 300000;

string str;
queue<int> A, B;

int main() {
    cin >> str;

    int cnt = 0;
    for(int i = 0; i < str.size(); i++) {
        switch(str[i]) {
            case 'A': A.push(i); break;
            case 'B': B.push(i); break;
            case 'C':
                if(!B.empty()) {
                    cnt++;
                    B.pop();
                }
            break;
        }
    }

    while(!A.empty() && !B.empty()) {
        if(A.front() > B.front()) B.pop();
        else {
            cnt++;
            A.pop(); B.pop();
        }
    }

    cout << cnt;
}