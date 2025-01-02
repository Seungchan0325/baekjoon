#include <bits/stdc++.h>

using namespace std;

int k, N;

int ask(char a, int x)
{
    static int cnt = 0;
    cnt++;
    assert(cnt <= 40);
    cout << "? " << a << " " << x << "\n";
    cout << flush;
    int res = 0;
    cin >> res;
    cout << flush;
    return res;
}

int main()
{
    cin >> N;

    int lo1 = 1;
    int hi1 = N;
    int lo2 = 1;
    int hi2 = N;
    while(true) {
        if(lo1 == hi1 || lo2 == hi2) break;
        int mid1 = (lo1 + hi1) / 2;
        int mid2 = (lo2 + hi2) / 2;
        int a = ask('A', mid1);
        int b = ask('B', mid2);
        if(a < b) {
            hi2 = mid2;
            lo1 = N - hi2 + 1;
        }
        if(a > b) {
            hi1 = mid1;
            lo2 = N - hi1 + 1;
        }
        if(a == b) {
            cout << "! " << a << "\n";
            cout << flush;
            return 0;
        }
    }

    int ans = min(ask('A', lo1), ask('B', lo2));
    cout << "! " << ans << "\n";
    cout << flush;
}