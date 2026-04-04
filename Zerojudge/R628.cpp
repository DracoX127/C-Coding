#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 1e5 + 1;
int N, num[MaxN];

int RangeQuery(vector<int>& BIT, int p){
    int ret = 0;
    while(0 < p){
        ret += BIT[p];
        p -= p & -p;
    }
    return ret;
}

void PointUpdate(vector<int>& BIT, int p, int x){
    int cur = p;
    while(cur <= N){
        if(cur == p) BIT[cur] += x;      // update position p normally
        else BIT[cur] -= 1;      // decrement all other affected positions
        cur += cur & -cur;
    }
}

int main(){
    cin >> N;
    for(int n = 1; n <= N; n++) cin >> num[n];
    vector<int> BIT(N + 1, 0);
    vector<int> Inv_pair(N + 1, 0);
    // scan right to left: count how many already-seen values are < num[n]
    for(int n = N; n >= 1; n--){
        Inv_pair[n] = RangeQuery(BIT, num[n] - 1);
        PointUpdate(BIT, num[n], 1);
    }
    long long ans = 0;
    for(int n = 1; n <= N; n++) ans += Inv_pair[n];
    cout << ans << "\n";
}