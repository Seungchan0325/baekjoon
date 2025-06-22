#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin>> n >> m;

    if((n%2) && (m==1)) {
        cout << "-1\n";
        return 0;
    }
    if(n%2 == 0) {
        cout << m << "\n";
        cout << "2 ";
        for(int i = 0; i < m-1; i++) cout << n-2*i-2 << " ";
        cout << "\n";
    } else {
        cout << m << "\n";
        cout << n << " 2 ";
        for(int i = 0; i < m-2; i++) cout << n-2*i-3 << " ";
    }
}