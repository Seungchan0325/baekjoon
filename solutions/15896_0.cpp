#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010101;

int N, A[MAXN], B[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    for(int i = 1; i <= N; i++) {
        cin >> B[i];
    }

    int ans = 0;
    for(int j = 0; j < 30; j++) {
        int bit = 1<<j;
        int a, b;
        a = b = 0;
        for(int i = 1; i <= N; i++) {
            if(A[i]&bit) a++;
            if(B[i]&bit) b++;
        }
        bit %= 1999;
        a %= 1999;
        b %= 1999;
        ans += bit*a%1999*b%1999;
        ans %= 1999;
    }
    cout << ans << " ";
    ans = 0;
    for(int j = 0; j < 30; j++) {
        int bit = 1<<j;
        int mask = bit-1;
        int A1, A2, A3, A4, B1, B2, B3, B4;
        A1 = A3 = B1 = B3 = 0;
        A2 = A4 = B2 = B4 = bit;
        for(int i = 1; i <= N; i++) {
            if(A[i]&bit) {
                A3 = max(A3, A[i]&mask);
                A4 = min(A4, A[i]&mask);
            } else {
                A1 = max(A1, A[i]&mask);
                A2 = min(A2, A[i]&mask);
            }
            if(B[i]&bit) {
                B3 = max(B3, B[i]&mask);
                B4 = min(B4, B[i]&mask);
            } else {
                B1 = max(B1, B[i]&mask);
                B2 = min(B2, B[i]&mask);
            }
        }
        if(A2+B2 >= bit && A1+B3 < bit && A4+B4 >= bit && A3+B1 < bit) ans |= bit;
    }
    cout << ans << "\n";
}