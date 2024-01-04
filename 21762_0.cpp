#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

string x, y, w;
int cnt_x[200005][256];
int cnt_y[200005][256];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin>>t;
    while(t--) {
        cin>>x;
        cin>>y;
        cin>>w;

        for(int i=1; i<=x.size(); i++) {
            memcpy(cnt_x[i], cnt_x[i-1], sizeof(int) * 256);
            cnt_x[i][x[i-1]]++;
        }
        for(int i=1; i<=y.size(); i++) {
            memcpy(cnt_y[i], cnt_y[i-1], sizeof(int) * 256);
            cnt_y[i][y[i-1]]++;
        }

        bool flag = false;
        vector<int> xl_ranges, xr_ranges;
        int last = 0;
        xl_ranges.push_back(0);
        for(int i=0; i<w.size(); i++) {
            while(x[last] != w[i]) last++;
            xl_ranges.push_back(last + 1);
            last++;
        }

        last = x.size() - 1;
        xr_ranges.push_back(x.size());
        for(int i=w.size()-1; i>=0; i--) {
            while(x[last] != w[i]) last--;
            xr_ranges.push_back(last);
            last--;
        }

        vector<int> yl_ranges, yr_ranges;
        last = 0;
        yl_ranges.push_back(0);
        for(int i=0; i<w.size(); i++) {
            while(y[last] != w[i]) last++;
            yl_ranges.push_back(last + 1);
            last++;
        }

        last = y.size() - 1;
        yr_ranges.push_back(y.size());
        for(int i=w.size()-1; i>=0; i--) {
            while(y[last] != w[i]) last--;
            yr_ranges.push_back(last);
            last--;
        }

        reverse(xr_ranges.begin(), xr_ranges.end());
        reverse(yr_ranges.begin(), yr_ranges.end());

        // for(auto i : xl_ranges) cout<<i<<" ";
        // cout<<"\n";
        // for(auto i : xr_ranges) cout<<i<<" ";
        // cout<<"\n";
        // for(auto i : yl_ranges) cout<<i<<" ";
        // cout<<"\n";
        // for(auto i : yr_ranges) cout<<i<<" ";
        // cout<<"\n";

        for(int i=0; i<w.size()+1; i++) {
            for(int j='a'; j<='z'; j++) {
                int cond1 = cnt_x[xr_ranges[i]][j] - cnt_x[xl_ranges[i]][j];
                int cond2 = cnt_y[yr_ranges[i]][j] - cnt_y[yl_ranges[i]][j];
                if(cond1 > 0 && cond2 > 0) flag = true;
            }
        }
        
        cout<<(int)flag<<"\n";
    }
}