#include <bits/stdc++.h>

using namespace std;

int main()
{
    string tmp;
    cin >> tmp;

    string s;
    s.push_back('?');
    for(char c : tmp)
    {
        s.push_back(c);
        s.push_back('?');
    }
    
    int n = s.size();
    int p = 0;
    int r = 0;
    vector<int> A(n);
    for(int i = 0; i < n; i++)
    {
        if(i <= r)
            A[i] = min(A[2 * p - i], r - i);
        else
            A[i] = 0;
        
        int left = i - A[i] - 1;
        int right = i + A[i] + 1;
        while(0 <= left && right < n && s[left] == s[right])
        {
            A[i]++;
            left--;
            right++;
        }

        if(r < i + A[i])
        {
            r = i + A[i];
            p = i;
        }
    }

    long long ans = 0;
    for(int i = 0; i < n; i++) {
        ans += (A[i] + 1) / 2;
    }
    cout << ans;
}