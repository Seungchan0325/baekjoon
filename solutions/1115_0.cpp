#include <bits/stdc++.h>

using namespace std;

const int MAXN = 50;

int n, arr[MAXN];
bool visited[MAXN];

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int cnt = 0;
    for(int i = 0; i < n; i++)
    {
        if(visited[i])
        {
            continue;
        }

        cnt++;
        
        int pos = i;
        while(!visited[pos])
        {
            visited[pos] = true;
            pos = arr[pos];
        }
    }

    if(cnt == 1)
    {
        cnt = 0;
    }

    cout << cnt;
}