#include <bits/stdc++.h>

using namespace std;

int N;

int compute(int c1, string op)
{
    if(c1 <= 0) return -1e9;
    int v = op[1] - '0';
    int ret = -1e9;
    if(op[0] == '+') {
        ret = c1 + v;
    } else if(op[0] == '-') {
        ret = c1 - v;
    } else if(op[0] == '/') {
        ret = c1 / v;
    } else if(op[0] == '*') {
        ret = c1 * v;
    }
    if(ret <= 0) return -1e9;
    return ret;
}

int main()
{
    cin >> N;

    int c1 = 1;
    int c2 = 0;
    for(int i = 1; i <= N; i++) {
        string op1, op2;
        cin >> op1 >> op2;
        c2 = max({compute(c2, op1), compute(c2, op2), c1});
        c1 = max({compute(c1, op1), compute(c1, op2)});
        if(max(c1, c2) <= 0) {
            cout << "ddong game\n";
            return 0;
        }
    }

    int ans = max(c1, c2);
    if(ans <= 0) {
        cout << "ddong game\n";
    } else {
        cout << ans;
    }
}