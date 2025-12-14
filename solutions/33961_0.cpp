#include <bits/stdc++.h>

using namespace std;

int main()
{
    int m; cin >> m;
    if(m < 3) {
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";
    if(m%3 == 0) {
        for(int c = 1; c < m; c+=3) {
            cout << "1 " << c << "\n";
            cout << "2 " << c+1 << "\n";
            cout << "1 " << c+2 << "\n";
            cout << "2 " << c << "\n";
            cout << "1 " << c+1 << "\n";
            cout << "2 " << c+2 << "\n";
        }
    } else if(m%3 == 1) {
        int c;
        for(c = 1; c+4 < m; c += 3) {
            cout << "1 " << c << "\n";
            cout << "2 " << c+1 << "\n";
            cout << "1 " << c+2 << "\n";
            cout << "2 " << c << "\n";
            cout << "1 " << c+1 << "\n";
            cout << "2 " << c+2 << "\n";
        }
        cout << "1 " << c << "\n";
        cout << "2 " << c+1 << "\n";
        cout << "1 " << c+3 << "\n";
        cout << "2 " << c+2 << "\n";
        cout << "1 " << c+1 << "\n";
        cout << "2 " << c << "\n";
        cout << "1 " << c+2 << "\n";
        cout << "2 " << c+3 << "\n";
    } else {
        int c;
        for(c = 1; c + 5 < m; c += 3) {
            cout << "1 " << c << "\n";
            cout << "2 " << c+1 << "\n";
            cout << "1 " << c+2 << "\n";
            cout << "2 " << c << "\n";
            cout << "1 " << c+1 << "\n";
            cout << "2 " << c+2 << "\n";
        }
        cout << "1 " << c << "\n";
        cout << "2 " << c+1 << "\n";
        cout << "1 " << c+2 << "\n";
        cout << "2 " << c << "\n";
        cout << "1 " << c+1 << "\n";
        cout << "2 " << c+3 << "\n";
        cout << "1 " << c+4 << "\n";
        cout << "2 " << c+2 << "\n";
        cout << "1 " << c+3 << "\n";
        cout << "2 " << c+4 << "\n";
    }
}