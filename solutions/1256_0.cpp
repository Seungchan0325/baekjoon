#include <bits/stdc++.h>

using namespace std;

int n, m, k;

const int M = 1'000'000'000 + 100;
int bino[205][205];

void build_bino() {
    for(int i = 0; i <= 200; i++) {
        bino[i][0] = bino[i][i] = 1;
        for(int j = 1; j < i; j++)
            bino[i][j] = min(M, bino[i-1][j-1] + bino[i-1][j]);
    }
}

int skip;
bool succeed = false;

void gen(int a, int z, string s) {
    if(skip < 0) return;
    if(a == 0 && z == 0) {
        if(skip == 0) {
            cout << s;
            succeed = true;
        }
        skip--;
        return;
    }
    if(bino[a+z][a] <= skip) {
        skip -= bino[a+z][a];
        return;
    }

    if(a > 0) gen(a-1, z, s + 'a');
    if(z > 0) gen(a, z-1, s + 'z');
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    build_bino();
    skip = k - 1;
    gen(n, m, "");
    if(!succeed) cout << -1;
}