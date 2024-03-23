#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int N, M;
bool t[MAXN];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        int st; cin >> st;
        t[st] = true;
    }

    int job1, job2;
    job1 = job2 = 0;
    queue<int> q;
    for(int i = MAXN-1; i >= 0; i--) {
        if(t[i]) {
            job1++; job2++;
            q.push(i);
        } else {
            if(job2) {
                job2--;
                if(q.front() - i > M) goto FAIL;
                q.pop();
            } else if(job1) {
                job1--;
            }
        }
    }

    if(job1 || job2) goto FAIL;

    cout << "success";
    return 0;
FAIL:
    cout << "fail";
    return 0;
}