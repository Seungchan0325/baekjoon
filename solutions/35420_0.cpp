    #include <bits/stdc++.h>

    using namespace std;

    const int MAXN = 505;

    constexpr int fac[13] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600};

    int N, h[MAXN];

    int main()
    {
        cin >> N;
        for(int i = 0; i < N; i++) cin >> h[i];

        if(N >= 12) {
            for(int i = 0; i < N; i++) {
                if(h[i] > 1) {
                    cout << "2\n";
                    return 0;
                }
            }
            cout << "1\n";
        } else if(N >= 7) {
            auto f = [](auto self, int i, int num, int limit) -> int {
                if(num > limit) return 1e9;
                if(i == N) return num;
                if(h[i] <= 0) return self(self, i+1, num, limit);
                int ans = 1e9;
                for(int j = N-1; j >= i; j--) {
                    for(int k = i; k <= j; k++) h[k] -= fac[N-j+i];
                    ans = min(ans, self(self, i, num+1, limit));
                    for(int k = i; k <= j; k++) h[k] += fac[N-j+i];
                }
                return ans;
            };

            int limits[] = {7, 4, 3, 3, 3};
            int ans = f(f, 0, 0, limits[N-7]+1);
            assert(ans < 1e9);
            cout << ans << "\n";
        } else {
            auto f = [](auto self, int i, int j) {
                if(i == N) {
                    int res = 0;
                    for(int k = 0; k < N; k++) {
                        if(h[k] > 0) res += (h[k] + fac[N]-1) / fac[N];
                    }
                    return res;
                }
                if(j >= N) return self(self, i+1, i+2);
                int res = 1e9;
                res = min(res, self(self, i, j+1));
                for(int k = i; k <= j; k++) h[k] -= fac[N-j+i];
                res = min(res, self(self, i, j+1)+1);
                for(int k = i; k <= j; k++) h[k] += fac[N-j+i];
                return res;
            };

            int ans = f(f, 0, 1);
            assert(ans < 1e9);
            cout << ans << "\n";
        }
    }
