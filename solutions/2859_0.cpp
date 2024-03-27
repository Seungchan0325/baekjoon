#include <bits/stdc++.h>

using namespace std;

char days[7][15] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

int main()
{
    int h1, h2, h3, h4;
    int m1, m2, m3, m4;
    scanf("%d:%d", &h1, &m1);
    scanf("%d:%d", &h2, &m2);
    scanf("%d:%d", &h3, &m3);
    scanf("%d:%d", &h4, &m4);

    int mm1, mm2, mm3, mm4;
    mm1 = h1*60 + m1;
    mm2 = h2*60 + m2;
    mm3 = h3*60 + m3;
    mm4 = h4*60 + m4;

    for(int i = 0; i < 1e6; i++) {
        if(mm1 < mm2) {
            int t = (mm2 - mm1 + mm3 - 1) / mm3;
            mm1 += t*mm3;
        } else if(mm2 < mm1) {
            int t = (mm1 - mm2 + mm4 - 1) / mm4;
            mm2 += t*mm4;
        } else {
            break;
        }
    }

    if(mm1 != mm2) {
        cout << "Never";
    } else {
        cout << days[(mm1 / (60 * 24)) % 7] << "\n";
        int m = mm1 % (60 * 24);
        int h = (mm1 / 60) % 24;
        m = m % 60;
        assert(h <= 23 && m <= 59);
        printf("%02d:%02d", h, m);
    }
}