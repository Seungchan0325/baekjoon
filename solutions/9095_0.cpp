#include <iostream>

using namespace std;

int fibo[100];

constexpr void f() {
    for(int i = 3; i < 100; i++)
        fibo[i] = fibo[i - 1] + fibo[i - 2] + fibo[i - 3];
}

int main() {
    int n;
    cin >> n;
    fibo[0] = 1;
    fibo[1] = 2;
    fibo[2] = 4;
    f();
    for(int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cout << fibo[a-1] << "\n";
    }
}