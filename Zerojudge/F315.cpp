#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 2e5 + 1;

int N, uN, num[MaxN * 2];

int RangeQuery(vector<int>& BIT, int p){
    int ret = 0;
    while(0 < p){
        ret += BIT[p];
        p -= p & -p;
    }
    return ret;
}

void PointUpdate(vector<int>& BIT, int p, int x){
    while(p <= N){
        BIT[p] += x;
        p += p & -p;
    }
}

int main(){
    cin >> N;
    vector<pair<int, int>> idx(N + 1); 
    vector<int> Inv_pair(2 * N + 1);
    for(int n = 1; n <= 2 * N; n++){
        cin >> num[n];
        if(idx[num[n]].first != 0){
            idx[num[n]].second = n;
        } else {
            idx[num[n]].first = n;
        }
    }
    vector<int> BIT(N + 1);
    for(int n = 2 * N; n >= 1; n--){
        Inv_pair[n] = RangeQuery(BIT, num[n] - 1);
        PointUpdate(BIT, num[n], 1);
    }
    long long ans = 0;
    for(int n = 1; n <= N; n++){
        ans += Inv_pair[idx[n].first] - Inv_pair[idx[n].second]; 
    }
    cout << ans << "\n";
}