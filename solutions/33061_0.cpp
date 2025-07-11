#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;
const int MAXQ = 202020;

const int dr[] = {0, 0, -1, 1};
const int dc[] = {-1, 1, 0, 0};
const char pt[] = {'R', 'L', 'D', 'U'};

int N, Q, r[MAXQ], c[MAXQ], chk[1010][1010], sz, ans[MAXQ];
char t[MAXQ], belt[MAXN][MAXN];

void step(int r, int c)
{
    if(chk[r][c]) return;
    chk[r][c] = true;
    sz++;

    for(int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if(nr < 0 || nr > N+1 || nc < 0 || nc > N+1 || chk[nr][nc]) continue;
        if(belt[nr][nc] != '?' && belt[nr][nc] != pt[i]) continue;
        step(nr, nc);
    }
}

void print()
{
    for(int i = 0; i <= N+1; i++) {
        for(int j = 0; j <= N+1; j++) {
            cout << belt[i][j];
        }
        cout << "\n";
    }
    for(int i = 0; i <= N+1; i++) {
        for(int j = 0; j <= N+1; j++) {
            cout << chk[i][j];
        }
        cout << "\n";
    }
    cout << sz << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;

    for(int i = 0; i <= N+1; i++) {
        for(int j = 0; j <= N+1; j++) {
            belt[i][j] = '?';
        }
    }

    for(int i = 1; i <= Q; i++) {
        cin >> r[i] >> c[i] >> t[i];
        belt[r[i]][c[i]] = t[i];
    }

    step(0, 0);
    // print();
    for(int i = Q; i >= 1; i--) {
        ans[i] = (N+2)*(N+2) - sz;
        belt[r[i]][c[i]] = '?';
        for(int j = 0; j < 4; j++) {
            if(chk[r[i]+dr[j]][c[i]+dc[j]]) {
                step(r[i], c[i]);
                break;
            }
        }
        // print();
    }

    for(int i = 1; i <= Q; i++) {
        cout << ans[i] << "\n";
    }
}