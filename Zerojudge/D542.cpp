#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 5e5 + 1;
const int MaxA = 1e9;

int N, uN, num[MaxN], srt[MaxN];

int RangeQuery(vector<int>& BIT, int p){
    int ret = 0;
    while(0 < p){
        ret += BIT[p];
        p -= p & -p;
    }
    return ret;
}

void PointUpdate(vector<int>& BIT, int p, int x){
    while(p < uN){
        BIT[p] += x;
        p += p & -p;
    }
}

int main(){
    while(cin >> N && N > 0){
        for(int n = 1; n <= N; n++){
            cin >> num[n];
            srt[n] = num[n];
        }
        sort(srt + 1, srt + N + 1);
        uN = unique(srt + 1, srt + N + 1) - srt;
        vector<int> BIT(uN);
        long long ans = 0;
        for(int n = 1; n <= N; n++){
            int p = lower_bound(srt + 1, srt + uN, num[n]) - srt;
            ans += n - 1 - RangeQuery(BIT, p);
            PointUpdate(BIT, p, 1);
        }
        cout << ans << "\n";
    }
}