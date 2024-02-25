#include <bits/stdc++.h>

using namespace std;

using llint = long long int;

const int MOD = 998244353;
const int MAXN = 100005;

int N, and_cnt[35], last_one[35], xor_cnt[35][2];

int main()
{
    cin >> N;
    llint and_ans = 0;
    llint or_ans = 0;
    llint xor_ans = 0;
    for(int i = 1; i <= N; ++i) {
        int A; cin >> A;
        for(int j = 0; j < 32; ++j) {
            if(A & (1LL<<j)) {
                and_cnt[j]++;
                and_ans += (1LL<<j) * and_cnt[j];
                and_ans %= MOD;

                or_ans += (1LL<<j) * i;
                or_ans %= MOD;
                last_one[j] = i;
                
                swap(xor_cnt[j][0], xor_cnt[j][1]);
                xor_cnt[j][1]++;
                xor_ans += (1LL<<j) * xor_cnt[j][1];
                xor_ans %= MOD;
            } else {
                and_cnt[j] = 0;

                if(last_one[j]) {
                    or_ans += (1LL<<j) * (last_one[j]);
                    or_ans %= MOD;
                }

                ++xor_cnt[j][0];
                xor_ans += (1LL<<j) * xor_cnt[j][1];
                xor_ans %= MOD;
            }
        }
    }
    printf("%lld %lld %lld\n", and_ans, or_ans, xor_ans);
}