#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 1e4 + 1;

int N, x[MaxN], y[MaxN], o[MaxN], a[MaxN];

int RangeQuery(vector<int>& BIT, int p){
    int ret = 0;
    while(0 < p){
        ret += BIT[p];
        p -= p & -p;
    }
    return ret;
}

void PointUpdate(vector<int>& BIT, int p, int x){
    while(p <= 1001){
        BIT[p] += x;
        p += p & -p;
    }
}

void solve(){
    for(int i = 1; i <= N; i++){
        cin >> x[i] >> y[i];
        o[i] = i;
    }
    sort(o + 1, o + N + 1, [](int lhs, int rhs){
        return x[lhs] < x[rhs];
    });
    vector<int> BIT(1001);
    int i = 1;
    while(i <= N){
        vector<int> pool;
        int cur_x = x[o[i]];
        while(i <= N && cur_x == x[o[i]]){
            pool.push_back(y[o[i]]);
            a[o[i]] = RangeQuery(BIT, y[o[i]] - 1);
            i++;
        }
        for(int cur_y : pool){
            PointUpdate(BIT, cur_y, 1);
        }
    }
    for(int i = 1; i <= N; i++){
        cout << a[i] << "\n";
    }
}

int main(){
    while(cin >> N){
        solve();
    }
}