#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    cin >> s;

    int ans = 0;
    int frame = 1;
    int remain_chance = 2;
    int remain_ball = 10;
    int i = 0;
    while(frame <= 10 && i < s.size()) {
        int plus = 0;
        if('0' <= s[i] && s[i] <= '9') {
            plus += s[i] - '0';
            remain_ball -= s[i] - '0';
            if(--remain_chance == 0) {
                remain_ball = 10;
                remain_chance = 2;
                frame++;
            }
        } else if (s[i] == 'S') {
            plus += 10;
            if('0' <= s[i+1] && s[i+1] <= '9') {
                plus += s[i+1] - '0';
            } else {
                if(s[i+1] == 'S') {
                    plus += 10;
                } else if(s[i+1] == '-') {
                } else {
                    assert(0);
                }
            }
            if('0' <= s[i+2] && s[i+2] <= '9') {
                plus += s[i+2] - '0';
            } else {
                if(s[i+2] == 'P') {
                    if('0' <= s[i+1] && s[i+1] <= '9') {
                        plus += 10 - (s[i+1] - '0');
                    } else if(s[i+1] == '-') {
                        plus += 10;
                    } else {
                        assert(0);
                    }
                } else if(s[i+2] == 'S') {
                    plus += 10;
                } else if(s[i+2] == '-') {
                } else {
                    assert(0);
                }
            }
            remain_ball = 10;
            remain_chance = 2;
            frame++;
        } else if (s[i] == 'P') {
            plus += remain_ball;
            if('0' <= s[i+1] && s[i+1] <= '9') {
                plus += s[i+1] - '0';
            } else {
                if(s[i+1] == 'S') {
                    plus += 10;
                } else if(s[i+1] == '-') {
                } else {
                    assert(0);
                }
            }
            remain_ball = 10;
            remain_chance = 2;
            frame++;
        } else if (s[i] == '-') {
            if(--remain_chance == 0) {
                remain_ball = 10;
                remain_chance = 2;
                frame++;
            }
        } else {
            assert(0);
        }
        // cout << s[i] << " " << plus << "\n";
        i++;
        ans += plus;
    }

    cout << ans;
}