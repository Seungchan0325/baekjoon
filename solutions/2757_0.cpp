#include <bits/stdc++.h>

using namespace std;

int main()
{
    while(true) {
        int n, m;
        scanf(" R%dC%d" , &n, &m);
        if(n == 0 && m == 0) break;

        m--;

        int len = 1;
        long long sum = 26;
        while(m >= sum) sum += pow(26, len+1), len++;
        sum = 0;
        for(int i = 1; i < len; i++) sum += pow(26, i);
        m -= sum;
        string s;
        for(int i = 0; i < len; i++) s.push_back('A');
        for(int i = len - 1; i >= 0; i--) {
            s[i] += m % 26;
            m /= 26;
        }
        cout << s << n << "\n";
    }
}