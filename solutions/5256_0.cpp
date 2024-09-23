#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int N, B[MAXN], l, r, used[2*MAXN];

void upd_l()
{
    while(used[l]) l++;
    cout << l << " ";
    used[l] = true;
}

void upd_r()
{
    while(used[r]) r--;
    cout << r << " ";
    used[r] = true;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> B[i];
    }

    l = 0;
    r = 2*N;
    used[l] = used[r] = true;

    cout << B[1] << " ";
    used[B[1]] = true;

    for(int i = 2; i <= N; i++) {
        if(B[i-1] == B[i]) {
            upd_l();
            upd_r();
        } else if(B[i-1] < B[i]) {
            if(used[B[i]]) {
                upd_r();
                upd_r();
            } else {
                cout << B[i] << " ";
                used[B[i]] = true;
                upd_r();
            }
        } else {
            if(used[B[i]]) {
                upd_l();
                upd_l();
            } else {
                cout << B[i] << " ";
                used[B[i]] = true;
                upd_l();
            }
        }
    }
}