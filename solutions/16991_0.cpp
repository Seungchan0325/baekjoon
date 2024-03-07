#include <bits/stdc++.h>

using namespace std;

const int MAXN = 17;

int N, X[MAXN], Y[MAXN];
double cache[1<<MAXN][MAXN][MAXN];

double distance(int i, int j)
{
    return sqrt((X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j]));
}

double tsp(int taken, int cur, int start)
{
    if(taken == (1<<N)-1) return distance(cur, start);
    double& ret = cache[taken][cur][start];
    if(ret != INFINITY) return ret;

    for(int i = 0; i < N; i++) {
        if(taken & (1<<i)) continue;
        ret = min(tsp(taken | (1<<i), i, start) + distance(i, cur), ret);
    }

    return ret;
}

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];
    }

    for(int i = 0; i < (1<<N); i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                cache[i][j][k] = INFINITY;
            }
        }
    }

    double result = INFINITY;
    for(int i = 0; i < N; i++)
        result = min(tsp((1<<i), i, i), result);
    cout << fixed << setprecision(9) << result;
}