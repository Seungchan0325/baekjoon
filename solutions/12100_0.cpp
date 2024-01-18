#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

int n;

void left(int arr[][MAXN], int next[][MAXN])
{
    for(int r = 0; r < n; r++)
    {
        queue<int> q;
        for(int c = 0; c < n; c++)
        {
            if(arr[r][c] != 0)
            {
                q.push(arr[r][c]);
            }
        }

        int last = 0;
        while(!q.empty())
        {
            int f = q.front(); q.pop();
            if(!q.empty() && f == q.front())
            {
                f += q.front(); q.pop();
            }
            next[r][last] = f;
            last++;
        }
    }
}

void right(int arr[][MAXN], int next[][MAXN])
{
    for(int r = 0; r < n; r++)
    {
        queue<int> q;
        for(int c = n - 1; c >= 0; c--)
        {
            if(arr[r][c] != 0)
            {
                q.push(arr[r][c]);
            }
        }

        int last = n-1;
        while(!q.empty())
        {
            int f = q.front(); q.pop();
            if(!q.empty() && f == q.front())
            {
                f += q.front(); q.pop();
            }
            next[r][last] = f;
            last--;
        }
    }
}

void up(int arr[][MAXN], int next[][MAXN])
{
    for(int c = 0; c < n; c++)
    {
        queue<int> q;
        for(int r = 0; r < n; r++)
        {
            if(arr[r][c] != 0)
            {
                q.push(arr[r][c]);
            }
        }

        int last = 0;
        while(!q.empty())
        {
            int f = q.front(); q.pop();
            if(!q.empty() && f == q.front())
            {
                f += q.front(); q.pop();
            }
            next[last][c] = f;
            last++;
        }
    }
}

void down(int arr[][MAXN], int next[][MAXN])
{
    for(int c = 0; c < n; c++)
    {
        queue<int> q;
        for(int r = n - 1; r >= 0; r--)
        {
            if(arr[r][c] != 0)
            {
                q.push(arr[r][c]);
            }
        }

        int last = n - 1;
        while(!q.empty())
        {
            int f = q.front(); q.pop();
            if(!q.empty() && f == q.front())
            {
                f += q.front(); q.pop();
            }
            next[last][c] = f;
            last--;
        }
    }
}

int f(int cur[][MAXN], int depth)
{
    int ret = 0;

    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < n; c++)
        {
            ret = max(cur[r][c], ret);
        }
    }

    if(depth >= 5)
    {
        return ret;
    }
    
    int next[MAXN][MAXN];
    memset(next, 0, sizeof(next));
    left(cur, next);
    ret = max(f(next, depth + 1), ret);
    
    memset(next, 0, sizeof(next));
    right(cur, next);
    ret = max(f(next, depth + 1), ret);
    
    memset(next, 0, sizeof(next));
    up(cur, next);
    ret = max(f(next, depth + 1), ret);
    
    memset(next, 0, sizeof(next));
    down(cur, next);
    ret = max(f(next, depth + 1), ret);
    
    return ret;
}

int main()
{
    cin >> n;
    int arr[MAXN][MAXN];
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < n; c++)
        {
            cin >> arr[r][c];
        }
    }

    int result = f(arr, 0);

    cout << result;
}