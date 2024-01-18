#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20;

int n;

int Left(int arr[MAXN][MAXN], int next[MAXN][MAXN])
{
    int max_v = 0;
    for(int r = 0; r < n; r++)
    {
        queue<int> q;
        for(int c = 0; c < n; c++)
        {
            if(arr[r][c] != 0)
            {
                q.push(arr[r][c]);
            }
            next[r][c] = 0;
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

            max_v = max(f, max_v);

            last++;
        }
    }

    return max_v;
}

void Turn(int arr[MAXN][MAXN])
{
    int tmp[MAXN][MAXN] = {0,};
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < n; c++)
        {
            tmp[c][n-r-1] = arr[r][c];
        }
    }
    memcpy(arr, tmp, sizeof(tmp));
}

int result = 0;

void GetMaxBlock(int arr[MAXN][MAXN], int depth, int max_v)
{
    if(depth > 10)
    {
        return;
    }

    if(max_v * pow(2, 10 - depth) <= result)
    {
        return;
    }

    int next[MAXN][MAXN] = {0,};
    for(int i = 0; i < 4; i++)
    {
        int next_max = Left(arr, next);
        result = max(next_max, result);
        if(memcmp(arr, next, sizeof(next)) != 0)
        {
            GetMaxBlock(next, depth + 1, next_max);
        }
        Turn(arr);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    int max_v = 0;
    int arr[MAXN][MAXN];
    for(int r = 0; r < n; r++)
    {
        for(int c = 0; c < n; c++)
        {
            cin >> arr[r][c];
            max_v = max(arr[r][c], max_v);
        }
    }

    result = max_v;
    GetMaxBlock(arr, 0, max_v);

    cout << result;
}