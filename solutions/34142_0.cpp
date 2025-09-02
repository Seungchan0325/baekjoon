#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2020;

int N, M, K, p, q;
int U[MAXN][MAXN], D[MAXN][MAXN], L[MAXN][MAXN], R[MAXN][MAXN];
int US[MAXN][MAXN], DS[MAXN][MAXN], LS[MAXN][MAXN], RS[MAXN][MAXN];
int UE[MAXN][MAXN], DE[MAXN][MAXN], LE[MAXN][MAXN], RE[MAXN][MAXN], A[MAXN][MAXN];

void print(int a[MAXN][MAXN]) {
    cout << "--- start print ---\n";
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "--- done ----\n";
}

bool inrange(int x, int n)
{
    return 0 <= x && x <= n;
}

int main()
{
    cin >> N >> M >> K;
    cin >> p >> q;
    for(int i = 1; i <= K; i++) {
        int r, c, d;
        cin >> r >> c >> d;
        if(d == 0) {
            A[r][c]++;
            continue;
        }

        DS[r-d][c-d]++;
        DS[r][c]--;
        DE[r+2][c-2]--;
        DE[r+d+2][c-d-2]++;

        RS[r][c]++;
        RS[r+d+2][c-d-2]--;
        RE[r][c+2]--;
        RE[r+d][c+d+2]++;
        R[r+d][c+d+1]--;

        US[r][c+2]++;
        US[r+d][c+d+2]--;
        UE[r-d][c+d]--;
        UE[r][c]++;

        LS[r-d][c+d]++;
        LS[r][c]--;
        LE[r-d][c-d]--;
        LE[r][c]++;
    }

    // cout << "DS\n";
    // print(DS);
    // cout << "DE\n";
    // print(DE);

    // cout << "RS\n";
    // print(RS);
    // cout << "RE\n";
    // print(RE);

    // cout << "US\n";
    // print(US);
    // cout << "UE\n";
    // print(UE);

    // cout << "LS\n";
    // print(LS);
    // cout << "LE\n";
    // print(LE);
    for(int i = 2; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(j-2 >= 0) DS[i][j] += DS[i-2][j-2];
            DE[i][j] += DE[i-2][j+2];
            RS[i][j] += RS[i-2][j+2];
            if(j-2 >= 0) RE[i][j] += RE[i-2][j-2];
            if(j-2 >= 0) US[i][j] += US[i-2][j-2];
            UE[i][j] += UE[i-2][j+2];
            LS[i][j] += LS[i-2][j+2];
            if(j-2 >= 0) LE[i][j] += LE[i-2][j-2];
        }
    }

    // cout << "DS\n";
    // print(DS);
    // cout << "DE\n";
    // print(DE);

    // cout << "RS\n";
    // print(RS);
    // cout << "RE\n";
    // print(RE);

    // cout << "US\n";
    // print(US);
    // cout << "UE\n";
    // print(UE);

    // cout << "LS\n";
    // print(LS);
    // cout << "LE\n";
    // print(LE);
    

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            D[i][j] += D[i-1][j] + DS[i][j] + DE[i][j];
            R[i][j] += R[i][j-1] + RS[i][j] + RE[i][j];
        }
    }
    
    for(int i = N; i >= 1; i--) {
        for(int j = M; j >= 1; j--) {
            U[i][j] += U[i+1][j] + US[i][j] + UE[i][j];
            L[i][j] += L[i][j+1] + LS[i][j] + LE[i][j];
        }
    }
    
    
        
        // cout << "D\n";
        // print(D);
    
        // cout << "R\n";
        // print(R);
    
        // cout << "U\n";
        // print(U);
    
        // cout << "L\n";
        // print(L);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            A[i][j] += L[i][j] + R[i][j] + D[i][j] + U[i][j];
        }
    }

    // print(A);

    long long ans = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            ans += (i*p)^(j*q)^A[i][j];
        }
    }
    cout << ans << "\n";
}